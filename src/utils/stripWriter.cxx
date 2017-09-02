#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include "dataFormat/StripWriter.h"

int
main(int argc, char **argv)
{

  /** options **/
  std::string inputFileName, outputFileName;
  int strip;
  
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help", "Print help messages")
    ("input,i", po::value<std::string>()->default_value("uTOFtree.root"), "Input TOFcalibTree file name")
    ("output,o", po::value<std::string>()->default_value("uTOFstrip.root"), "Output uTOFtree file name")
    ("strip,s", po::value<int>()->required(), "TOF strip index")
    ;
  
  /** process arguments **/
  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    
    /** help **/ 
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }
    
    if (vm.count("input"))  inputFileName  = vm["input"].as<std::string>();
    if (vm.count("output")) outputFileName = vm["output"].as<std::string>();
    if (vm.count("strip"))  strip          = vm["strip"].as<int>();
    
    po::notify(vm);
  }
  catch(std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }
  
  uTOF::StripWriter writer(strip, inputFileName, outputFileName);
  if (!writer.Process()) return 1;
  
  return 0;
}

