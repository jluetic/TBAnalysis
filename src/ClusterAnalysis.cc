#include "TROOT.h"
#include "TInterpreter.h"
#include "TH1.h"
#include "TH2.h"
#include "TKey.h"
#include "TClass.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include "ClusterAnalysis.h"
using std::vector;
using std::map;
ClusterAnalysis::ClusterAnalysis(const std::string inFilename,const std::string outFilename) :
  BeamAnaBase::BeamAnaBase(),
  outFile_(outFilename)
{
  std::cout << "EDM Tuple Analyzer initialized with the following options\n" 
            << "Infile: " << inFilename
            << "\nOutFile: " << outFile_
            << std::endl; 
  if( setInputFile(inFilename) == 0 ) {
    std::cout << "Empty Chain!!";
    exit(1);
  }
  nEntries_ = analysisTree()->GetEntries();
  hist_ = new Histogrammer(outFile_);
  beginJob();

}
void ClusterAnalysis::bookHistograms() {
  hist_->bookEventHistograms();
  hist_->bookDUTHistograms("det0");
  hist_->bookDUTHistograms("det1");
  //hist_->bookStubHistograms();
  hist_->bookCorrelationHistograms();
  hist_->bookClusterCorrHistograms();
}

void ClusterAnalysis::beginJob() {
  setAddresses();
  bookHistograms();
  analysisTree()->GetEntry(0);
  getCbcConfig(condEv()->cwd, condEv()->window);
}
 
void ClusterAnalysis::eventLoop()
{
   //if (fChain == 0) return;

   Long64_t nbytes = 0, nb = 0;
   cout << "#Events=" << nEntries_ << endl;
   hist_->fillHist1D("EventInfo","nevents", nEntries_);

   double angle = static_cast<double>(condEv()->DUTangle)>100 ? (static_cast<double>(condEv()->DUTangle)-999000.)/10.-5. : static_cast<double>(condEv()->DUTangle+5.);

   std::cout << "CBC configuration:: SW=" << stubWindow()
             << "\tCWD=" << cbcClusterWidth()
             << "\tOffset1="<< cbcOffset1() 
             << "\tOffset2=" << cbcOffset2()
             << "\tAngle=" << angle
			 << "\t Tilt=" << static_cast<unsigned long int>(condEv()->tilt)
   << std::endl;
 
   for (Long64_t jentry=0; jentry<nEntries_;jentry++) {
	 clearEvent();   
  //for (Long64_t jentry=0; jentry<50;jentry++) {
//     cout << "running over entry:  " << jentry << endl;
	Long64_t ientry = analysisTree()->GetEntry(jentry);
     //std::cout << "Chain load status=" << ientry << std::endl;
     if (ientry < 0) break;
     if (jentry%10000 == 0) {
       cout << " Events processed. " << std::setw(8) << jentry 
	    << endl;
     }
     //cout << "Point 1" << endl;
     if(jentry==0) {
       hist_->fillHist1D("EventInfo","hvSettings", condEv()->HVsettings);
       hist_->fillHist1D("EventInfo","dutAngle", angle);
       hist_->fillHist1D("EventInfo","vcth", condEv()->vcth);
       hist_->fillHist1D("EventInfo","offset", cbcOffset1());
       hist_->fillHist1D("EventInfo","offset", cbcOffset2());
       hist_->fillHist1D("EventInfo","window", stubWindow());
       hist_->fillHist1D("EventInfo","tilt", static_cast<unsigned long int>(condEv()->tilt));
     }
     hist_->fillHist1D("EventInfo","isPeriodic",isPeriodic());
     hist_->fillHist1D("EventInfo","isGoodFlag",isGoodEvent());

       if(!isGoodEvent()){continue;}
      
      setDetChannelVectors();
      if(dutRecoClmap()->at("det0C0").size()!=1 || dutRecoClmap()->at("det1C0").size()!=1 ) {  continue;}      
      if(dutRecoClmap()->at("det0C0")[0].size>1 || dutRecoClmap()->at("det1C0")[0].size>1 ) {  continue;}		
//      if(dutRecoClmap()->at("det0C0")[0].x-127<40 || dutRecoClmap()->at("det1C0")[0].x-127>87 ) {  continue;}
      const auto& d0c0 = *det0C0();
      const auto& d0c1 = *det0C1();
      const auto& d1c0 = *det1C0();
      const auto& d1c1 = *det1C1();     
      hist_->fillClusterCorrHistograms(dutRecoClmap()->at("det0C0"),dutRecoClmap()->at("det1C0"),"C0");
      hist_->fillHist1D("det0","chsizeC0", d0c0.size());
      hist_->fillHistofromVec(d0c0,"det0","hitmapC0");
      hist_->fill2DHistofromVec(d0c0,d0c1,"det0","hitmapfull");
      hist_->fillClusterHistograms("det0",dutRecoClmap()->at("det0C0"),"C0");

      //Fill histo for det1
      //std::cout << "Hits det1c0=" << dut1Ch0()->size() << std::endl;
      hist_->fillHist1D("det1","chsizeC0", d1c0.size());
      //hist_->fillHist1D("det1","chsizeC1", d1c1.size());
      hist_->fillHistofromVec(d1c0,"det1","hitmapC0");
      //hist_->fillHistofromVec(d1c1,"det1","hitmapC1");
      hist_->fill2DHistofromVec(d1c0,d1c1,"det1","hitmapfull");
      hist_->fillClusterHistograms("det1",dutRecoClmap()->at("det1C0"),"C0");
      //hist_->fillClusterHistograms("det1",dutRecoClmap()->at("det1C1"),"C1");
      
      //cout << "Point 4" << endl;
      if(d0c0.size() && !d1c0.size()) hist_->fillHist1D("Correlation","cor_hitC0", 1);
      if(!d0c0.size() && d1c0.size()) hist_->fillHist1D("Correlation","cor_hitC0", 2);
      if(d0c0.size() && d1c0.size()) hist_->fillHist1D("Correlation","cor_hitC0", 3);
      if(!d0c0.size() && !d1c0.size()) hist_->fillHist1D("Correlation","cor_hitC0", 4);
      hist_->fillHist1D("Correlation","nclusterdiffC0", dutRecoClmap()->at("det1C0").size() - 
                                                     dutRecoClmap()->at("det1C0").size()); 
	  
   }
}

void ClusterAnalysis::clearEvent() {
  BeamAnaBase::clearEvent();
}
void ClusterAnalysis::endJob() {
  BeamAnaBase::endJob();
  hist_->closeFile();
}

ClusterAnalysis::~ClusterAnalysis(){
  delete hist_;
}
