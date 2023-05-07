//
// Created by lev on 02.05.23.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "ImageBuilder.h"

using namespace cv;

int ImageBuilder::ImageBuilder::addFinishing(const Finishing &finishing, const Coordinates& pasteCoords) {

    // Input Quadilateral or Image plane coordinates
//    Point2f inputQuad[4];
//    // Output Quadilateral or World plane coordinates
//    Point2f outputQuad[4];
    // The 4 points that select quadilateral on the input , from top-left in clockwise order
    // These four pts are the sides of the rect box used as input
//    inputQuad[0] = Point2f( 0.f,0.f );
//    inputQuad[1] = Point2f( foreground.cols - 1, 0.f);
//    inputQuad[2] = Point2f( 0.f, foreground.rows - 1);
//    inputQuad[3] = Point2f( foreground.cols - 1, foreground.rows - 1);
//    // The 4 points where the mapping is to be done , from top-left in clockwise order
//    outputQuad[0] = Point2f( 0.f, 0.f );
//    outputQuad[1] = Point2f( 1600.f - 1 + 20,0.f);
//    outputQuad[2] = Point2f( 327.f, 203.f);
//    outputQuad[3] = Point2f( 1293.f, 203.f);

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
