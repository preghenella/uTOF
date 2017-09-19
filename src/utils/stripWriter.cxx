#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include "dataFormat/StripWriter.h"
#include "TROOT.h"

int
main(int argc, char **argv)
{

  /** options **/
  std::string inputFileName, outputFileName;
  int strip, nThreads;
  
  namespace po = boost::program_options;
  po::options_description desc("Options");

  /** process arguments **/
  try {
    desc.add_options()
      ("help", "Print help messages")
      ("input,i", po::value<std::string>(&inputFileName)->default_value("uTOFtree.root"), "Input TOFcalibTree file name")
      ("output,o", po::value<std::string>(&outputFileName)->default_value("uTOFstrip.root"), "Output uTOFtree file name")
      ("strip,s", po::value<int>(&strip), "TOF strip index")
      ("nthreads,t", po::value<int>(&nThreads)->default_value(0), "Number of threads (0 = number of cores)")
      ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    
    /** help **/ 
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }

    if (!vm.count("strip")) {
      std::cout << "Strip is required" << std::endl;
      return 1;
    }
    
    po::notify(vm);
  }
  catch(std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }
  
  ROOT::EnableImplicitMT(nThreads);
  uTOF::StripWriter writer(strip, inputFileName, outputFileName);
  if (!writer.Process()) return 1;
  
  return 0;
}

