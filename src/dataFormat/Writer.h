#ifndef uTOF_Writer_H
#define uTOF_Writer_H

#include <string>

namespace uTOF {

  class Writer {
    
  public:
    
    /** constructors **/
    Writer();
    Writer(std::string inputFileName, std::string outputFileName);
    
    /** destructors **/
    ~Writer();
    
    /** methods **/
    bool Process();
    
  private:
    
    /** **/
    Writer(const Writer &rhs);
    Writer &operator=(const Writer &rhs);    
    
    /** constants **/
    const int kMaxHits          = 4096;
    const int kNumberOfChannels = 157248;
    
    /** members **/
    std::string mInputFileName, mOutputFileName; 
      
  }; /** class Writer **/

} /** namespace uTOF **/

#endif /** uTOF_Writer_H **/
