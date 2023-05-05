//
// Created by lev on 05.05.23.
//

#pragma once

#include <string>
#include "Finishing.h"

namespace ImageBuilder{
    using CoordinateMap = std::unordered_map<std::string, Coordinates>;

    class Config {
    public:
        Config(const std::string& path);

        CoordinateMap getCoordinatsMapping();

    private:
        CoordinateMap finishingCoordinates_;
    };
}
