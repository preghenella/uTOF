#include "calibration/Base.h"
#include "dataFormat/Channel.h"
#include "dataFormat/Hit.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include <iostream>

namespace uTOF {
  namespace calib {
  
    Base::Base() :
      mChannel(new Channel()),
      mIndex(-1),
      mHistogram(nullptr),
      mCorrection(nullptr),
      mCalibrations(),
      mFitFunction((TF1 *)gROOT->GetFunction("gaus")),
      mFitMinEntries(500),
      mFitStartSigma(100.),
      mFitMinNSigma(3.),
      mFitMaxNSigma(2.),
      mFitMaxError(100.),
      mCutsTOT(),
      mCutsDeltaX(),
      mCutsDeltaZ()
    {}

    Base::Base(int aIndex) :
      mChannel(new Channel(aIndex)),
      mIndex(aIndex),
      mHistogram(nullptr),
      mCorrection(nullptr),
      mCalibrations(),
      mFitFunction((TF1 *)gROOT->GetFunction("gaus")),
      mFitMinEntries(500),
      mFitStartSigma(100.),
      mFitMinNSigma(3.),
      mFitMaxNSigma(2.),
      mFitMaxError(100.),
      mCutsTOT(),
      mCutsDeltaX(),
      mCutsDeltaZ()
    {}

    Base::~Base()
    {
      if (mChannel) delete mChannel;
      if (mHistogram) delete mHistogram;
      if (mCorrection) delete mCorrection;
    }

    void
    Base::process(TTree *tree)
    {
      /** reset histogram **/
      if (!mHistogram) book();
      mHistogram->Reset();
      
      /** process the data **/
      tree->SetBranchAddress("channel", &mChannel);
      auto nEntries = tree->GetEntries();
      auto offset = mIndex % 96;

      /** loop over entries **/
      for (int iEntry = offset; iEntry < nEntries; iEntry += 96) {
	tree->GetEntry(iEntry);
	auto index = mChannel->getIndex();
	if (index != mIndex) std::cout << "Channel index mismatch: entry = " << iEntry << std::endl;

	/** loop over hits **/
	auto nHits = mChannel->getNumberOfHits();
	for (int iHit = 0; iHit < nHits; iHit++) {
	  auto hit = mChannel->getHit(iHit);

	  /** check cuts **/
	  if (cut(hit)) continue;
	  
	  /** loop over calibrations **/
	  for (const auto &calibration : mCalibrations)
	    calibration->correct(hit);

	  /** fill **/
	  fill(hit);

	} /** loop over hits **/
      } /** end of loop over entries **/
      
      /** calibrate **/
      calibrate();
    }

    bool
    Base::cut(const Hit *aHit) const
    {
      auto tot = aHit->getTOT();
      auto deltaX = aHit->getDeltaX();
      auto deltaZ = aHit->getDeltaZ();
      
      for (const auto &cut : mCutsTOT)    if (tot > cut.first && tot < cut.second) return true;
      for (const auto &cut : mCutsDeltaX) if (deltaX > cut.first && deltaX < cut.second) return true;
      for (const auto &cut : mCutsDeltaZ) if (deltaZ > cut.first && deltaX < cut.second) return true;

      /** success **/
      return false;
    }
    
    void
    Base::correct(Hit *aHit, float x)
    {
      if (!mCorrection) return;
      float deltaRAW = aHit->getDeltaRAW();
      float correction = mCorrection->Eval(x);
      aHit->setDeltaRAW(deltaRAW - correction);
    }
      
    void
    Base::calibrate1D()
    {
      /** reset correction **/
      if (mCorrection) delete mCorrection;
      mCorrection = new TGraphErrors();
      mCorrection->SetName(Form("gCorrection_%s", mHistogram->GetName()));
      
      /* fit time-zero */
      if (fitPeak(mFitFunction, mHistogram, mFitStartSigma, mFitMinNSigma, mFitMaxNSigma) != 0) {
	return;
      }
      float mean = mFitFunction->GetParameter(1);
      float meanerr = mFitFunction->GetParError(1);
      mCorrection->SetPoint(0, 0., mean);
      mCorrection->SetPointError(0, 0., meanerr);
    }
  
