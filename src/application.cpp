
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
    this->entryModule = this->entryPackage->getAppModule();
}

void Application::setEntryModule(fs::path path) {
    fs::path packagePath = Package::getPathByModule(path);
    if (packagePath.empty()) {
        throw std::runtime_error(path.string() + " is not inside an OstraCode package.");
    }
    this->entryPackage = new Package(packagePath);
    fs::path relPath = fs::relative(path, this->entryPackage->srcPath).lexically_normal();
    this->entryModule = this->entryPackage->getModule(relPath);
}


