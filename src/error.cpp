
#include "error.hpp"
#include "module.hpp"
#include <sstream>

Error::Error(std::string message, int lineNum) {
    this->message = message;
    this->lineNum = lineNum;
    this->module = NULL;
}

std::string Error::toStr() {
    std::stringstream strStream;
    strStream << "Error";
    if (this->lineNum > 0) {
        strStream << " on line " << this->lineNum;
        if (this->module != NULL) {
            strStream << " of " << this->module->absPath.string();
        }
    } else {
        if (this->module != NULL) {
            strStream << " in " << this->module->absPath.string();
        }
    }
    strStream << ": " << this->message;
    return strStream.str();
}


