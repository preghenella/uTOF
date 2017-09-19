#include "calibration/Walk.h"
#include "TH2F.h"

namespace uTOF {
  namespace calib {
  
    Walk::Walk() :
      Base()
    {}
    
    Walk::Walk(int aIndex) :
      Base(aIndex)
    {}
    
    Walk::~Walk()
    {}

    void
    Walk::book()
    {
      mHistogram = new TH2F(Form("hWalk_%d", mIndex),
			    Form("Channel walk (#%d);#Deltaz (cm);#Deltat (ps)", mIndex),
			    20, -5., 5., 400, -4880., 4880.);
    }

  } /** namespace calib **/
} /** namespace uTOF **/
