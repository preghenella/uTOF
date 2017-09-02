#include "StripWriter.h"
#include "Channel.h"
#include "Hit.h"
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

namespace uTOF {

  StripWriter::StripWriter() :
    mInputFileName(), mOutputFileName()
  {}

  StripWriter::StripWriter(int aStripIndex, std::string aInputFileName, std::string aOutputFileName) :
    mStripIndex(aStripIndex), mInputFileName(aInputFileName), mOutputFileName(aOutputFileName)
  {}

  StripWriter::~StripWriter()
  {
  }

  bool
  StripWriter::Process()
  {
    
    /** open input **/
    TFile *fin = TFile::Open(mInputFileName.c_str());
    if (!fin || !fin->IsOpen()) {
      std::cerr << "Cannot open input file: " << mInputFileName << std::endl;
      return false;
    }
    TTree *tin = (TTree *)fin->Get("uTOFtree");
    if (!tin) {
      std::cerr << "Cannot find \"uTOFtree\" in input file: " << mInputFileName << std::endl;
      return false;
    }
    std::cout << "Processing input file: " << mInputFileName << std::endl;
    Channel *channelIn = new Channel();
    tin->SetBranchAddress("channel", &channelIn);
    
    /** open output **/
    TFile *fout = TFile::Open(mOutputFileName.c_str(), "RECREATE");
    if (!fout || !fout->IsOpen()) {
      std::cerr << "Cannot open output file: " << mOutputFileName << std::endl;
      return false;
    }
    TTree *tout = new TTree("uTOFstrip", ""); 
    Channel *channel = new Channel();
    tout->Branch("channel", "uTOF::Channel", &channel); 
    
    /** create channels **/
    int stripOffset = mStripIndex * kNumberOfStripChannels;
    std::vector<Channel *> channels;
    for (int ich = 0; ich < kNumberOfStripChannels; ich++)
      channels.push_back(new Channel(stripOffset + ich));
    
    /** loop over input tree **/
    long nev = tin->GetEntries();
    long totalHits = 0, partialHits = 0;
    std::cout << "Start processing input tree: " << nev << " entries found" << std::endl;
    for (int iev = 0; iev < nev; iev += kNumberOfChannels) {

      /** increment strip offset **/
      stripOffset += iev;
      
      /** loop over strip channels **/
      for (int ich = 0; ich < kNumberOfStripChannels; ich++) {

	/** get entry **/
	tin->GetEntry(stripOffset + ich);

	/** add hits to channel **/
	channels[ich]->addHits(channelIn);
	totalHits += channelIn->getNumberOfHits();
	
      } /** end of loop over strip channels **/

      /** partial fill output tree **/
      if (partialHits > 15724800) {
	partialHits = 0;
	std::cout << "Partial fill of \"uTOFstrip\" tree: totalHits = " << totalHits << " (at event #" << iev << ")" << std::endl;
	for (Int_t ich = 0; ich < kNumberOfStripChannels; ich++) {
	  channel = channels.at(ich);
	  tout->Fill();
	  channel->clear();
	}
      }

    } /** and of loop over input tree **/

    /** final fill output tree **/
    std::cout << "Final fill of \"uTOFstrip\" tree: totalHits " << totalHits << std::endl;
    for (Int_t ich = 0; ich < kNumberOfStripChannels; ich++) {
      channel = channels.at(ich);
      tout->Fill();
    }
    
    /** write and close output **/
    tout->Write();
    fout->Close();
    std::cout << "Tree \"uTOFstrip\" successfully written: " << mOutputFileName << std::endl;

    /** success **/
    return true;
  }
  
} /** namespace uTOF **/
