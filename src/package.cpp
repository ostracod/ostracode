
#include <iostream>
#include <fstream>
#include <filesystem>
#include "json/json.h"
#include "package.hpp"

namespace fs = std::filesystem;

Package::Package(fs::path path) {
    this->path = path;
    this->srcPath = this->path / fs::path("src");
    fs::path configPath = this->path / fs::path("ostraConfig.json");
    Json::Value config;
    std::ifstream fileStream;
    fileStream.open(configPath.string());
    Json::CharReaderBuilder readerBuilder;
    std::string error;
    bool hasSucceeded = parseFromStream(readerBuilder, fileStream, &config, &error);
    fileStream.close();
    if (!hasSucceeded) {
        throw std::runtime_error(configPath.string() + " contains malformed JSON:\n" + error);
    }
    this->name = config["name"].asString();
    if (config.isMember("appModule")) {
        fs::path relPath(config["appModule"].asString());
        this->appModulePath = fs::canonical(this->srcPath / relPath);
    }
    if (config.isMember("libModule")) {
        fs::path relPath(config["libModule"].asString());
        this->libModulePath = fs::canonical(this->srcPath / relPath);
    }
}


