#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TString.h>
#include <TLegend.h>
#include "TLegendEntry.h"
#include "TH1.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include <TObjArray.h>
#include <TString.h>
#include <vector>
#include "TF2.h"
#include "TH2.h"
#include <fstream>
#include <TGraph.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <iostream>
using namespace std;

void graph_maker(){
//VCTH scans irr module
vector <double> delta_VCTH_600_7_0;
vector <double> vcth_VCTH_600_7_0;
vector <double> delta_VCTH_600_7_17;
vector <double> vcth_VCTH_600_7_17;
vector <double> delta_VCTH_600_5_10;
vector <double> vcth_VCTH_600_5_10;
vector <double> delta_VCTH_400_5_0;
vector <double> vcth_VCTH_400_5_0;
vector <double> delta_VCTH_900_5_0;
vector <double> vcth_VCTH_900_5_0;
vector <double> delta_VCTH_600_5_0;
vector <double> vcth_VCTH_600_5_0;

//angular scans irr module
vector <double> delta_ANGLE_600_5_110;
vector <double> volt_ANGLE_600_5_110;
vector <double> delta_ANGLE_400_5_110;
vector <double> volt_ANGLE_400_5_110;
vector <double> delta_ANGLE_900_5_110;
vector <double> volt_ANGLE_900_5_110;
vector <double> delta_ANGLE_600_4_110;
vector <double> volt_ANGLE_600_4_110;
vector <double> delta_ANGLE_600_6_110;
vector <double> volt_ANGLE_600_6_110;

//VCTH scan cnm module
vector <double> delta_VCTH_250_3_0;
vector <double> vcth_VCTH_250_3_0;

//angular scans cnm module
vector <double> delta_ANGLE_250_5_106;
vector <double> volt_ANGLE_250_5_106;
string file_name;
std::fstream inFile("processed_file_list_some_lines_deleted.txt");
while(inFile >> file_name){
	size_t lastindex = file_name.find_last_of("."); 
	file_name = file_name.substr(0, lastindex);
	cout << "file name:  " << file_name << endl;
	std::stringstream stringStream(file_name);
	std::string word;
	vector <string> wordVector;
	while(std::getline(stringStream, word, '_')) 
	{
    		wordVector.push_back(word);
		cout << word << endl;
	}
	TFile* f = new TFile(("/afs/cern.ch/work/j/jluetic/public/TestBeam/Analysis/Results/"+file_name+".root").c_str());
	cout << "1" << endl;
	TH1F *h = (TH1F*)gDirectory->Get("ClusterCorr/delta_clusterPos");
	cout << "2" << endl;
//	h->Draw();
	double mean_delta_cl = h->GetMean();
	cout << "3" << endl;
	cout << "mean from histo:   "<< mean_delta_cl << endl;
	if(wordVector[0] == "VCTH" && wordVector[2] == "600" && wordVector[3] == "0" && wordVector[4] == "7"){
//		cout << h->GetMean() << endl;
		cout << "conditions are met" << endl;
		delta_VCTH_600_7_0.push_back(mean_delta_cl);
		cout << 2 << endl;
		vcth_VCTH_600_7_0.push_back(atof((wordVector[5]).c_str()));
		cout << 3 << endl;
		cout << h->GetMean() << "   " << wordVector[5] << endl;
		continue;
	}
}

}
