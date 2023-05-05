//
// Created by lev on 02.05.23.
//

#pragma once
#include <string>
#include <opencv2/core/mat.hpp>
#include "Config.h"
#include "Finishing.h"

namespace ImageBuilder{
    class ImageBuilder {
    public:
        ImageBuilder(const Config& config );

        int loadConfig(const Config& config );

        int addFinishing(const std::string& type, cv::Mat texture);
        cv::Mat getRoom();

    private:
        cv::Mat buildFinishing(const Coordinates& outCoords, cv::Mat texture);

        CoordinateMap  finishingCoordinates_;
        cv::Mat base_;
    };
}
