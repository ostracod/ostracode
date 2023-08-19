
#include <iostream>
#include <filesystem>
#include "application.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage:" << std::endl << "ostracode (packagePath)" << std::endl << "ostracode (modulePath)" << std::endl;
        return 1;
    }
    fs::path argPath(argv[1]);
    fs::path absPath = fs::absolute(argPath).lexically_normal();
    Application app;
    if (fs::is_directory(absPath)) {
        app.setEntryPackage(absPath);
    } else {
        app.setEntryModule(absPath);
    }
    std::cout << "Entry module: " << app.entryModule->path << std::endl;
    return 0;
}


