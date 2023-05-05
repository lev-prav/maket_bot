//
// Created by lev on 02.05.23.
//

#include <opencv2/imgproc.hpp>
#include "ImageBuilder.h"

using namespace cv;

int ImageBuilder::ImageBuilder::addFinishing(const std::string &type, cv::Mat texture) {

    // Input Quadilateral or Image plane coordinates
    Point2f inputQuad[4];
    // Output Quadilateral or World plane coordinates
    Point2f outputQuad[4];

    auto texturePosition = finishingCoordinates_[type];

    auto foreground = buildFinishing(texturePosition, texture);

    // The 4 points that select quadilateral on the input , from top-left in clockwise order
    // These four pts are the sides of the rect box used as input
    inputQuad[0] = Point2f( 0.f,0.f );
    inputQuad[1] = Point2f( foreground.cols - 1, 0.f);
    inputQuad[2] = Point2f( 0.f, foreground.rows - 1);
    inputQuad[3] = Point2f( foreground.cols - 1, foreground.rows - 1);
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0.f, 0.f );
    outputQuad[1] = Point2f( 1600.f - 1 + 20,0.f);
    outputQuad[2] = Point2f( 327.f, 203.f);
    outputQuad[3] = Point2f( 1293.f, 203.f);


    // Get the Perspective Transform Matrix i.e. lambda
    auto lambda = getPerspectiveTransform( inputQuad, outputQuad);
    // Apply the Perspective Transform just found to the src image
    warpPerspective(foreground,base_,lambda,base_.size(),cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);

    imshow("dsd", base_);
    waitKey();
    return 0;
}

cv::Mat ImageBuilder::ImageBuilder::buildFinishing(const Coordinates &outCoords, cv::Mat texture) {
    cv::Mat foreground;
    int cols = 5, rows = 14;

    cv::repeat(texture, cols,rows,foreground);

    return foreground;
}

cv::Mat ImageBuilder::ImageBuilder::getRoom() {
    return base_;
}
