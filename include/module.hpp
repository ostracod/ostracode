
#ifndef MODULE_HEADER_FILE
#define MODULE_HEADER_FILE

#include <vector>
#include <filesystem>
#include "token.hpp"

namespace fs = std::filesystem;

class Package;

class Module {
    public:
    
    Package *package;
    fs::path path;
    fs::path absPath;
    std::string fileContent;
    std::vector<Token *> tokens;
    
    Module(Package *package, fs::path path);
    void readFile();
    void parseTokens();
    void import();
};

#endif


