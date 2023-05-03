#pragma once

#include <string>
#include <vector>
#include "../DBHandler.h"

namespace models{
    struct Material{
        std::string name;
        std::vector<std::string> getSamples(){
            auto samples = DBHandler::getSamples(name);
            return samples;
        }
    };
}