#include "Hit.h"

namespace uTOF {
  
  Hit::Hit() : 
    mTOT(0.), 
    mDeltaX(0.), 
    mDeltaZ(0.), 
    mDeltaT(0.), 
    mDeltaRAW(0.) 
  {}
 
  Hit::Hit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW) :
    mTOT(aTOT), 
    mDeltaX(aDeltaX), 
    mDeltaZ(aDeltaZ), 
    mDeltaT(aDeltaT), 
    mDeltaRAW(aDeltaRAW) 
  {}

  Hit::Hit(const Hit &rhs) :
    mTOT(rhs.mTOT), 
    mDeltaX(rhs.mDeltaX), 
    mDeltaZ(rhs.mDeltaZ), 
    mDeltaT(rhs.mDeltaT), 
    mDeltaRAW(rhs.mDeltaRAW)
  {}

  Hit::~Hit()
  {}

  Hit &
  Hit::operator=(const Hit &rhs)
  {
    if (&rhs == this) return *this;
    mTOT = rhs.mTOT;
    mDeltaX = rhs.mDeltaX;
    mDeltaZ = rhs.mDeltaZ;
    mDeltaT = rhs.mDeltaT;
    mDeltaRAW = rhs.mDeltaRAW;
    return *this;
  }

} /** namespace uTOF **/
