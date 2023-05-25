//
// Created by lev on 02.05.23.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageBuilder.h"

using namespace cv;

int ImageBuilder::ImageBuilder::addFinishing(const Finishing &finishing, const Coordinates& pasteCoords) {

    auto foreground = multiplyFinishing(pasteCoords, finishing);

    auto inputCoords = foreground.getCoords().toArray();
    // Get the Perspective Transform Matrix i.e. lambda
    auto lambda = getPerspectiveTransform( inputCoords.data(), pasteCoords.toArray().data());
    // Apply the Perspective Transform just found to the src image
    warpPerspective(foreground.getTexture(),base_,lambda,base_.size(),cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);

    return 0;
}

ImageBuilder::Finishing
ImageBuilder::ImageBuilder::multiplyFinishing(const Coordinates &outCoords, const Finishing &finishing) {

//    auto inputPoints = finishing.getCoords();
//    int width = outCoords.getMaxWidth(),
//        height = outCoords.getMaxHeight();
//    int cols = width/inputPoints.getMaxWidth() - 2,
//        rows = height/inputPoints.getMaxHeight() + 3;

    cv::Mat foreground;
    int cols = 5, rows = 12;
    std::cout<<cols<<"x"<<rows<<"\n";

    cv::repeat(finishing.getTexture(), cols,rows,foreground);

    return Finishing(finishing.getType(), foreground);
}

cv::Mat ImageBuilder::ImageBuilder::getRoom() {
    return base_;
}

int ImageBuilder::ImageBuilder::setBase(const Mat &base) {
    base_ = base;
    return 0;
}
