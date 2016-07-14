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

void graph_maker_ext(){
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
std::fstream inFile("processed_file_list.txt");
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
	//	cout << word << endl;
	}
	TFile* f = new TFile(("/afs/cern.ch/work/j/jluetic/public/TestBeam/Analysis/Results/"+file_name+".root").c_str());
	//cout << "1" << endl;
	TH1F *h = (TH1F*)gDirectory->Get("ClusterCorr/delta_clusterPos");
	//cout << "2" << endl;
//	h->Draw();
	double mean_delta_cl = h->GetMean();
	//cout << "3" << endl;
	cout << "mean from histo:   "<< mean_delta_cl << endl;
	if(wordVector[0] == "VCTH" && wordVector[2] == "600" && wordVector[4] == "7" && wordVector[3] == "0"){
		cout << "fill the VCTH vectors" << endl;	
		delta_VCTH_600_7_0.push_back(mean_delta_cl);
		vcth_VCTH_600_7_0.push_back(atof((wordVector[5]).c_str()));
	}
	else if(wordVector[0] == "VCTH" && wordVector[2] == "600" && wordVector[4] == "7" && wordVector[3] == "17"){
                delta_VCTH_600_7_17.push_back(mean_delta_cl);
                vcth_VCTH_600_7_17.push_back(atof((wordVector[5]).c_str()));
        }
	else if(wordVector[0] == "VCTH" && wordVector[2] == "600" && wordVector[4] == "5" && wordVector[3] == "10"){
                delta_VCTH_600_5_10.push_back(mean_delta_cl);
                vcth_VCTH_600_5_10.push_back(atof((wordVector[5]).c_str()));
        }
	else if(wordVector[0] == "VCTH" && wordVector[2] == "400" && wordVector[4] == "5" && wordVector[3] == "0"){
                delta_VCTH_400_5_0.push_back(mean_delta_cl);
                vcth_VCTH_400_5_0.push_back(atof((wordVector[5]).c_str()));
        }
	else if(wordVector[0] == "VCTH" && wordVector[2] == "900" && wordVector[4] == "5" && wordVector[3] == "0"){
                delta_VCTH_900_5_0.push_back(mean_delta_cl);
                vcth_VCTH_900_5_0.push_back(atof((wordVector[5]).c_str()));
        }
	else if(wordVector[0] == "VCTH" && wordVector[2] == "600" && wordVector[4] == "5" && wordVector[3] == "0"){
                delta_VCTH_600_5_0.push_back(mean_delta_cl);
                vcth_VCTH_600_5_0.push_back(atof((wordVector[5]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "600" && wordVector[4] == "5" && wordVector[5] == "110"){
        	cout << "do you fill the ANGLE vectors?" << endl;
	        delta_ANGLE_600_5_110.push_back(mean_delta_cl);
                volt_ANGLE_600_5_110.push_back(atof((wordVector[3]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "400" && wordVector[4] == "5" && wordVector[5] == "110"){
                delta_ANGLE_400_5_110.push_back(mean_delta_cl);
                volt_ANGLE_400_5_110.push_back(atof((wordVector[3]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "900" && wordVector[4] == "5" && wordVector[5] == "110"){
                delta_ANGLE_900_5_110.push_back(mean_delta_cl);
                volt_ANGLE_900_5_110.push_back(atof((wordVector[3]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "600" && wordVector[4] == "4" && wordVector[5] == "110"){
                delta_ANGLE_600_4_110.push_back(mean_delta_cl);
                volt_ANGLE_600_4_110.push_back(atof((wordVector[3]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "600" && wordVector[4] == "6" && wordVector[5] == "110"){
                delta_ANGLE_600_6_110.push_back(mean_delta_cl);
                volt_ANGLE_600_6_110.push_back(TMath::Abs(atof((wordVector[3]).c_str())));
        }
	else if(wordVector[0] == "VCTH" && wordVector[2] == "250" && wordVector[4] == "3" && wordVector[5] == "0"){
                delta_VCTH_250_3_0.push_back(mean_delta_cl);
                vcth_VCTH_250_3_0.push_back(atof((wordVector[3]).c_str()));
        }
	else if(wordVector[0] == "ANGLE" && wordVector[2] == "250" && wordVector[4] == "5" && wordVector[5] == "106"){
                delta_ANGLE_250_5_106.push_back(mean_delta_cl);
                volt_ANGLE_250_5_106.push_back(atof((wordVector[3]).c_str()));
        }	
}

TFile *graph_results = new TFile( "Results/graph_results.root","RECREATE");
graph_results->cd();
/*TCanvas *c1 = new TCanvas("ex_graph","ex_graph",200,10,700,500);
c1->SetFillColor(42);
c1->SetGrid();
c1->Update();
c1->GetFrame()->SetFillColor(21);
c1->GetFrame()->SetBorderSize(12);
c1->Modified();*/

TGraph *delta_cl_vcth_600_7_0 = new TGraph(delta_VCTH_600_7_0.size(), &vcth_VCTH_600_7_0[0], &delta_VCTH_600_7_0[0]);
delta_cl_vcth_600_7_0->SetMarkerColor(4);
delta_cl_vcth_600_7_0->SetMarkerStyle(21);
delta_cl_vcth_600_7_0->SetTitle("Delta cluster VCTH scan (Voltage = 600, CW = 7, angle = 0)");
delta_cl_vcth_600_7_0->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_600_7_0->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_600_7_0->SetLineColor(0);
delta_cl_vcth_600_7_0->Draw();
delta_cl_vcth_600_7_0->Write();

TGraph *delta_cl_vcth_600_7_17 = new TGraph(delta_VCTH_600_7_17.size(), &vcth_VCTH_600_7_17[0], &delta_VCTH_600_7_17[0]);
delta_cl_vcth_600_7_17->SetMarkerColor(4);
delta_cl_vcth_600_7_17->SetMarkerStyle(21);
delta_cl_vcth_600_7_17->SetTitle("Delta cluster VCTH scan (Voltage = 600, CW = 7, angle = 17)");
delta_cl_vcth_600_7_17->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_600_7_17->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_600_7_17->SetLineColor(0);
delta_cl_vcth_600_7_17->Draw();
delta_cl_vcth_600_7_17->Write();

TGraph *delta_cl_vcth_600_5_10 = new TGraph(delta_VCTH_600_5_10.size(), &vcth_VCTH_600_5_10[0], &delta_VCTH_600_5_10[0]);
delta_cl_vcth_600_5_10->SetMarkerColor(4);
delta_cl_vcth_600_5_10->SetMarkerStyle(21);
delta_cl_vcth_600_5_10->SetTitle("Delta cluster VCTH scan (Voltage = 600, CW = 5, angle = 10)");
delta_cl_vcth_600_5_10->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_600_5_10->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_600_5_10->SetLineColor(0);
delta_cl_vcth_600_5_10->Draw();
delta_cl_vcth_600_5_10->Write();

TGraph *delta_cl_vcth_400_5_0 = new TGraph(delta_VCTH_400_5_0.size(), &vcth_VCTH_400_5_0[0], &delta_VCTH_400_5_0[0]);
delta_cl_vcth_400_5_0->SetMarkerColor(4);
delta_cl_vcth_400_5_0->SetMarkerStyle(21);
delta_cl_vcth_400_5_0->SetTitle("Delta cluster VCTH scan (Voltage = 400, CW = 5, angle = 0)");
delta_cl_vcth_400_5_0->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_400_5_0->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_400_5_0->SetLineColor(0);
delta_cl_vcth_400_5_0->Draw();
delta_cl_vcth_400_5_0->Write();


TGraph *delta_cl_vcth_900_5_0 = new TGraph(delta_VCTH_900_5_0.size(), &vcth_VCTH_900_5_0[0], &delta_VCTH_900_5_0[0]);
delta_cl_vcth_900_5_0->SetMarkerColor(4);
delta_cl_vcth_900_5_0->SetMarkerStyle(21);
delta_cl_vcth_900_5_0->SetTitle("Delta cluster VCTH scan (Voltage = 900, CW = 5, angle = 0)");
delta_cl_vcth_900_5_0->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_900_5_0->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_900_5_0->SetLineColor(0);
delta_cl_vcth_900_5_0->Draw();
delta_cl_vcth_900_5_0->Write();


TGraph *delta_cl_vcth_600_5_0 = new TGraph(delta_VCTH_600_5_0.size(), &vcth_VCTH_600_5_0[0], &delta_VCTH_600_5_0[0]);
delta_cl_vcth_600_5_0->SetMarkerColor(4);
delta_cl_vcth_600_5_0->SetMarkerStyle(21);
delta_cl_vcth_600_5_0->SetTitle("Delta cluster VCTH scan (Voltage = 600, CW = 5, angle = 0)");
delta_cl_vcth_600_5_0->GetXaxis()->SetTitle("VCTH");
delta_cl_vcth_600_5_0->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_vcth_600_5_0->SetLineColor(0);
delta_cl_vcth_600_5_0->Draw();
delta_cl_vcth_600_5_0->Write();


TGraph *delta_cl_angle_600_5_110 = new TGraph(delta_ANGLE_600_5_110.size(), &volt_ANGLE_600_5_110[0], &delta_ANGLE_600_5_110[0]);
delta_cl_angle_600_5_110->SetMarkerColor(4);
delta_cl_angle_600_5_110->SetMarkerStyle(21);
delta_cl_angle_600_5_110->SetTitle("Delta cluster ANGLE scan (Voltage = 600, CW = 5, VCTH = 110)");
delta_cl_angle_600_5_110->GetXaxis()->SetTitle("angle");
delta_cl_angle_600_5_110->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_angle_600_5_110->SetLineColor(0);
delta_cl_angle_600_5_110->Draw();
delta_cl_angle_600_5_110->Write();

TGraph *delta_cl_angle_400_5_110 = new TGraph(delta_ANGLE_400_5_110.size(), &volt_ANGLE_400_5_110[0], &delta_ANGLE_400_5_110[0]);
delta_cl_angle_400_5_110->SetMarkerColor(4);
delta_cl_angle_400_5_110->SetMarkerStyle(21);
delta_cl_angle_400_5_110->SetTitle("Delta cluster ANGLE scan (Voltage = 400, CW = 5, VCTH = 110)");
delta_cl_angle_400_5_110->GetXaxis()->SetTitle("angle");
delta_cl_angle_400_5_110->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_angle_400_5_110->SetLineColor(0);
delta_cl_angle_400_5_110->Draw();
delta_cl_angle_400_5_110->Write();

TGraph *delta_cl_angle_900_5_110 = new TGraph(delta_ANGLE_900_5_110.size(), &volt_ANGLE_900_5_110[0], &delta_ANGLE_900_5_110[0]);
delta_cl_angle_900_5_110->SetMarkerColor(4);
delta_cl_angle_900_5_110->SetMarkerStyle(21);
delta_cl_angle_900_5_110->SetTitle("Delta cluster ANGLE scan (Voltage = 900, CW = 5, VCTH = 110)");
delta_cl_angle_900_5_110->GetXaxis()->SetTitle("angle");
delta_cl_angle_900_5_110->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_angle_900_5_110->SetLineColor(0);
delta_cl_angle_900_5_110->Draw();
delta_cl_angle_900_5_110->Write();

TGraph *delta_cl_angle_600_4_110 = new TGraph(delta_ANGLE_600_4_110.size(), &volt_ANGLE_600_4_110[0], &delta_ANGLE_600_4_110[0]);
delta_cl_angle_600_4_110->SetMarkerColor(4);
delta_cl_angle_600_4_110->SetMarkerStyle(21);
delta_cl_angle_600_4_110->SetTitle("Delta cluster ANGLE scan (Voltage = 600, CW = 4, VCTH = 110)");
delta_cl_angle_600_4_110->GetXaxis()->SetTitle("angle");
delta_cl_angle_600_4_110->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_angle_600_4_110->SetLineColor(0);
delta_cl_angle_600_4_110->Draw();
delta_cl_angle_600_4_110->Write();

TGraph *delta_cl_angle_600_6_110 = new TGraph(delta_ANGLE_600_6_110.size(), &volt_ANGLE_600_6_110[0], &delta_ANGLE_600_6_110[0]);
delta_cl_angle_600_6_110->SetMarkerColor(4);
delta_cl_angle_600_6_110->SetMarkerStyle(21);
delta_cl_angle_600_6_110->SetTitle("Delta cluster ANGLE scan (Voltage = 600, CW = 6, VCTH = 110)");
delta_cl_angle_600_6_110->GetXaxis()->SetTitle("angle");
delta_cl_angle_600_6_110->GetYaxis()->SetTitle("mean Delta_{Cluster}");
delta_cl_angle_600_6_110->SetLineColor(0);
delta_cl_angle_600_6_110->Draw();
delta_cl_angle_600_6_110->Write();
}
