#ifndef uTOF_Channel_H
#define uTOF_Channel_H

#include <vector>

namespace uTOF {

  class Hit;
  typedef std::vector<Hit *> HitArray;

  class Channel {
    
  public:
    
    /** constructors **/
    Channel();
    Channel(int aIndex);
    Channel(const Channel &rhs);

    /** destructors **/
    ~Channel();

    /** operators **/
    Channel &operator=(const Channel &rhs);

    /** accessors **/
    int        getIndex()        const {return mIndex;};
    int        getNumberOfHits() const {return mHits.size();};
    const Hit *getHit(int iHit)  const {return iHit < mHits.size() ? mHits.at(iHit) : nullptr;};

    /** modifiers **/
    void addHit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW);
    void addHits(const Channel *aChannel);
    void clear();

  private:
    
    /** members **/ 
    int      mIndex;
    HitArray mHits;
    
  };
  
} /** namespace uTOF **/

#endif /** uTOF_Channel_H **/
