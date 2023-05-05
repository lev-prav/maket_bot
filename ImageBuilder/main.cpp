#include "opencv2//opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read the images
    Mat foreground_ = imread("/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 3 (ПОТОЛОК)/3_plitka_2.png");
    Mat background = imread("/home/lev/data/projects/tgBotCpp/res/textures/room.png");

    // Input Quadilateral or Image plane coordinates
    Point2f inputQuad[4];
    // Output Quadilateral or World plane coordinates
    Point2f outputQuad[4];
    cv::Mat foreground;
    cv::repeat(foreground_, 5,14,foreground);

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
    warpPerspective(foreground,background,lambda,background.size(),cv::INTER_LINEAR, cv::BORDER_TRANSPARENT);

    imshow("dsd", background);
    waitKey();

    return 0;
}