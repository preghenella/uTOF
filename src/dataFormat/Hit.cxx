#include "Hit.h"

namespace uTOF {
  
  Hit::Hit() : 
    mIndex(-1),
    mTOT(0.), 
    mDeltaX(0.), 
    mDeltaZ(0.), 
    mDeltaT(0.), 
    mDeltaRAW(0.) 
  {}
 
  Hit::Hit(int aIndex, float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW) :
    mIndex(aIndex),
    mTOT(aTOT), 
    mDeltaX(aDeltaX), 
    mDeltaZ(aDeltaZ), 
    mDeltaT(aDeltaT), 
    mDeltaRAW(aDeltaRAW) 
  {}

  Hit::Hit(const Hit &rhs) :
    mIndex(rhs.mIndex),
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
    mIndex = rhs.mIndex;
    mTOT = rhs.mTOT;
    mDeltaX = rhs.mDeltaX;
    mDeltaZ = rhs.mDeltaZ;
    mDeltaT = rhs.mDeltaT;
    mDeltaRAW = rhs.mDeltaRAW;
    return *this;
  }

} /** namespace uTOF **/