    void
    Base::calibrate2D()
    {
      /** reset correction **/
      if (mCorrection) delete mCorrection;
      mCorrection = new TGraphErrors();
      mCorrection->SetName(Form("gCorrection_%s", mHistogram->GetName()));

      /** projection-x **/
      auto hpx = ((TH2 *)mHistogram)->ProjectionX("hpx");

      /** define mix and max TOT bin **/
      int minBin = hpx->FindFirstBinAbove(0);
      int maxBin = hpx->FindLastBinAbove(0);
      float minTOT = hpx->GetBinLowEdge(minBin);
      float maxTOT = hpx->GetBinLowEdge(maxBin + 1);
      //      printf("min/max TOT defined: %f < TOT < %f ns [%d, %d]\n", minTOT, maxTOT, minBin, maxBin);

      /** loop over TOT bins **/
      int nPoints = 0;
      float tot, toterr, mean, meanerr;
      for (int ibin = minBin; ibin <= maxBin; ibin++) {
      
	/* define TOT window */
	int startBin = ibin;
	int endBin = ibin;
	while(hpx->Integral(startBin, endBin) < mFitMinEntries) {
	  if (ibin == 1) break;
	  else if (endBin < maxBin) endBin++;
	  else if (startBin > minBin) startBin--;
	  else break;
	}
	if (hpx->Integral(startBin, endBin) <= 0) continue;
	//	printf("TOT window defined: %f < TOT < %f ns [%d, %d], %d tracks\n", hpx->GetBinLowEdge(startBin), hpx->GetBinLowEdge(endBin + 1), startBin, endBin, hpx->Integral(startBin, endBin));

	/* projection-y */
	auto hpy = ((TH2 *)mHistogram)->ProjectionY("hpy", startBin, endBin);

	/* average TOT */
	hpx->GetXaxis()->SetRange(startBin, endBin);
	tot = hpx->GetMean();
	toterr = hpx->GetMeanError();

	/* fit time-zero */
	if (fitPeak(mFitFunction, hpy, mFitStartSigma, mFitMinNSigma, mFitMaxNSigma) != 0) {
	  delete hpy;
	  continue;
	}
	mean = mFitFunction->GetParameter(1);
	meanerr = mFitFunction->GetParError(1);

	/* delete projection-y */
	delete hpy;

        /* add point if good mean error */
	if (meanerr < mFitMaxError) {
	  mCorrection->SetPoint(nPoints, tot, mean);
	  mCorrection->SetPointError(nPoints, toterr, meanerr);
	  nPoints++;
	}

	/* set current bin */
	ibin = endBin;

      } /* end of loop over time bins */

    }

    int
    Base::fitPeak(TF1 *fitFunc, TH1 *h, float startSigma, float nSigmaMin, float nSigmaMax)
    {
      auto fitCent = h->GetBinCenter(h->GetMaximumBin());
      auto fitMin = fitCent - nSigmaMin * startSigma;
      auto fitMax = fitCent + nSigmaMax * startSigma;
      if (fitMin < h->GetXaxis()->GetXmin()) fitMin = h->GetXaxis()->GetXmin();
      if (fitMax > h->GetXaxis()->GetXmax()) fitMax = h->GetXaxis()->GetXmax();
      fitFunc->SetParameter(1, fitCent);
      fitFunc->SetParameter(2, startSigma);
      int fitres = h->Fit(fitFunc, "WWq0", "", fitMin, fitMax);
      if (fitres != 0) return fitres;
      /* refit with better range */
      for (int i = 0; i < 3; i++) {
	fitCent = fitFunc->GetParameter(1);
	fitMin = fitCent - nSigmaMin * fitFunc->GetParameter(2);
	fitMax = fitCent + nSigmaMax * fitFunc->GetParameter(2);	
	if (fitMin < h->GetXaxis()->GetXmin()) fitMin = h->GetXaxis()->GetXmin();
	if (fitMax > h->GetXaxis()->GetXmax()) fitMax = h->GetXaxis()->GetXmax();
	fitres = h->Fit(fitFunc, "q0", "", fitMin, fitMax);
	if (fitres != 0) return fitres;
      }
      return fitres;
    }

    void
    Base::excludeBelow(TH1 *h, int thr, std::vector<std::pair<float, float>> &regions)
    {
      bool above = true;
      float min, max;
      for (int ibin = 0; ibin < h->GetNbinsX(); ibin++) {
	auto content = h->GetBinContent(ibin + 1);
	/** no transition **/
	if (content == 0) continue;
	/** below transition **/
	if (content < thr && above) {
	  min = h->GetBinLowEdge(ibin + 1);
	  above = false;
	}
	/** above transition **/
	if (content >= thr && !above) {
	  max = h->GetBinLowEdge(ibin + 1);
	  regions.push_back({min, max});
	  above = true;
	  continue;
	}
      }
      if (!above) {
	max = h->GetBinLowEdge(h->GetNbinsX() + 1);
	regions.push_back({min, max});    
      }
      
    }
    
  } /** namespace calib **/
} /** namespace uTOF **/
