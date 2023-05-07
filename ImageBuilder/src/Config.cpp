//
// Created by lev on 05.05.23.
//

#include "Config.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>


using namespace ImageBuilder;
using json = nlohmann::json;

std::optional<json> read_json(const std::string& config_path) {
    std::ifstream config(config_path);

    try {
        return json::parse(config);
    }
    catch (json::parse_error& json_error) {
        std::cout<<json_error.what()<<"\n";
    }

    return {};
}

Config::Config(const std::string &path) {
    auto config = read_json(path);
    if (!config)
        throw std::domain_error("Файл " + path + " не найден или содержит ошибки!");

    const json& data = config.value();

    
}

ImageBuilder::Config::Config(const ImageBuilder::CoordinateMap &map) {
    finishingCoordinates_ = map;
}

std::optional<Coordinates> ImageBuilder::Config::getTypeCoordinate(const std::string &type) {
    if (!checkForType(type))
        return {};
    return finishingCoordinates_[type];
}

bool Config::checkForType(const std::string &type) {
    return finishingCoordinates_.find(type) != finishingCoordinates_.end();
}

CoordinateMap Config::getCoordinateMapping() {
    return finishingCoordinates_;
}
