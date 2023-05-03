#pragma once

#include "../db/model/user.h"
#include "../db/model/DataObject.h"
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


enum class Stage{
    START,
    SQUARE,
    WALL,
    FLOOR,
    ROOF,
    LOW_BASEBOARD,
    UP_BASEBOARD
};

class UserState {
public:
    UserState() = default;
    UserState(const models::User& user, State initState) : user_(user), state_(initState)
    {}

    void setState(State state){
        state_ = state;
    }
    State getState(){
        return state_;
    }

    void setStage(Stage stage){
        stage_ = stage;
    }
    Stage getStage(){
        return stage_;
    }

    std::map<std::string, models::DataObject> storage;
private:
    models::User user_;
    State state_;
    Stage stage_;
};
