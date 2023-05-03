#include <algorithm>
#include "mock.h"


std::vector<models::User> DB::get_users(int amount) {
        std::vector<models::User> users(amount);

        for(int i = 0; i < amount;i++){
            users[i] = {
                    .tg_id = i,
                    .tg_nickname = "ds",
                    .name = "dsdasd"
                };
        }
        return users;
}

std::optional<models::User> DB::findUser(int user_id) {
    auto users = get_users(5);
    auto target_user = std::find_if(users.begin(), users.end(),[&user_id](const models::User& user ){
        return user.tg_id == user_id;
    });

    if (target_user == users.end())
        return {};

    return *target_user;
}

int DB::add_user(const models::User &user) {

    return 0;
}
