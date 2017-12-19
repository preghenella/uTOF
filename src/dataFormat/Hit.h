#ifndef uTOF_Hit_H
#define uTOF_Hit_H

namespace uTOF {
  
  class Hit {

  public:
    
    /** flag enumerator **/
    enum EFlag_t {
      kMultiple     = 0x01,
      kAdjacentX    = 0x02,
      kAdjacentZ    = 0x04,
      kPrimary      = 0x08,
      kGoodClusters = 0x10,
      kGoodChi2     = 0x20,
      kGoodT0       = 0x40
    };
    
    /** constructors **/
    Hit();
    Hit(float aMomentum, unsigned char aFlag, float aTOT, float aDeltaX, float aDeltaZ, float aDeltaRAW);
    Hit(const Hit &rhs);

    /** destructors **/
    ~Hit();

    /** operators **/
    Hit &operator=(const Hit &rhs);

    /** accessors **/
    float         getMomentum() const {return mMomentum;};
    unsigned char getFlag()     const {return mFlag;};
    float         getTOT()      const {return mTOT;};
    float         getDeltaX()   const {return mDeltaX;};
    float         getDeltaZ()   const {return mDeltaZ;};
    float         getDeltaRAW() const {return mDeltaRAW;};

    /** methods **/
    bool isFlag(EFlag_t aFlag) const {return (mFlag && aFlag) == aFlag;};
    
    /** modifiers **/
    void setDeltaRAW(float value) {mDeltaRAW = value;};

  private:
    
    float         mMomentum;
    unsigned char mFlag;
    float         mTOT;
    float         mDeltaX;
    float         mDeltaZ;
    float         mDeltaRAW;

  }; /** class Hit **/

} /** namespace uTOF **/

#endif /** uTOF_Hit_H **/
