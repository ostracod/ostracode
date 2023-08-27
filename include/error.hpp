
#ifndef ERROR_HEADER_FILE
#define ERROR_HEADER_FILE

#include <string>

class Module;

class Error {
    public:
    
    std::string message;
    int lineNum;
    Module *module;
    
    Error(std::string message, int lineNum = 0);
    std::string toStr();
};

#endif


