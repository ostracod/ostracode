
#ifndef PACKAGE_HEADER_FILE
#define PACKAGE_HEADER_FILE

#include <map>
#include <filesystem>
#include "module.hpp"

namespace fs = std::filesystem;

class Package {
    public:
    
    static std::string configFileName;
    
    static fs::path getPathByModule(fs::path modulePath);
    
    fs::path path;
    fs::path srcPath;
    fs::path appModulePath;
    fs::path libModulePath;
    std::string name;
    std::map<fs::path, Module *> modules;
    
    Package(fs::path path);
    // `path` must be normal and relative to `srcPath`.
    Module *getModule(fs::path path);
    Module *getAppModule();
};

#endif


