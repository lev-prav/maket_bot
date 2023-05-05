#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

namespace ImageBuilder{
    struct Coordinates{
        cv::Point2f topLeft,
                    topRight,
                    bottomLeft,
                    bottomRight;
    };

    class Finishing{
    public:
        Finishing(const std::string& type, const cv::Mat& texture) :
        type_(type), texture_(texture)
        {
            coords_ = {
              .topLeft =        {0.f,                   0.f},
              .topRight =       {texture_.cols - 1.f,   0.f},
              .bottomLeft =     {0.f,                   texture_.rows - 1.f},
              .bottomRight =    {texture_.cols - 1.f,   texture_.rows - 1.f}
            };
        }

        cv::Mat getTexture();
        Coordinates getCoords();

    private:
        std::string type_;
        cv::Mat texture_;
        Coordinates coords_;
    };
}