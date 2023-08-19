
#include <iostream>
#include <fstream>
#include <sstream>
#include "package.hpp"
#include "module.hpp"

Module::Module(Package *package, fs::path path) {
    this->package = package;
    this->path = path;
    this->absPath = this->package->srcPath / this->path;
}

void Module::readFile() {
    std::ifstream fileStream;
    fileStream.open(this->absPath);
    std::stringstream strStream;
    strStream << fileStream.rdbuf();
    fileStream.close();
    this->fileContent = strStream.str();
    std::cout << "Content of " << this->path << ":" << std::endl << this->fileContent << std::endl;
}

void Module::import() {
    this->readFile();
    // TODO: Finish implementation.
    
}


