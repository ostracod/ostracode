
#ifndef PACKAGE_HEADER_FILE
#define PACKAGE_HEADER_FILE

#include <filesystem>

namespace fs = std::filesystem;

class Package {
    public:
    
    fs::path path;
    fs::path srcPath;
    fs::path appModulePath;
    fs::path libModulePath;
    std::string name;
    
    Package(fs::path path);
};

#endif


