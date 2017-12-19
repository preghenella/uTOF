#include "dataFormat/Hit.h"

namespace uTOF {
  
  Hit::Hit() : 
    mMomentum(0.),
    mFlag(0x0),
    mTOT(0.), 
    mDeltaX(0.), 
    mDeltaZ(0.), 
    mDeltaRAW(0.) 
  {}
 
  Hit::Hit(float aMomentum, unsigned char aFlag, float aTOT, float aDeltaX, float aDeltaZ, float aDeltaRAW) :
    mMomentum(aMomentum),
    mFlag(aFlag),
    mTOT(aTOT), 
    mDeltaX(aDeltaX), 
    mDeltaZ(aDeltaZ), 
    mDeltaRAW(aDeltaRAW) 
  {}

  Hit::Hit(const Hit &rhs) :
    mMomentum(rhs.mMomentum),
    mFlag(rhs.mFlag),
    mTOT(rhs.mTOT), 
    mDeltaX(rhs.mDeltaX), 
    mDeltaZ(rhs.mDeltaZ), 
    mDeltaRAW(rhs.mDeltaRAW)
  {}

  Hit::~Hit()
  {}

  Hit &
  Hit::operator=(const Hit &rhs)
  {
    if (&rhs == this) return *this;
    mMomentum = rhs.mMomentum;
    mFlag = rhs.mFlag;
    mTOT = rhs.mTOT;
    mDeltaX = rhs.mDeltaX;
    mDeltaZ = rhs.mDeltaZ;
    mDeltaRAW = rhs.mDeltaRAW;
    return *this;
  }

} /** namespace uTOF **/
