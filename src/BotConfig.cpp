//
// Created by lev on 13.05.23.
//

#include "BotConfig.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>


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

int BotConfig::parseJSON(const std::string &path) {

    auto config = read_json(path);
    if (!config)
        throw std::domain_error("Файл " + path + " не найден или содержит ошибки!");

    const json& data = config.value();

    token_ = data["token"];

    auto& labelsConfig = data["labels_"];

    for(auto it = labelsConfig.begin(); it != labelsConfig.end(); ++it) {
        auto &label = it.key();
        auto &parts = it.value();

        stagesOrder_.push_back(label);
        labels_[label] = {};
        for(auto& partLabel : parts){
            labels_[label].push_back(partLabel);
        }
    }

    return 0;
}

BotConfig::BotConfig(const std::string &path) {
    parseJSON(path);
}

std::list<std::string> BotConfig::getStages() const {
    return stagesOrder_;
}

std::vector<std::string> BotConfig::getPartsOfStage(const std::string &stage) {
    return labels_[stage];
}

std::string BotConfig::getToken() {
    return token_;
}
