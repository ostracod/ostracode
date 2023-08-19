
#ifndef APPLICATION_HEADER_FILE
#define APPLICATION_HEADER_FILE

#include <filesystem>
#include "package.hpp"

namespace fs = std::filesystem;

class Application {
    public:
    
    Package *entryPackage;
    
    Application();
    void setEntryPackage(fs::path path);
    void setEntryModule(fs::path path);
};

#endif


