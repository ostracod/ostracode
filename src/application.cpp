
#include <iostream>
#include <filesystem>
#include "application.hpp"
#include "package.hpp"

namespace fs = std::filesystem;

Application::Application() {
    std::cout << "I am the application!" << std::endl;
}

void Application::setEntryPackage(fs::path path) {
    this->entryPackage = new Package(path);
    std::cout << "Package name: " << this->entryPackage->name << std::endl;
}

void Application::setEntryModule(fs::path path) {
    // TODO: Implement.
    
}


