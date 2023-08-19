
#include <iostream>
#include "module.hpp"

Module::Module(Package *package, fs::path path) {
    this->package = package;
    this->path = path;
}


