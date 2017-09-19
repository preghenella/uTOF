#include "calibration/Channel.h"
#include "calibration/Offset.h"
#include "calibration/Slewing.h"
#include "calibration/Walk.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphErrors.h"
#include "TObjArray.h"

namespace uTOF {
  namespace calib {
  
    Channel::Channel() :
      Base(),
      mOffset(nullptr),
      mSlewing(nullptr),
      mWalk(nullptr)
    {}

    Channel::Channel(int aIndex) :
      Base(aIndex),
      mOffset(new Offset(aIndex)),
      mSlewing(new Slewing(aIndex)),
      mWalk(new Walk(aIndex))
    {

      /** useful cuts **/
      uTOF::calib::Cuts cutsDeltaX_center = { {-1.e6, -0.5}, {0.5, 1.e6} };
      
      /** offset default settings **/
      mOffset->addCalibration(mSlewing);
      mOffset->addCalibration(mWalk);
      mOffset->setCutsDeltaX(cutsDeltaX_center);
      /** slewing calibrations **/
      mSlewing->addCalibration(mOffset);
      mSlewing->addCalibration(mWalk);
      mSlewing->setCutsDeltaX(cutsDeltaX_center);
      /** walk calibrations **/
      mWalk->addCalibration(mOffset);
      mWalk->addCalibration(mSlewing);
      mWalk->setCutsDeltaX(cutsDeltaX_center);

      /** own settings **/
      setCutsDeltaX(cutsDeltaX_center);
      addCalibration(mOffset);
      addCalibration(mSlewing);
      addCalibration(mWalk);
      
    }

    Channel::~Channel()
    {
      if (mOffset) delete mOffset;
      if (mSlewing) delete mSlewing;
      if (mWalk) delete mWalk;
    }

    void
    Channel::book()
    {
      mHistogram = new TH1F(Form("hChannel_%d", mIndex),
			    Form("Channel performance (#%d);#Deltat (ps);", mIndex),
			    100, -1220., 1220.);
    }

    void
    Channel::process(TTree *aTree)
    {

      /** useful cuts **/
      uTOF::calib::Cuts cutsDeltaZ_center = { {-1.e6, -0.5}, {0.5, 1.e6} };
      uTOF::calib::Cuts cutsDeltaZ_none = { };

      /** loop over **/
      for (int iloop = 0; iloop < 3; iloop++) {
	
	/** offset calibration **/
	mOffset->process(aTree);
	
	/** time slewing calibration **/
	if (iloop == 0) mSlewing->setCutsDeltaZ(cutsDeltaZ_center);
	else mSlewing->setCutsDeltaZ(cutsDeltaZ_none);
	mSlewing->process(aTree);
	
	/** time walk calibration **/
	mWalk->process(aTree);
      }

      Base::process(aTree);
    }

    void
    Channel::write(TFile *aFile)
    {
      TObjArray oa;
      oa.Add(mOffset->getCorrection());
      oa.Add(mSlewing->getCorrection());
      oa.Add(mWalk->getCorrection());
      oa.Add(mHistogram);
      aFile->cd();
      oa.Write(Form("Channel_%d", mIndex), TObject::kSingleKey);
    }
      
  } /** namespace calib **/
} /** namespace uTOF **/
