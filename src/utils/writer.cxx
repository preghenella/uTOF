#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include "dataFormat/Writer.h"

int
main(int argc, char **argv)
{

  /** options **/
  std::string inputFileName, outputFileName;
  
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help", "Print help messages")
    ("input,i", po::value<std::string>()->default_value("TOFcalibTree.root"), "Input TOFcalibTree file name")
    ("output,o", po::value<std::string>()->default_value("uTOFtree.root"), "Output uTOFtree file name")
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
    
    po::notify(vm);
  }
  catch(std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }
  
  uTOF::Writer writer(inputFileName, outputFileName);
  if (!writer.Process()) return 1;
  
  return 0;
}

