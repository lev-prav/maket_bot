//
// Created by lev on 23.04.23.
//

#include "Dispatcher.h"
#include <sstream>

#include "../db/model/Room.h"
#include "../db/model/Wall.h"

using namespace std;
using namespace TgBot;

ReplyKeyboardMarkup::Ptr createKeyboard(const vector<vector<string>>& buttonLayout)
{
    ReplyKeyboardMarkup::Ptr kb(new ReplyKeyboardMarkup());

    for (size_t i = 0; i < buttonLayout.size(); ++i) {
        vector<KeyboardButton::Ptr> row;
        for (size_t j = 0; j < buttonLayout[i].size(); ++j) {
            KeyboardButton::Ptr button(new KeyboardButton);
            button->text = buttonLayout[i][j];
            button->requestContact = false;
            button->requestLocation = false;
            row.push_back(button);
        }
        kb->keyboard.push_back(row);
    }
    kb->resizeKeyboard = true;

    return kb;
}


void Dispatcher::handle(TgBot::Bot& bot, UserState& user, TgBot::Message::Ptr& message) {
    ReplyKeyboardMarkup::Ptr keyboard;
    std::string answerText = "Непонятно...";

    StageQueue& stage = user.getStage();
    switch(stage.getStage()){
        case "START" :{
            if (message->text == "Начать редактирование"){
                answerText = "Задайте размеры комнаты в формате: Ширина-Длина-Высота";

                user.setStage(StageQueue::SQUARE);
                user.setState(State::IDLE);
            }
            break;
        }
        case "SQUARE": {
            std::istringstream iss(message->text);
            std::string item;
            std::vector<int> room;
            while (std::getline(iss, item, '-')) {
                room.push_back(std::stoi(item));
            }
            user.storage.insert_or_assign(
                "room", models::Room(
                        room[0],
                        room[1],
                        room[2]
                        )
            );
            user.setStage(StageQueue::WALL);
            user.setState(State::START);
            break;
        }
        default:{

        }
    }

    State state = user.getState();
    switch(state){
        case State::IDLE:{

            break;
        }
        case State::START:{
            keyboard =createKeyboard({
                {"Открыть каталог"},
                {"Загрузить свой узор"},
                {"Шаг назад"},
                {"Следующий раздел"}
            });
            break;
        }
        case State::ADD:{
            break;
        }
        case State::MATERIAL:{
            auto obj = user.storage["wall"];
            auto materials  = obj.getMaterials();
            keyboard = createKeyboard({
                                        materials
                                      });
            user.setState(State::PLATE);
            break;
        }
        case State::PLATE:{
            auto& obj = user.storage["wall"];
            auto materials  = obj.getMaterials();
            auto mat = std::find(materials.begin(), materials.end(), message->text);

            if (mat == materials.end()){
                answerText = "Выберите материал из предложенных";
                break;
            }

            obj.material.name = message->text;

            auto samples = obj.material.getSamples();
            //bot.getApi().sendPhoto();

            keyboard = createKeyboard({
                                              {"1", "2", "3"},
                                              {"4", "5", "6"},
                                              {"7", "8", "9"},
                                              {"Перейти на след. страницу"}
                                      });
            user.setState(State::SET_TEXTURE);
            break;
        }
        case State::SET_TEXTURE:{
            if (message->text == "Перейти на след. страницу"){
                //ПРидумать хуйню тут
            }
            auto plateNum = std::stoi(message->text);

            break;
        }
        case State::CONFIRM:{

            auto& obj = user.storage["wall"];
            //obj.materialType = message->text;

            keyboard = createKeyboard({
                                              {"Оставить"},
                                              {"Назад"}
                                      });
            break;
        }
    }

    bot.getApi().sendMessage(message->chat->id, answerText, false, 0, keyboard);

}
