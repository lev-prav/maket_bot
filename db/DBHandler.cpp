//
// Created by lev on 16.04.23.
//

#include "DBHandler.h"
#include <iostream>


auto DBHandler::get_storage() {
    using namespace sqlite_orm;
    using namespace models;

    static auto storage = make_storage("market.sqlite",
                                       make_table("Users",
                                                  make_column("ID", &User::id, primary_key().autoincrement()),
                                                  make_column("NAME", &User::name),
                                                  make_column("TG_ID", &User::tg_id),
                                                  make_column("TG_NICKNAME", &User::tg_nickname)
                                       )
    );
    storage.sync_schema();
    return storage;
}

void DBHandler::init_database() {
    using namespace sqlite_orm;
    using namespace models;

    auto storage = get_storage();

    std::cout << "---------------------" << std::endl;
    for(auto& employee: storage.iterate<User>()) {
        std::cout << storage.dump(employee) << std::endl;
    }
}

int DBHandler::addUser(const models::User &user) {
    auto storage = get_storage();

    int user_id = storage.insert(user);

    return user_id;
}

std::optional<models::User> DBHandler::findUser(long userTGid) {
    auto storage = get_storage();

    auto user = storage.select(sql::object<models::User>(),
            (sql::where(sql::c(&models::User::tg_id) == userTGid)));

    if (user.empty())
        return {};
    return user[0];
}

std::vector<std::string> DBHandler::getSamples(std::string material) {
    auto storage = get_storage();

    return {

    };
}
