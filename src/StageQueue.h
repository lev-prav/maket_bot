//
// Created by lev on 14.05.23.
//

#pragma once


#include <list>
#include <string>

class StageQueue {
public:
    StageQueue() = default;
    explicit StageQueue(const std::list<std::string>& stages);
    StageQueue(const StageQueue& stage);

    std::string nextStage();
    std::string previousStage();
    std::string getStage();
private:
    std::list<std::string> stages_;
    decltype(stages_.begin()) it_;
};
