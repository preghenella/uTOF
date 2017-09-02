#ifndef uTOF_StripWriter_H
#define uTOF_StripWriter_H

#include <string>

namespace uTOF {

  class StripWriter {
    
  public:
    
    /** constructors **/
    StripWriter();
    StripWriter(int aStripIndex, std::string aInputFileName, std::string aOutputFileName);
    
    /** destructors **/
    ~StripWriter();
    
    /** methods **/
    bool Process();
    
  private:
    
    /** **/
    StripWriter(const StripWriter &rhs);
    StripWriter &operator=(const StripWriter &rhs);    
    
    /** constants **/
    const int kNumberOfChannels      = 157248;
    const int kNumberOfStripChannels = 96;
    
    /** members **/
    int         mStripIndex;
    std::string mInputFileName, mOutputFileName; 
      
  };
  
} /** namespace uTOF **/

#endif /** uTOF_StripWriter_H **/
