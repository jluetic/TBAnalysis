#ifndef BaselineAnalysis_h
#define BaselineAnalysis_h

#include "BeamAnaBase.h"

#include "TString.h"
//#include "Utility.h"
#include "DataFormats.h"
#include "Histogrammer.h"

class TH1;
class BaselineAnalysis : public BeamAnaBase {
 public:
  BaselineAnalysis(const string inFilename,const string outFilename);
  ~BaselineAnalysis();
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
