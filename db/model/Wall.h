#pragma once

#include "DataObject.h"

namespace models{
    struct Wall : public DataObject{
        std::vector<std::string> getMaterials() override {
            return  {"Обои", "Штукатурка",
                     "Плитка", "Декоративный камень",
                     "Пробка", "Вагонка"};
        }
    };
}