#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

namespace ImageBuilder{
    struct Coordinates{
        cv::Point2f topLeft,
                    topRight,
                    bottomLeft,
                    bottomRight;

        inline std::array<cv::Point2f, 4> toArray() const {
            return {topLeft, topRight, bottomLeft, bottomRight};
        };

        inline int getMaxWidth() const{
            int minLeft = std::min(topLeft.x, bottomLeft.x),
                maxRight = std::max(topRight.x, bottomRight.x);

            return maxRight - minLeft;
        }
        inline int getMaxHeight() const{
            int minTop = std::min(topLeft.y, topRight.y),
                maxBottom = std::max(bottomLeft.y, bottomRight.y);

            return maxBottom - minTop;
        }
    };

    class Finishing{
    public:
        Finishing(const std::string& type, const cv::Mat& texture) :
        type_(type), texture_(texture)
        {
            updateCoords();
        }

        cv::Mat getTexture() const{
            return texture_;
        }
        Coordinates getCoords() const{
            return coords_;
        }

        std::string getType() const{
            return type_;
        }

    private:

        void updateCoords();

        std::string type_;
        cv::Mat texture_;
        Coordinates coords_;
    };
}