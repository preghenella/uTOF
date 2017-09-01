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
    int        getIndex()       const {return mIndex;};
    const Hit *getHit(int iHit) const {return iHit < mHits.size() ? mHits.at(iHit) : NULL;};

    /** modifiers **/
    void AddHit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW);
    void Clear();

  private:
    
    /** members **/ 
    int      mIndex; //!
    HitArray mHits;
    
  };
  
} /** namespace uTOF **/

#endif /** uTOF_Channel_H **/
