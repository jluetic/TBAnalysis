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

void graph_maker_multi_graph(){
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

///////////////////////////////
TCanvas *c3 = new TCanvas("c3","c3",600, 400);  
delta_cl_angle_600_4_110->SetMarkerColor(4);
delta_cl_angle_600_4_110->SetMarkerStyle(2);
delta_cl_angle_600_4_110->SetTitle("CW = 4");

delta_cl_angle_600_5_110->SetMarkerColor(2);
delta_cl_angle_600_5_110->SetMarkerStyle(2);
delta_cl_angle_600_5_110->SetTitle("CW = 5");

delta_cl_angle_600_6_110->SetMarkerColor(3);
delta_cl_angle_600_6_110->SetMarkerStyle(2);
delta_cl_angle_600_6_110->SetTitle("CW = 6");

TMultiGraph  *mg  = new TMultiGraph();
mg->Add(delta_cl_angle_600_4_110);
mg->Add(delta_cl_angle_600_5_110);
mg->Add(delta_cl_angle_600_6_110);
mg->Draw("AP");
mg->SetTitle("Delta Cluster Angular scan (Voltage = 600V, VCTH = 110)");
mg->GetXaxis()->SetTitle("Angle");
mg->GetYaxis()->SetTitle("mean Delta_{Cluster}");
mg->Draw("AP");
c3->BuildLegend();
//mg->Draw();
mg->Write("delta_cl_angle_600_110");

///////////////////////////////
TCanvas *c4 = new TCanvas("c4","c4",600, 400);  
delta_cl_angle_400_5_110->SetMarkerColor(4);
delta_cl_angle_400_5_110->SetMarkerStyle(2);
delta_cl_angle_400_5_110->SetTitle("Voltage = 400");

delta_cl_angle_900_5_110->SetMarkerColor(2);
delta_cl_angle_900_5_110->SetMarkerStyle(2);
delta_cl_angle_900_5_110->SetTitle("Voltage = 900");

TMultiGraph  *mg1  = new TMultiGraph();
mg1->Add(delta_cl_angle_400_5_110);
mg1->Add(delta_cl_angle_900_5_110);
mg1->Draw("AP");
mg1->SetTitle("Delta Cluster Angular scan (CW = 5, VCTH = 110)");
mg1->GetXaxis()->SetTitle("Angle");
mg1->GetYaxis()->SetTitle("mean Delta_{Cluster}");
mg1->Draw("AP");
c4->BuildLegend();
//mg->Draw();
mg1->Write("delta_cl_angle_5_110");

///////////////////////////////
TCanvas *c5 = new TCanvas("c5","c5",600, 400);  
delta_cl_vcth_600_5_0->SetMarkerColor(4);
delta_cl_vcth_600_5_0->SetMarkerStyle(2);
delta_cl_vcth_600_5_0->SetTitle("Angle = 0");

delta_cl_vcth_600_5_10->SetMarkerColor(2);
delta_cl_vcth_600_5_10->SetMarkerStyle(2);
delta_cl_vcth_600_5_10->SetTitle("Angle = 10");

TMultiGraph  *mg2  = new TMultiGraph();
mg2->Add(delta_cl_vcth_600_5_0);
mg2->Add(delta_cl_vcth_600_5_10);
mg2->Draw("AP");
mg2->SetTitle("Delta Cluster Threshold scan (Voltage = 600V, CW = 5)");
mg2->GetXaxis()->SetTitle("VCTH");
mg2->GetYaxis()->SetTitle("mean Delta_{Cluster}");
mg2->Draw("AP");
c5->BuildLegend();
//mg->Draw();
mg2->Write("delta_cl_vcth_600_5");

///////////////////////////////
TCanvas *c6 = new TCanvas("c6","c6",600, 400);  
delta_cl_vcth_600_7_0->SetMarkerColor(4);
delta_cl_vcth_600_7_0->SetMarkerStyle(2);
delta_cl_vcth_600_7_0->SetTitle("Angle = 0");

delta_cl_vcth_600_7_17->SetMarkerColor(2);
delta_cl_vcth_600_7_17->SetMarkerStyle(2);
delta_cl_vcth_600_7_17->SetTitle("Angle = 17");

TMultiGraph  *mg3  = new TMultiGraph();
mg3->Add(delta_cl_vcth_600_7_0);
mg3->Add(delta_cl_vcth_600_7_17);
mg3->Draw("AP");
mg3->SetTitle("Delta Cluster Threshold scan (Voltage = 600V, CW = 7)");
mg3->GetXaxis()->SetTitle("VCTH");
mg3->GetYaxis()->SetTitle("mean Delta_{Cluster}");
mg3->Draw("AP");
c6->BuildLegend();
//mg->Draw();
mg3->Write("delta_cl_vcth_600_7");

///////////////////////////////
TCanvas *c7 = new TCanvas("c7","c7",600, 400);  
delta_cl_vcth_400_5_0->SetMarkerColor(4);
delta_cl_vcth_400_5_0->SetMarkerStyle(2);
delta_cl_vcth_400_5_0->SetTitle("Voltage = 400");

delta_cl_vcth_900_5_0->SetMarkerColor(2);
delta_cl_vcth_900_5_0->SetMarkerStyle(2);
delta_cl_vcth_900_5_0->SetTitle("Voltage = 900");

TMultiGraph  *mg4  = new TMultiGraph();
mg4->Add(delta_cl_vcth_400_5_0);
mg4->Add(delta_cl_vcth_900_5_0);
mg4->Draw("AP");
mg4->SetTitle("Delta Cluster Threshold scan (CW = 5, angle = 0)");
mg4->GetXaxis()->SetTitle("VCTH");
mg4->GetYaxis()->SetTitle("mean Delta_{Cluster}");
mg4->Draw("AP");
c7->BuildLegend();
//mg->Draw();
mg4->Write("delta_cl_vcth_5_0");


}
