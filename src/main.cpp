
#include <iostream>
#include <filesystem>
#include "application.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage:" << std::endl << "ostracode (packagePath)" << std::endl << "ostracode (modulePath)" << std::endl;
        return 1;
    }
    std::string argStr(argv[1]);
    fs::path argPath(argStr);
    fs::path absPath = fs::canonical(fs::absolute(argPath));
    Application app;
    if (fs::is_directory(absPath)) {
        app.setEntryPackage(absPath);
    } else {
        app.setEntryModule(absPath);
    }
    return 0;
}


