
#include <iostream>
#include <fstream>
#include <sstream>
#include "error.hpp"
#include "token.hpp"
#include "module.hpp"
#include "package.hpp"

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
        std::cout << token->toStr() << std::endl;
    }
}

void Module::import() {
    try {
        this->readFile();
        this->parseTokens();
        // TODO: Finish implementation.
    
    } catch (Error &error) {
        if (error.module == NULL) {
            error.module = this;
        }
        throw error;
    }
}


