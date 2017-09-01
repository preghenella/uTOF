#include "Channel.h"
#include "Hit.h"

namespace uTOF {

  Channel::Channel() :
    TObject(), mIndex(-1), mHits()
  {}

  Channel::Channel(int aIndex) :
    TObject(), mIndex(aIndex), mHits()
  {}

  Channel::Channel(const Channel &rhs) :
    TObject(rhs), mIndex(rhs.mIndex), mHits(rhs.mHits)
  {}

  Channel::~Channel()
  {
    mHits.clear();
  }

  Channel &
  Channel::operator=(const Channel &rhs)
  {
    if (&rhs == this) return *this;
    TObject::operator=(rhs);
    mIndex = rhs.mIndex;
    mHits  = rhs.mHits;
    return *this;
  }

  void 
  Channel::AddHit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW) 
  {
    mHits.push_back(new Hit(aTOT, aDeltaX, aDeltaZ, aDeltaT, aDeltaRAW));
  }

  void 
  Channel::Clear() 
  {
    mHits.clear();
  }

} /** namespace uTOF **/
