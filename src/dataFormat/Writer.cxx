#include "Writer.h"
#include "Channel.h"
#include "Hit.h"
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include <vector>
#include <iostream>

namespace uTOF {

  Writer::Writer() :
    mInputFileName(), mOutputFileName()
  {}

  Writer::Writer(std::string inputFileName, std::string outputFileName) :
    mInputFileName(inputFileName), mOutputFileName(outputFileName)
  {}

  Writer::~Writer()
  {
  }

  bool
  Writer::Process()
  {
    
    /** open input **/
    TFile *fin = TFile::Open(mInputFileName.c_str());
    if (!fin || !fin->IsOpen()) {
      std::cerr << "Cannot open input file: " << mInputFileName << std::endl;
      return false;
    }
    TTree *tin = (TTree *)fin->Get("aodTree");
    if (!tin) {
      std::cerr << "Cannot find \"aodTree\" in input file: " << mInputFileName << std::endl;
      return false;
    }
    std::cout << "Processing input file: " << mInputFileName << std::endl;
    Int_t nhits, index[kMaxHits];
    Float_t tot[kMaxHits], deltax[kMaxHits], deltaz[kMaxHits], deltat[kMaxHits], deltaraw[kMaxHits];
    tin->SetBranchAddress("nhits", &nhits);
    tin->SetBranchAddress("index", &index);
    tin->SetBranchAddress("tot", &tot);
    tin->SetBranchAddress("deltax", &deltax);
    tin->SetBranchAddress("deltaz", &deltaz);
    tin->SetBranchAddress("deltat", &deltat);
    tin->SetBranchAddress("deltaraw", &deltaraw);
    
    /** open output **/
    TFile *fout = TFile::Open(mOutputFileName.c_str(), "RECREATE");
    if (!fout || !fout->IsOpen()) {
      std::cerr << "Cannot open output file: " << mOutputFileName << std::endl;
      return false;
    }
    TTree *tout = new TTree("uTOFtree", ""); 
    Channel *channel = new Channel();
    tout->Branch("channel", "uTOF::Channel", &channel); 
    
    /** create channels **/
    std::vector<Channel *> channels;
    for (Int_t ich = 0; ich < kNumberOfChannels; ich++)
      channels.push_back(new Channel(ich));
    
    /** loop over input tree **/
    Long64_t nev = tin->GetEntries();
    long totalHits = 0, partialHits = 0;
    std::cout << "Start processing input tree: " << nev << " entries found" << std::endl;
    for (Int_t iev = 0; iev < nev; iev++) {
      /** get event **/
      tin->GetEntry(iev);
      
      /** loop over hits **/
      for (Int_t ihit = 0; ihit < nhits; ihit++) {
	
	/** add hit to channel **/
	channel = channels.at(index[ihit]);
	channel->addHit(index[ihit], tot[ihit], deltax[ihit], deltaz[ihit], deltat[ihit], deltaraw[ihit]); 
	partialHits++;
	totalHits++;
	
      } /** end of loop over hits **/

      /** partial fill output tree **/
      if (partialHits > 15724800) {
	partialHits = 0;
	std::cout << "Partial fill of \"uTOFtree\" tree: totalHits = " << totalHits << " (at event #" << iev << ")" << std::endl;
	for (Int_t ich = 0; ich < kNumberOfChannels; ich++) {
	  channel = channels.at(ich);
	  tout->Fill();
	  channel->clear();
	}
      }

    } /** and of loop over input tree **/

    /** final fill output tree **/
    std::cout << "Final fill of \"uTOFtree\" tree: totalHits " << totalHits << std::endl;
    for (Int_t ich = 0; ich < kNumberOfChannels; ich++) {
      channel = channels.at(ich);
      tout->Fill();
    }
    
    /** close input **/
    fin->Close();
    
    
    /** write and close output **/
    tout->Write();
    fout->Close();
    std::cout << "Tree \"uTOFtree\" successfully written: " << mOutputFileName << std::endl;

    /** success **/
    return true;
  }
  
} /** namespace uTOF **/
