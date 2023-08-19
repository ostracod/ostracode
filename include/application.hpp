
#ifndef APPLICATION_HEADER_FILE
#define APPLICATION_HEADER_FILE

#include <filesystem>

namespace fs = std::filesystem;

class Application {
    public:
    
    Application();
    void setEntryPackage(fs::path path);
    void setEntryModule(fs::path path);
};

#endif


