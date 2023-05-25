#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <fstream>

#include <tgbot/tgbot.h>

#include "db/model/mock.h"
#include "db/DBHandler.h"
#include "src/UserState.h"
#include "src/Dispatcher.h"
#include "ImageBuilder/src/IBConfig.h"
#include "ImageBuilder/src/ImageProcessor.h"
#include "src/BotConfig.h"

std::map<std::string, std::vector<std::string>> mock = {
        {"wall" ,  {
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_kamen_1.png"    ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_1.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_2.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_3.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_4.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_5.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_6.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_7.png"     ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_probka_1.png"   ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_vagonka_1.png"
        }},
        {"floor" ,   {
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_kvarz_1.png"  ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_lamin_1.png"  ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_linol_1.png"  ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_plitka_1.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_plitka_2.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_plitka_3.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_plitka_4.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_plitka_5.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_probka_1.png" ,
            "/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_probka_2.png"
        }},
        {"roof",        {}},
        {"floor_board", {}} ,
        {"roof_board",  {}},
        {"furniture",   {}},
        {"stuff" ,      {}}
};

using namespace std;
using namespace TgBot;


int main(int argc, char** argv) {
//    string token("5838544474:AAEBmmC7HIIQte-AVJjHPV6Hzea4mnI5gtw");


    ImageBuilder::IBConfig IBConfig("/home/lev/data/projects/tgBotCpp/config.json");
    ImageBuilder::ImageProcessor processor(IBConfig);
    BotConfig botConfig("/home/lev/data/projects/tgBotCpp/config.json");
    std::string token = botConfig.getToken();
    printf("Token: %s\n", token.c_str());

    auto configStages = botConfig.getStages();

    std::list<std::string> stagesList = {"START", "SQUARE"};
    stagesList.assign( configStages.cbegin(), configStages.cend());
    stagesList.emplace_back("END");

    StageQueue stage(stagesList);

    std::map<long, UserState> states;
    Dispatcher dp;
    DBHandler db;

    Bot bot(token);
    bot.getApi().deleteMyCommands();

    bot.getEvents().onCommand("start", [&bot, &db, &states, stage](Message::Ptr message) {

        auto user= db.findUser(message->from->id);
        if (!user){
            models::User testUser{
                    .tg_id = message->from->id,
                    .tg_nickname = message->from->username,
                    .name = message->from->firstName + " " + message->from->lastName
            };
            testUser.id = db.addUser(testUser);
            states.insert(
                    {testUser.tg_id, UserState(testUser, State::START, stage)}
                    );
            std::cout<<"Add New User!\n";
        }

        states[user->tg_id].setState(State::START);
        std::string messageText = "Здравствуй, дорогой " + user->tg_nickname;

        ReplyKeyboardMarkup::Ptr keyboardWithLayout = createKeyboard({
                               {"Начать редактирование"}
        });

        bot.getApi().sendMessage(message->chat->id, messageText, false, 0, keyboardWithLayout);

        const string photoFilePath = "/home/lev/data/projects/tgBotCpp/res/textures/room.png";
        const string photoMimeType = "image/png";
        auto photo = InputFile::fromFile(photoFilePath, photoMimeType);

        bot.getApi().sendPhoto(message->chat->id, photo);
    });


    bot.getEvents().onAnyMessage([&bot, &states, &dp](Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }

        auto& userState = states[message->from->id];
        dp.handle(bot, userState, message);

//        if (message->text == "Начать редактирование"){
//            bot.getApi().sendMessage(message->chat->id, "Задайте размеры комнаты в формате: ШиринаxДлинаxВысота");
//        }

        //bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}

void getUserState(int64_t id) {

}
