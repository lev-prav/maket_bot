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

        int addFinishing(const Finishing &finishing, const Coordinates& pasteCoords);
        cv::Mat getRoom();

    private:
        cv::Mat buildFinishing(const Coordinates& outCoords, cv::Mat texture);
        cv::Mat base_;
    };
}
