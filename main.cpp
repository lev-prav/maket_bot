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


using namespace std;
using namespace TgBot;


int main(int argc, char** argv) {
    string token("5838544474:AAEBmmC7HIIQte-AVJjHPV6Hzea4mnI5gtw");
    printf("Token: %s\n", token.c_str());

    DBHandler db;

    Bot bot(token);
    bot.getApi().deleteMyCommands();

    std::map<long, UserState> states;
    Dispatcher dp;

    bot.getEvents().onCommand("start", [&bot, &db, &states](Message::Ptr message) {

        auto user= db.findUser(message->from->id);
        if (!user){
            models::User testUser{
                    .tg_id = message->from->id,
                    .tg_nickname = message->from->username,
                    .name = message->from->firstName + " " + message->from->lastName
            };
            testUser.id = db.addUser(testUser);
            states.insert(
                    {testUser.tg_id, UserState(testUser, State::START)}
                    );
            std::cout<<"Add New User!\n";
        }

        states[user->tg_id].setState(State::START);
        states[user->tg_id].setStage(Stage::START);
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
