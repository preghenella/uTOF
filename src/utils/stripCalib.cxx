#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include "dataFormat/Channel.h"
#include "calibration/Channel.h"
#include "TFile.h"
#include "TTree.h"
#include "TBenchmark.h"

int
main(int argc, char **argv)
{

  /** options **/
  std::string inputFileName, outputFileName;
  
  namespace po = boost::program_options;
  po::options_description desc("Options");

  /** process arguments **/
  try {
    desc.add_options()
      ("help", "Print help messages")
      ("input,i", po::value<std::string>(&inputFileName)->default_value("uTOFstrip.root"), "Input uTOFstrip file name")
      ("output,o", po::value<std::string>(&outputFileName)->default_value("uTOFcalib.root"), "Output uTOFcalib file name")
      ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    
    /** help **/ 
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }

    po::notify(vm);
  }
  catch(std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }
  
  auto fin = TFile::Open(inputFileName.c_str());
  auto tin = (TTree *)fin->Get("uTOFstrip");
  auto fout = TFile::Open(outputFileName.c_str(), "RECREATE");

  auto channel = new uTOF::Channel();
  TBenchmark bench;
  bench.Start("process");
  for (int ich = 0; ich < 96; ich++) {
    tin->SetBranchAddress("channel", &channel);
    tin->GetEntry(ich);
    auto index = channel->getIndex();
    auto calibChannel = new uTOF::calib::Channel(index);
    std::cout << "Calibrating channel #" << index << std::endl;
    calibChannel->process(tin);
    calibChannel->write(fout);
    delete calibChannel;
  }
  bench.Stop("process");
  bench.Print("process");
  
  return 0;
}

