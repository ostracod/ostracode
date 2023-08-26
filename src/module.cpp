
#include <iostream>
#include <fstream>
#include <sstream>
#include "package.hpp"
#include "module.hpp"
#include "token.hpp"

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
}

void Module::parseTokens() {
    TokenParser parser(&(this->fileContent));
    this->tokens = parser.parseTokens();
    for (auto &token : this->tokens) {
        std::cout << token->toString() << std::endl;
    }
}

void Module::import() {
    this->readFile();
    this->parseTokens();
    // TODO: Finish implementation.
    
}


