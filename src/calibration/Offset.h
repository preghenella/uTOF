#ifndef uTOF_calib_Offset_H
#define uTOF_calib_Offset_H

#include "calibration/Base.h"

namespace uTOF {
  namespace calib {
    
    class Offset : public Base {
    
    public:
    
      /** constructors **/
      Offset();
      Offset(int aIndex);

      /** destructors **/
      ~Offset();

    private:

      Offset(const Offset &);
      Offset &operator=(const Offset &);
	
      /** methods **/
      void book() override;
      void calibrate() override {calibrate1D();};
    
    }; /** class Offset **/

  } /** namespace Offset **/
} /** namespace uTOF **/

#endif /** uTOF_calib_Offset_H **/
