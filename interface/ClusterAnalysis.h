#ifndef ClusterAnalysis_h
#define ClusterAnalysis_h

#include "BeamAnaBase.h"

#include "TString.h"
//#include "Utility.h"
#include "DataFormats.h"
#include "Histogrammer.h"

class TH1;
class ClusterAnalysis : public BeamAnaBase {
 public:
  ClusterAnalysis(const string inFilename,const string outFilename);
  ~ClusterAnalysis();
  void beginJob();
  void eventLoop(); 
  void bookHistograms();
  void clearEvent();
  void endJob();

 private:
  std::string outFile_;
  Histogrammer* hist_;
  unsigned long int nEntries_; 
};
#endif
