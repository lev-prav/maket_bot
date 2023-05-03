#pragma once

#include "user.h"
#include <vector>
#include <optional>

struct DB{
    std::vector<models::User> get_users(int amount);
    std::optional<models::User> findUser(int user_id);

    int add_user(const models::User& user);
};
