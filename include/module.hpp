
#ifndef MODULE_HEADER_FILE
#define MODULE_HEADER_FILE

#include <filesystem>

namespace fs = std::filesystem;

class Package;

class Module {
    public:
    
    Package *package;
    fs::path path;
    fs::path absPath;
    std::string fileContent;
    
    Module(Package *package, fs::path path);
    void readFile();
    void import();
};

#endif


