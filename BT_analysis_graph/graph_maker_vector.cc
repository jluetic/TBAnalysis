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
#include <string>
using namespace std;

void graph_maker_vector(){
	//vector of vector containing all the data: <<0=VCTH/1=ANGLE,voltage,CW,Angle/VCTH>,<VCTH1/ANGLE1,VCTH2/ANGLE2,...>,<delta_cl1, delta_cl2,...>>
	//multigraph_chooser lets you choose wich of the multigraps you would like to display
	//number_of_multi_graphs is the total number of multigraphs that will be made
	//nr_of_vectors is the number of different kinds of vectors that are in delta_cl_size_irr. This is 1) a vector with info on the run 2) a vector with VCTH or ANGLE values 3) a vector with delta_cl values 4) the error on delta_cl
	int multigraph_chooser = 4;
	int number_of_multi_graphs = 5;
        int nr_of_vectors = 4;
	int start_angular_mg = 3;
	double angle_offset_setting = 5;
	vector<vector<double> > delta_cl_size_irr;
	TMultiGraph *mg_array[number_of_multi_graphs];
	TCanvas *canvas_array[number_of_multi_graphs];
	TLegend *leg_array[number_of_multi_graphs];
	int colour[number_of_multi_graphs];
	string file_name;
	//the loop will run over all the files that are defined in the .txt file below. These is typically just an ls of all that is in the Results directory after running ./clusterCorrelations
	std::fstream inFile("processed_file_list_130716.txt");
	//loop over the root files which are defined in processed_file_list.txt
	while(inFile >> file_name){
		size_t lastindex = file_name.find_last_of("."); 
		file_name = file_name.substr(0, lastindex);
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "file name:  " << file_name << endl;
		std::stringstream stringStream(file_name);
		std::string word;
		vector <string> wordVector;
		//get the info which is in the filename
		while(std::getline(stringStream, word, '_')) 
		{
				wordVector.push_back(word);
		}
		TFile* f = new TFile(("/afs/cern.ch/user/j/jdeclerc/public/Analysis/Results130716/"+file_name+".root").c_str());
	//	TFile* f = new TFile(("/afs/cern.ch/user/j/jdeclerc/public/Analysis/Results_050716/Results/"+file_name+".root").c_str());
		TH1F *h = (TH1F*)gDirectory->Get("ClusterCorr/delta_clusterPos");
		//get the mean of the delta_cl_size
		double mean_delta_cl = h->GetMean();
		double std_dev_mean_delta_cl = h -> GetStdDevError();
		// get the angle and vcth from the condition data in the root file
		TH1F *h1 = (TH1F*)gDirectory->Get("EventInfo/dutAngle");
		double angle_from_cond = h1->GetMean();
		TH1F *h2 = (TH1F*)gDirectory->Get("EventInfo/vcth");
                double vcth_from_cond = h2->GetMean();
		//cout << "mean delta_cl from histo:   "<< mean_delta_cl << endl;
		//cout << "standard deviation delta_cl:   "<< std_dev_mean_delta_cl << endl;	
		//get the info that is in the root filename name
		//there are two type of runs: type 1 = ANGLE, type 0 = VCTH. 
		double type_scan = 1;
		//cout << "wordvector0 " << wordVector[0] << endl;
		if(wordVector[0] == "VCTH"){
			type_scan = 0;
		}
		//get the run info from the name of the file (this is from the elog)
		double run_nr = atof(wordVector[1].c_str());
		double voltage = atof(wordVector[2].c_str());
		double angle = TMath::Abs(atof(wordVector[3].c_str()));
		double cw = atof(wordVector[4].c_str());
		double vcth = 	atof(wordVector[5].c_str());
		double angle_elog_original = angle; 
		//use the angle that is closest to the expected angle (calculating backward from the measured delta strip (formula: see the google doc from the measurment programme))
		
		if(vcth!=vcth_from_cond){cout << "There is a difference in vcth between elog and cond data. elog: " << vcth << " cond data: " << vcth_from_cond << " the difference is: " << vcth - vcth_from_cond << endl;}
		if(angle!=angle_from_cond){cout << "There is a difference in angle between elog and cond data. elog: " << angle << " cond data: " << angle_from_cond << " the difference is: " << angle - angle_from_cond << endl;}

		double angle_expected = 17*180/(20.08*TMath::Pi())*TMath::ATan(mean_delta_cl*0.09/2.5);
                double diff_elog = TMath::Abs(angle_expected-angle);
                double diff_cond = TMath::Abs(angle_expected-angle_from_cond);
		cout << "angle elog:  " << angle << endl;
		cout << "angle cond:  " << angle_from_cond << endl;
		cout << "angle expected:  " << angle_expected << endl;
        //        if(diff_elog>diff_cond){cout << "change angle to cond_angle" << endl; angle=angle_from_cond;}
		if (TMath::Abs(angle-angle_expected)>4){angle=angle+angle_offset_setting; cout << "angle offset is used" << endl;}
		bool setting_encountered = false;
		//if the setting has already been encountered you can add the value for the VCTH/ANGLE, delta_cl_size, error_delta_cl_size to the subsequent, subsequent subsequent and subsequent subsequent subsequent vector.
		for(int vec = 0; vec< (int)delta_cl_size_irr.size(); vec = vec +nr_of_vectors){
			if (delta_cl_size_irr[vec][0] == 0  && delta_cl_size_irr[vec][1] == voltage && delta_cl_size_irr[vec][2] == cw && delta_cl_size_irr[vec][3] == angle_elog_original){
				cout << "value encountered" << endl;
				setting_encountered = true;
				delta_cl_size_irr[vec+1].push_back(vcth);
				delta_cl_size_irr[vec+2].push_back(mean_delta_cl);
				delta_cl_size_irr[vec+3].push_back(std_dev_mean_delta_cl);	
			}
			if (delta_cl_size_irr[vec][0] == 1  && delta_cl_size_irr[vec][1] == voltage && delta_cl_size_irr[vec][2] == cw && delta_cl_size_irr[vec][3] == vcth){
                                cout << "value encountered" << endl;
                                setting_encountered = true;
                                delta_cl_size_irr[vec+1].push_back(TMath::Abs(angle));
                                delta_cl_size_irr[vec+2].push_back(mean_delta_cl);
				delta_cl_size_irr[vec+3].push_back(std_dev_mean_delta_cl);
                        }
		}
		//if the settings have not yet been encountered create a new vector with these settings and the respective vectors for ANGLE/VCTH, delta_cl and error_delta_cl
		if (!setting_encountered){
			delta_cl_size_irr.push_back(vector<double>());
                        delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(type_scan);
                        delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(voltage);
                        delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(cw);
			if(type_scan == 0){
				delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(angle_elog_original);
                       		delta_cl_size_irr.push_back(vector<double>());
				delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(vcth);
				cout << "vcth   " << vcth << endl;
			}
			if(type_scan == 1){
                                delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(vcth);
                        	delta_cl_size_irr.push_back(vector<double>());
				delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(TMath::Abs(angle));
                        	cout << "angle  " << angle << endl; 
			}
			delta_cl_size_irr.push_back(vector<double>());
                        delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(mean_delta_cl);
                        cout << "mean_delta_cl   " << mean_delta_cl << endl;  
			delta_cl_size_irr.push_back(vector<double>());
                        delta_cl_size_irr[(int)delta_cl_size_irr.size()-1].push_back(std_dev_mean_delta_cl);	
			cout << "std_dev_mean_delta_cl  " << std_dev_mean_delta_cl << endl;				
		}	
	}
	
	//start miaking the graphs
	TFile *graph_results = new TFile( "Results/graph_results.root","RECREATE");
	graph_results->cd();
	canvas_array[0]= new TCanvas("c1","Delta Cluster VCTH scan (Voltage = 600V, cw = 5)",600,500);
	canvas_array[1]= new TCanvas("c2","Delta Cluster VCTH scan (Voltage = 600V, cw = 7)",600,500);
	canvas_array[2]= new TCanvas("c3","Delta Cluster VCTH scan (cw = 5, angle = 0)",600,500);
	canvas_array[3]= new TCanvas("c4","Delta Cluster Angular scan (Voltage = 600V, VCTH = 110)",600,500);
	canvas_array[4]= new TCanvas("c5","Delta Cluster Angular scan (cw = 5)",600,500);

	for(int nr_mg = 0; nr_mg<number_of_multi_graphs; nr_mg++){	
		mg_array[nr_mg] = new TMultiGraph();
		leg_array[nr_mg] = new TLegend(0.1,0.7,0.48,0.9);
		colour[nr_mg]=2;
	}
	

	for(int i = 0; i< (int)delta_cl_size_irr.size(); i = i+4 ){
		//make a graph for every run
		TGraph *temp_graph = new TGraphErrors(delta_cl_size_irr[i+1].size(), &delta_cl_size_irr[i+1][0], &delta_cl_size_irr[i+2][0],0,&delta_cl_size_irr[i+3][0]);
		temp_graph->SetMarkerColor(4);
		temp_graph->SetMarkerStyle(7);
		string type = "VCTH";
		temp_graph->GetXaxis()->SetTitle("VCTH");
                if(delta_cl_size_irr[i][0]==1){
                        type = "ANGLE";
                        temp_graph->GetXaxis()->SetTitle("ANGLE");
                }
		char buffer[100];
		if(type == "VCTH"){
  			snprintf ( buffer, 100, "Delta cluster for VCTH scan (Voltage = %d, CW = %d, angle = %d)", (int)delta_cl_size_irr[i][1],(int)delta_cl_size_irr[i][2],(int)delta_cl_size_irr[i][3] );
			temp_graph->GetXaxis()->SetTitle("VCTH");
		}
		if(type == "ANGLE"){
			snprintf ( buffer, 100, "Delta cluster for ANGLE scan (Voltage = %d, CW = %d, vcth = %d)", (int)delta_cl_size_irr[i][1],(int)delta_cl_size_irr[i][2],(int)delta_cl_size_irr[i][3] );
			temp_graph->GetXaxis()->SetTitle("ANGLE");
		}
		temp_graph->SetName(buffer);
		temp_graph->SetTitle(buffer);
		temp_graph->GetYaxis()->SetTitle("mean #Delta_{Cluster}");
		temp_graph->Draw("AEP");
		temp_graph->Write(buffer);
		
		//for the multigraphs, here you combine the graphs made in the previous section to a multigraph depending on the if selection criteria

		temp_graph->SetMarkerStyle(8);

		if(delta_cl_size_irr[i][0] == 0 && delta_cl_size_irr[i][1] == 600 && delta_cl_size_irr[i][2]==5 ){
			temp_graph->SetMarkerColor(colour[0]);
			temp_graph->SetLineColor(colour[0]);
			colour[0]++;
			mg_array[0]->Add(temp_graph);
			leg_array[0]->AddEntry(buffer,buffer,"lep");
		}
		if(delta_cl_size_irr[i][0] == 0 && delta_cl_size_irr[i][1] == 600 && delta_cl_size_irr[i][2]==7){
			temp_graph->SetMarkerColor(colour[1]);
                        temp_graph->SetLineColor(colour[1]);
			colour[1]++;
			mg_array[1]->Add(temp_graph);
			leg_array[1]->AddEntry(buffer,buffer,"lep");
		}
		if(delta_cl_size_irr[i][0] == 0 && delta_cl_size_irr[i][2]==5 && delta_cl_size_irr[i][3]==0  ){
			temp_graph->SetMarkerColor(colour[2]);
                	temp_graph->SetLineColor(colour[2]); 
		        colour[2]++;
			mg_array[2]->Add(temp_graph);
			leg_array[2]->AddEntry(buffer,buffer,"lep");
		}
		if(delta_cl_size_irr[i][0] == 1 && delta_cl_size_irr[i][1] == 600 && delta_cl_size_irr[i][3]==110){
			temp_graph->SetMarkerColor(colour[3]);
			temp_graph->SetLineColor(colour[3]);
			colour[3]++;
			mg_array[3]->Add(temp_graph);
			leg_array[3]->AddEntry(buffer,buffer,"lep");
		}
		if(delta_cl_size_irr[i][0] == 1  && delta_cl_size_irr[i][2]==5){
			temp_graph->SetMarkerColor(colour[4]);
			temp_graph->SetLineColor(colour[4]);
                        colour[4]++;			
			mg_array[4]->Add(temp_graph);
			leg_array[4]->AddEntry(buffer,buffer,"lep");
		}
	}

//	mg_array[0]->GetXaxis()->SetTitle("vcth");
  //      mg_array[0]->GetYaxis()->SetTitle("mean Delta_{Cluster}");
        mg_array[0]->SetTitle("Delta Cluster VCTH scan (Voltage = 600V, cw = 5)");
	mg_array[1]->SetTitle("Delta Cluster VCTH scan (Voltage = 600V, cw = 7)");
        mg_array[2]->SetTitle("Delta Cluster VCTH scan (cw = 5, angle = 0)");
        mg_array[3]->SetTitle("Delta Cluster Angular scan (Voltage = 600V, VCTH = 110)");
        mg_array[4]->SetTitle("Delta Cluster Angular scan (cw = 5)");

	for(int nr_mg = 0; nr_mg<number_of_multi_graphs; nr_mg++){
		if(nr_mg != multigraph_chooser) continue;    
		mg_array[nr_mg]->Draw("AEP");
		cout << "drawing!!" << endl;
		if(nr_mg<start_angular_mg){
			mg_array[nr_mg]->GetXaxis()->SetTitle("VCTH");
		}	
		if(nr_mg>=start_angular_mg){
			mg_array[nr_mg]->GetXaxis()->SetTitle("Angle");
		}
		mg_array[nr_mg]->GetYaxis()->SetTitle("mean Delta_{Cluster}");
//         	gPad->Modified(); gPad->Update();
		mg_array[nr_mg]->Draw("AEP");
		//canvas_array[nr_mg]->BuildLegend();
		leg_array[nr_mg]->SetFillColor(kWhite);
		leg_array[nr_mg]->Draw();
	//	leg_array[nr_mg]->Write();
		//mg_array[nr_mg]->Draw("AEP");
	//	canvas_array[nr_mg]->Print("plots.pdf","Title");
	}
	mg_array[0]->Write("Delta Cluster VCTH scan (Voltage = 600V, cw = 5)");
	leg_array[0]->Write();
	mg_array[1]->Write("Delta Cluster VCTH scan (Voltage = 600V, cw = 7)");
	leg_array[1]->Write();
	mg_array[2]->Write("Delta Cluster VCTH scan (cw = 5, angle = 0)");
	leg_array[2]->Write();
	mg_array[3]->Write("Delta Cluster Angular scan (Voltage = 600V, VCTH = 110)");
	leg_array[3]->Write();
	mg_array[4]->Write("Delta Cluster Angular scan (cw = 5)");
	leg_array[4]->Write();
	//return canvas_array;
}

