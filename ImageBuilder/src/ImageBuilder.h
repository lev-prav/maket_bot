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

        int setBase(const cv::Mat& base);
        int addFinishing(const Finishing &finishing, const Coordinates& pasteCoords);
        cv::Mat getRoom();

    private:
        Finishing multiplyFinishing(const Coordinates& outCoords,const Finishing &finishing);
        cv::Mat base_;
    };
}
