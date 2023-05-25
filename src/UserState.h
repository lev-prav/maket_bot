#pragma once

#include "../db/model/user.h"
#include "../db/model/DataObject.h"
#include "StageQueue.h"
#include <map>

enum class State{
    START,
    ADD,
    MATERIAL,
    PLATE,
    SET_TEXTURE,
    CONFIRM,
    IDLE
};


class UserState {
public:
    UserState() = default;
    UserState(const models::User& user, State initState, const StageQueue& stage) :
    user_(user), state_(initState), stage_(stage)
    {}

    void setState(State state){
        state_ = state;
    }
    State getState(){
        return state_;
    }

    StageQueue& getStage(){
        return stage_;
    }

    std::map<std::string, models::DataObject> storage;
private:
    models::User user_;
    State state_;
    StageQueue stage_;
};
