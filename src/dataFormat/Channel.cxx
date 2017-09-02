#include "Channel.h"
#include "Hit.h"

namespace uTOF {

  Channel::Channel() :
    mIndex(-1), mHits()
  {}

  Channel::Channel(int aIndex) :
    mIndex(aIndex), mHits()
  {}

  Channel::Channel(const Channel &rhs) :
    mIndex(rhs.mIndex), mHits(rhs.mHits)
  {}

  Channel::~Channel()
  {
    mHits.clear();
  }

  Channel &
  Channel::operator=(const Channel &rhs)
  {
    if (&rhs == this) return *this;
    mIndex = rhs.mIndex;
    mHits  = rhs.mHits;
    return *this;
  }

  void 
  Channel::addHit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW) 
  {
    mHits.push_back(new Hit(aTOT, aDeltaX, aDeltaZ, aDeltaT, aDeltaRAW));
  }

  void 
  Channel::clear() 
  {
    mHits.clear();
  }

} /** namespace uTOF **/
