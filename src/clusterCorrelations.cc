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

using namespace CommandLineProcessing;

enum runType{VCTH,ANGLE};

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

  std::string inFilename = ( cmd.foundOption( "iFile" ) ) ? cmd.optionValue( "iFile" ) : "dummy.txt";
  
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
  string in;
  int voltage, stubWindow, vcth, rt;
  //runType rt;
  double angle;
  std::fstream inFile(inFilename);
  while(inFile >> in >> rt >> stubWindow >> vcth >> voltage){
	cout << "Running on file:" << in << endl;
  	cout << "Run data - type: " << rt << ", stub window: " << stubWindow << ", VCTH: " << vcth << ", bias voltage: " << voltage << endl;
	ClusterAnalysis r(in,outFilename);
	std::cout << "Event Loop start" << std::endl;
	r.eventLoop();
	r.endJob();
  }
  timer.Stop();
  cout << "Realtime/CpuTime = " << timer.RealTime() << "/" << timer.CpuTime() << endl;
  return 0;
}
