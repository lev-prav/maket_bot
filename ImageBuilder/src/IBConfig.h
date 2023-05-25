//
// Created by lev on 05.05.23.
//

#pragma once

#include <string>
#include "Finishing.h"

namespace ImageBuilder{
    using CoordinateMap = std::unordered_map<std::string, Coordinates>;

    class IBConfig {
    public:
        IBConfig() = default;
        IBConfig(const std::string& path);
        IBConfig(const CoordinateMap& map);

        int parseJSON(const std::string& path);
        cv::Mat getBaseImg() const;
        CoordinateMap getCoordinateMapping();
        bool checkForType(const std::string& type);
        std::optional<Coordinates> getTypeCoordinate(const std::string& type);

    private:
        int loadBaseImage(const std::string& path);

        cv::Mat baseImg_;
        CoordinateMap finishingCoordinates_;
    };
}
