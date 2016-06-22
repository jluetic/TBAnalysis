#ifndef __Histogrammer__HH
#define __Histogrammer__HH

#include "TDirectory.h"
#include "TProfile.h"
#include "TFile.h"
#include "Utility.h"
#include "DataFormats.h"
#include<string>
#include<vector>
class Histogrammer {
  public:
    Histogrammer(std::string& outFile);
    virtual ~Histogrammer();
    void bookEventHistograms();
    void bookDUTHistograms(std::string det);
    void bookDUTHistoForColumn(TString& d, TString c);
    void bookStubHistograms();
    void bookClusterCorrHistograms();
    void bookStubHistoForColumn(TString c);
    void bookCorrelationHistograms();
    void bookCorrelationHistoForColumn(TString c);
    template <class T>
    void fillHist1D(const char* dir, const char* histo, T val) {
      fout_->cd(dir);
      Utility::fillHist1D(histo, val);
    }
    template <class T>
    void fillHist1D(const std::string& dir, const std::string& histo, T val) {
      fillHist1D(dir.c_str(), histo.c_str(), val);
    }
    template <class T1, class T2>
    void fillHist2D(const char* dir, const char* histo, T1 xval, T2 yval) {
      fout_->cd(dir);
      Utility::fillHist2D(histo, xval, yval);
    }
    template <class T1, class T2>
    void fillHist2D(const std::string& dir, const std::string& histo, T1 xval, T2 yval) {
      fillHist2D(dir.c_str(), histo.c_str(), xval, yval);
    } 
 
    template <class T>
    void fillHistofromVec( const std::vector<T>& vec, const char* dir, const char* h) {
      fout_->cd(dir);
      Utility::fillHistofromVec( vec, h); 
    }
    template <class T1, class T2>
    void fill2DHistofromVec( const std::vector<T1>& vecC0, const std::vector<T2>& vecC1, 
                             const char* dir, const char* h) {
      fout_->cd(dir);
      Utility::fill2DHistofromVec( vecC0, vecC1,h);
     }
    
    void fillClusterHistograms( const char* det, std::vector<tbeam::cluster>& cvec, const char* col);
    void fillClusterCorrHistograms( std::vector<tbeam::cluster>& cvec0, std::vector<tbeam::cluster>& cvec1, const char* col);
    void closeFile();
    
    TFile* hfile() const { return fout_;}
  private:
    TFile* fout_;
    bool isFileopen_;  
};
#endif
