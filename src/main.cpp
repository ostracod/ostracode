
#include <iostream>
#include <filesystem>
#include "error.hpp"
#include "token.hpp"
#include "application.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage:" << std::endl << "ostracode (packagePath)" << std::endl << "ostracode (modulePath)" << std::endl;
        return 1;
    }
    TokenText::init();
    fs::path argPath(argv[1]);
    fs::path absPath = fs::absolute(argPath).lexically_normal();
    try {
        Application app;
        if (fs::is_directory(absPath)) {
            app.setEntryPackage(absPath);
        } else {
            app.setEntryModule(absPath);
        }
        app.run();
    } catch (Error &error) {
        std::cout << error.toStr() << std::endl;
        return 1;
    }
    return 0;
}


