//
// Created by lev on 13.05.23.
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>

using Labels = std::map<std::string, std::vector<std::string>>;

class BotConfig {
public:
    explicit BotConfig(const std::string& path);

    std::list<std::string> getStages() const;
    std::vector<std::string> getPartsOfStage(const std::string& stage);
    std::string getToken();

    int parseJSON(const std::string& path);
private:

    std::string token_;
    Labels labels_;
    std::list<std::string> stagesOrder_;
};
