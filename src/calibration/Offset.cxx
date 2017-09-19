#include "calibration/Offset.h"
#include "TH1F.h"

namespace uTOF {
  namespace calib {
  
    Offset::Offset() :
      Base()
    {}

    Offset::Offset(int aIndex) :
      Base(aIndex)
    {}

    Offset::~Offset()
    {}

    void
    Offset::book()
    {
      mHistogram = new TH1F(Form("hOffset_%d", mIndex),
			    Form("Channel offset (#%d);#Deltat (ps);", mIndex),
			    25000, 0., 610000.);
    }

  } /** namespace calib **/
} /** namespace uTOF **/
