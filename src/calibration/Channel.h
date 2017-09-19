#ifndef uTOF_calib_Channel_H
#define uTOF_calib_Channel_H

#include "calibration/Base.h"

class TFile;

namespace uTOF {
  namespace calib {
  
    class Offset;
    class Slewing;
    class Walk;
    
    class Channel : public Base {
    
    public:
    
      /** constructors **/
      Channel();
      Channel(int aIndex);

      /** destructors **/
      ~Channel();

      /** operators **/

      /** accessors **/
      int      getIndex() const {return mIndex;};
      Offset  *getOffset() const {return mOffset;};
      Slewing *getSlewing() const {return mSlewing;};
      Walk    *getWalk() const {return mWalk;};
      
      /** modifiers **/

      /** methods **/
      void process(TTree *aTree) override;
      void write(TFile *aFile);
      
    private:

      Channel(const Channel &);
      Channel &operator=(const Channel &);
	
      /** methods **/
      void book() override;
      void calibrate() override {};
    
      /** members **/
      Offset  *mOffset; //->
      Slewing *mSlewing; //->
      Walk    *mWalk; //->
      
    }; /** class Channel **/

  } /** namespace calib **/
} /** namespace uTOF **/

#endif /** uTOF_calib_Channel_H **/
