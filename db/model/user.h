#pragma once
#include <string>
#include "entity.h"

namespace models {
    struct User{
        int id;
        long tg_id;
        std::string tg_nickname;
        std::string name;
    };

};
