#include "dataFormat/Channel.h"
#include "dataFormat/Hit.h"
#include "TTree.h"

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
    for (auto &aHit : mHits)
      delete aHit;
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
  Channel::addHit(float aMomentum, unsigned char aFlag, float aTOT, float aDeltaX, float aDeltaZ, float aDeltaRAW) 
  {
    mHits.push_back(new Hit(aMomentum, aFlag, aTOT, aDeltaX, aDeltaZ, aDeltaRAW));
  }

  void
  Channel::addHits(const Channel *aChannel)
  {
    for (const auto &aHit : aChannel->mHits)
      mHits.push_back(new Hit(*aHit));
  }
  
  void 
  Channel::clear() 
  {
    for (auto &aHit : mHits)
      delete aHit;
    mHits.clear();
  }

} /** namespace uTOF **/
