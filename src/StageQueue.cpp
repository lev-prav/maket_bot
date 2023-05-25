//
// Created by lev on 14.05.23.
//

#include <iostream>
#include "StageQueue.h"

StageQueue::StageQueue(const std::list<std::string> &stages) {
    stages_ = stages;

    it_ = stages_.begin();
    for(auto& stage : stages_){
        std::cout<<stage<<" ";
    }
    std::cout<<"\n";
}

std::string StageQueue::nextStage() {
    if (it_ == --stages_.end()){
        return stages_.back();
    }

    return *(++it_);
}

std::string StageQueue::getStage() {
    return *it_;
}

StageQueue::StageQueue(const StageQueue &stage) {
    stages_= stage.stages_;
    it_ = stages_.begin();
}

std::string StageQueue::previousStage() {
    if (it_ == stages_.begin()){
        return *it_;
    }
    return *(--it_);
}
