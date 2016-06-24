#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "TROOT.h"
#include "TStopwatch.h"
#include "ClusterAnalysis.h"
//#include "ReconstructionFromRaw.h"
#include "argvparser.h"
using std::cout;
using std::cerr;
using std::endl;
using std::to_string;

using namespace CommandLineProcessing;

enum runType{VCTH,ANGLE};
typedef struct{
	string type;
	string inFile;
	string angle;
	int EDMRun, telescopeRun; 
	int vcth, biasVoltage, stubWindow, DAQRun;
} runInfo;


int main( int argc,char* argv[] ){
   
  ArgvParser cmd;
  cmd.setIntroductoryDescription( "Cluster correlations analysis for beam test data" );
  cmd.setHelpOption( "h", "help", "Print this help page" );
  cmd.addErrorCode( 0, "Success" );
  cmd.addErrorCode( 1, "Error" );
  cmd.defineOption( "iFile", "Input Tree name", ArgvParser::OptionRequiresValue);
  cmd.defineOption( "oFile", "Output file name", ArgvParser::OptionRequiresValue);  
  int result = cmd.parse( argc, argv );
  if (result != ArgvParser::NoParserError)
  {
    cout << cmd.parseErrorDescription(result);
    exit(1);
  }

  std::string inFilename = ( cmd.foundOption( "iFile" ) ) ? cmd.optionValue( "iFile" ) : "runlists/run_list_irr_module.txt";
  
  if ( inFilename.empty() ) {
    std::cerr << "Error, no input file provided. Quitting" << std::endl;
    exit( 1 );
  }

  std::string outFilename = ( cmd.foundOption( "oFile" ) ) ? cmd.optionValue( "oFile" ) : "test.root";
  if ( outFilename.empty() ) {
    std::cerr << "Error, no output filename provided. Quitting" << std::endl;
    exit( 1 );
  }
  //Let's roll
  TStopwatch timer;
  timer.Start();

  //Read the txt file
  runInfo rInfo;
  std::fstream inFile(inFilename);
  if (!inFile.good()) {
  	cout << "Input file not good." << endl;
	exit(1);
  }

  while(inFile >> rInfo.type >> rInfo.inFile >> rInfo.EDMRun >> rInfo.telescopeRun >> rInfo.angle >> std::hex >> rInfo.vcth >> std::dec >> rInfo.biasVoltage >> rInfo.stubWindow >> rInfo.DAQRun){
	cout << "Running on file:" << rInfo.inFile << endl;
  	cout << "Run data -> type: " << rInfo.type << ", EDM: " << rInfo.EDMRun << ", stub window: " << rInfo.stubWindow << ", VCTH: " << rInfo.vcth << ", bias voltage: " << rInfo.biasVoltage << ", Telescope run: " << rInfo.telescopeRun << ", DAQ run: " << rInfo.DAQRun << endl;
	outFilename = "Results/"+rInfo.type+"_"+to_string(rInfo.EDMRun)+"_"+to_string(rInfo.biasVoltage)+"_"+rInfo.angle+"_"+to_string(rInfo.stubWindow)+"_"+to_string(rInfo.vcth)+".root";	
	cout << outFilename << endl;
	ClusterAnalysis r("root://eoscms//eos/cms/store/group/upgrade/Tracker/TestBeam/BTMay2016/AnalysisTuple/"+rInfo.inFile,outFilename);
	std::cout << "Event Loop start" << std::endl;
	r.eventLoop();
	r.endJob();
  }
  timer.Stop();
  cout << "Realtime/CpuTime = " << timer.RealTime() << "/" << timer.CpuTime() << endl;
  return 0;
}
