
#include <iostream>
#include <filesystem>
#include "application.hpp"

namespace fs = std::filesystem;

Application::Application() {
    std::cout << "I am the application!" << std::endl;
}

void Application::setEntryPackage(fs::path path) {
    std::cout << "Entry package: " << path << std::endl;
}

void Application::setEntryModule(fs::path path) {
    std::cout << "Entry module: " << path << std::endl;
}


