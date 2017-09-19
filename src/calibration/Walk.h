#ifndef uTOF_calib_Walk_H
#define uTOF_calib_Walk_H

#include "calibration/Base.h"

namespace uTOF {
  namespace calib {
  
    class Offset;
  
    class Walk : public Base {
    
    public:
    
      /** constructors **/
      Walk();
      Walk(int aIndex);

      /** destructors **/
      ~Walk();

    private:

      Walk(const Walk &);
      Walk &operator=(const Walk &);
	
      /** methods **/
      void book() override;
      void fill(const Hit *aHit) override {Base::fill(aHit, aHit->getDeltaZ());};
      void calibrate() override           {Base::calibrate2D();};
      void correct(Hit *aHit) override    {Base::correct(aHit, aHit->getDeltaZ());};

    }; /** class Walk **/

  } /** namespace calib **/
} /** namespace uTOF **/

#endif /** uTOF_calib_Walk_H **/
