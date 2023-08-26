
#include <iostream>
#include <fstream>
#include <filesystem>
#include "json/json.h"
#include "error.hpp"
#include "module.hpp"
#include "package.hpp"

namespace fs = std::filesystem;

std::string Package::configFileName = "ostraConfig.json";

fs::path Package::getPathByModule(fs::path modulePath) {
    fs::path path = modulePath;
    while (path.has_relative_path()) {
        path = path.parent_path();
        fs::path configPath = path / fs::path(Package::configFileName);
        if (fs::exists(configPath)) {
            return path;
        }
    }
    return fs::path();
}

Package::Package(Application *app, fs::path path) {
    this->app = app;
    this->path = path;
    this->srcPath = this->path / fs::path("src");
    fs::path configPath = this->path / fs::path(Package::configFileName);
    Json::Value config;
    std::ifstream fileStream;
    fileStream.open(configPath.string());
    Json::CharReaderBuilder readerBuilder;
    std::string error;
    bool hasSucceeded = parseFromStream(readerBuilder, fileStream, &config, &error);
    fileStream.close();
    if (!hasSucceeded) {
        throw Error(configPath.string() + " contains malformed JSON:\n" + error);
    }
    this->name = config["name"].asString();
    if (config.isMember("appModule")) {
        fs::path path(config["appModule"].asString());
        this->appModulePath = path.lexically_normal();
    }
    if (config.isMember("libModule")) {
        fs::path path(config["libModule"].asString());
        this->libModulePath = path.lexically_normal();
    }
}

Module *Package::getModule(fs::path path) {
    auto it = this->modules.find(path);
    if (it != this->modules.end()) {
        return it->second;
    }
    Module *module = new Module(this, path);
    this->modules.insert({ path, module });
    return module;
}

Module *Package::getAppModule() {
    if (this->appModulePath.empty()) {
        throw Error(this->path.string() + " does not define a default entry-point module.");
    }
    return this->getModule(this->appModulePath);
}


