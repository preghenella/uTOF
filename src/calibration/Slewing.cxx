#include "calibration/Slewing.h"
#include "TH2F.h"

namespace uTOF {
  namespace calib {
  
    Slewing::Slewing() :
      Base()
    {}

    Slewing::Slewing(int aIndex) :
      Base(aIndex)
    {}

    Slewing::~Slewing()
    {}

    void
    Slewing::book()
    {
      mHistogram = new TH2F(Form("hSlewing_%d", mIndex),
			    Form("Channel slewing (#%d);ToT (ns);#Deltat (ps)", mIndex),
			    4000, 0., 48.8, 400, -4880., 4880.);
    }

  } /** namespace calib **/
} /** namespace uTOF **/
