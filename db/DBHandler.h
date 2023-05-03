//
// Created by lev on 16.04.23.
//

#pragma once
#include "model/user.h"
#include <sqlite_orm/sqlite_orm.h>
#include <vector>
#include <optional>

namespace sql =  sqlite_orm;

class DBHandler {
public:
    DBHandler(){
        init_database();
    }

    int addUser(const models::User& user);
    std::optional<models::User> findUser(long userTGid);
    static std::vector<std::string> getSamples(std::string material);

private:
    void init_database();

    static auto get_storage();

    //sqlite_orm::internal::storage_base storage;
};
