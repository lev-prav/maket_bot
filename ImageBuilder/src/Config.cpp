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
    auto test = config.is_open();
    try {
        return json::parse(config);
    }
    catch (json::parse_error& json_error) {
        std::cout<<json_error.what()<<"\n";
    }

    return {};
}

Config::Config(const std::string &path) {
    parseJSON(path);
}

int Config::parseJSON(const std::string &path) {
    auto config = read_json(path);
    if (!config)
        throw std::domain_error("Файл " + path + " не найден или содержит ошибки!");

    const json& data = config.value();

    std::string baseImagePath = data["room_path"];
    loadBaseImage(baseImagePath);

    auto& coords = data["coordinates"];

    for(auto it = coords.begin(); it != coords.end(); ++it) {
        auto &points = it.value();
        Coordinates finishCoords{
                .topLeft =      {points["top_left"][0], points["top_left"][1]},
                .topRight =     {points["top_right"][0], points["top_right"][1]},
                .bottomLeft =   {points["bottom_left"][0], points["bottom_left"][1]},
                .bottomRight =  {points["bottom_right"][0], points["bottom_right"][1]}
        };
        finishingCoordinates_[it.key()] = finishCoords;
    }
    return 0;
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

int Config::loadBaseImage(const std::string &path) {
    baseImg_ = cv::imread(path);
    return 0;
}

cv::Mat Config::getBaseImg() const {
    return baseImg_;
}
