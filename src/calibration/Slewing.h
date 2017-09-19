#ifndef uTOF_calib_Slewing_H
#define uTOF_calib_Slewing_H

#include "calibration/Base.h"

namespace uTOF {
  namespace calib {
  
    class Offset;
  
    class Slewing : public Base {
    
    public:
    
      /** constructors **/
      Slewing();
      Slewing(int aIndex);

      /** destructors **/
      ~Slewing();

    private:

      Slewing(const Slewing &);
      Slewing &operator=(const Slewing &);
	
      /** methods **/
      void book() override;
      void fill(const Hit *aHit) override {Base::fill(aHit, aHit->getTOT());};
      void calibrate() override           {Base::calibrate2D();};
      void correct(Hit *aHit) override    {Base::correct(aHit, aHit->getTOT());};
    
    }; /** class Slewing **/

  } /** namespace calib **/
} /** namespace uTOF **/

#endif /** uTOF_calib_Slewing_H **/
