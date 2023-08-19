
#include <iostream>
#include <filesystem>
#include "application.hpp"
#include "package.hpp"

namespace fs = std::filesystem;

Package *Application::getPackage(fs::path path) {
    auto it = this->packages.find(path);
    if (it != this->packages.end()) {
        return it->second;
    }
    Package *package = new Package(this, path);
    this->packages.insert({ path, package });
    return package;
}

void Application::setEntryPackage(fs::path path) {
    this->entryPackage = this->getPackage(path);
    this->entryModule = this->entryPackage->getAppModule();
}

void Application::setEntryModule(fs::path path) {
    fs::path packagePath = Package::getPathByModule(path);
    if (packagePath.empty()) {
        throw std::runtime_error(path.string() + " is not inside an OstraCode package.");
    }
    this->entryPackage = this->getPackage(packagePath);
    fs::path relPath = fs::relative(path, this->entryPackage->srcPath).lexically_normal();
    this->entryModule = this->entryPackage->getModule(relPath);
}

void Application::run() {
    this->entryModule->import();
}


