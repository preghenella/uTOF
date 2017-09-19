#ifndef uTOF_calib_Base_H
#define uTOF_calib_Base_H

#include <vector>
#include "dataFormat/Hit.h"
#include "TH1.h"

class TTree;
class TFile;
class TF1;
class TGraphErrors;

namespace uTOF {

  class Channel;
  class Hit;

    namespace calib {    
    
    typedef std::vector<std::pair<float, float>> Cuts;
    
    class Base {
    
    public:
    
      /** constructors **/
      Base();
      Base(int aIndex);

      /** destructors **/
      virtual ~Base();

      /** operators **/

      /** accessors **/
      int getIndex() const {return mIndex;};
      TH1 *getHistogram() const {return mHistogram;};
      TGraphErrors *getCorrection() const {return mCorrection;};
      const Cuts &getCutsTOT() const {return mCutsTOT;};
      
      /** modifiers **/
      void addCalibration(Base *aCalibration) {mCalibrations.push_back(aCalibration);};

      /** fit modifiers **/
      void setFitMinEntries(int value) {mFitMinEntries = value;};
      void setFitStartSigma(float value) {mFitStartSigma = value;};
      void setFitMinNSigma(float value) {mFitMinNSigma = value;};
      void setFitMaxNSigma(float value) {mFitMaxNSigma = value;};
      void setFitMaxError(float value) {mFitMaxError = value;};

      /** cut modifiers **/
      void setCut(const std::string &name, double min, double max);
      void setCutsTOT(Cuts &value) {mCutsTOT = value;};
      void addCutTOT(float min, float max) {mCutsTOT.push_back({min, max});};
      void setCutsDeltaX(Cuts &value) {mCutsDeltaX = value;};
      void addCutDeltaX(float min, float max) {mCutsDeltaX.push_back({min, max});};
      void setCutsDeltaZ(Cuts &value) {mCutsDeltaZ = value;};
      void addCutDeltaZ(float min, float max) {mCutsDeltaZ.push_back({min, max});};
      
      /** methods **/
      virtual void process(TTree *aTree);

      /** static methods **/
      static int fitPeak(TF1 *aFunction, TH1 *hHistogram, float startSigma, float nSigmaMin, float nSigmaMax);
      static void excludeBelow(TH1 *aHistogram, int threshold, Cuts &regions);
      
    protected:

      Base(const Base &);
      Base &operator=(const Base &);

      /** methods **/
      bool cut(const Hit *aHit) const;
      virtual void book() = 0;
      virtual void calibrate() = 0;
      
      virtual void fill(const Hit *aHit)          {mHistogram->Fill(aHit->getDeltaRAW());};      
      virtual void fill(const Hit *aHit, float x) {mHistogram->Fill(x, aHit->getDeltaRAW());};      
      virtual void correct(Hit *aHit)             {correct(aHit, 0.);};
      virtual void correct(Hit *aHit, float x);
      virtual void calibrate1D();
      virtual void calibrate2D();
      
      /** members **/ 
      Channel      *mChannel; //!
      int           mIndex;
      TH1          *mHistogram; //!
      TGraphErrors *mCorrection;
      std::vector<Base *> mCalibrations; //!

      /** fit memeber **/
      TF1 *mFitFunction = nullptr; //!
      int  mFitMinEntries = 500; //!
      float mFitStartSigma = 100.; //!
      float mFitMinNSigma = 3.; //!
      float mFitMaxNSigma = 2.; //!
      float mFitMaxError = 100.; //!
      
      /** cut members **/
      Cuts mCutsTOT; //!
      Cuts mCutsDeltaX; //!
      Cuts mCutsDeltaZ; //!
      
    }; /** class Base **/

  } /** namespace calib **/
} /** namespace uTOF **/

#endif /** uTOF_calib_Base_H **/
