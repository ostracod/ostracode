
#ifndef APPLICATION_HEADER_FILE
#define APPLICATION_HEADER_FILE

#include <map>
#include <filesystem>
#include "package.hpp"
#include "module.hpp"

namespace fs = std::filesystem;

class Application {
    public:
    
    std::map<fs::path, Package *> packages;
    Package *entryPackage;
    Module *entryModule;
    
    Package *getPackage(fs::path path);
    void setEntryPackage(fs::path path);
    void setEntryModule(fs::path path);
    void run();
};

#endif


