#ifndef uTOF_Hit_H
#define uTOF_Hit_H

namespace uTOF {
  
  class Hit {

  public:
    
    /** constructors **/
    Hit();
    Hit(float aTOT, float aDeltaX, float aDeltaZ, float aDeltaT, float aDeltaRAW);
    Hit(const Hit &rhs);

    /** destructors **/
    ~Hit();

    /** operators **/
    Hit &operator=(const Hit &rhs);

    /** accessors **/
    float getTOT()      const {return mTOT;};
    float getDeltaX()   const {return mDeltaX;};
    float getDeltaZ()   const {return mDeltaZ;};
    float getDeltaT()   const {return mDeltaT;};
    float getDeltaRAW() const {return mDeltaRAW;};

    /** modifiers **/
    void setDeltaRAW(float value) {mDeltaRAW = value;};
    
  private:
    
    float mTOT;
    float mDeltaX;
    float mDeltaZ;
    float mDeltaT;
    float mDeltaRAW;

  }; /** class Hit **/

} /** namespace uTOF **/

#endif /** uTOF_Hit_H **/
