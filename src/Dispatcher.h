//
// Created by lev on 23.04.23.
//

#pragma once

#include <map>
#include <string>
#include <vector>
#include "UserState.h"
#include <tgbot/tgbot.h>

TgBot::ReplyKeyboardMarkup::Ptr createKeyboard(const std::vector<std::vector<std::string>>& buttonLayout);

class Dispatcher {
public:
    void handle(TgBot::Bot& bot, UserState& user, TgBot::Message::Ptr& message);
    std::map<Stage, int> routers;
};
