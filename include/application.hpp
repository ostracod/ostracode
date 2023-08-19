
#ifndef APPLICATION_HEADER_FILE
#define APPLICATION_HEADER_FILE

#include <filesystem>
#include "package.hpp"
#include "module.hpp"

namespace fs = std::filesystem;

class Application {
    public:
    
    Package *entryPackage;
    Module *entryModule;
    
    Application();
    void setEntryPackage(fs::path path);
    void setEntryModule(fs::path path);
};

#endif


