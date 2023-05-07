#include "opencv2//opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "src/ImageProcessor.h"

using namespace cv;
using namespace std;

using namespace ImageBuilder;

int main(int argc, char** argv)
{
    /*
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
*/
    Mat roof_pic = imread("/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 3 (ПОТОЛОК)/3_plitka_2.png");
    Mat floor_pic = imread("/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 2 (ПОЛ)/2_linol_1.png");
    Mat wall_left_pic =     imread("/home/lev/data/projects/tgBotCpp/res/textures/РАЗДЕЛ - 1 (СТЕНЫ)/1_oboi_5.png");
    Mat wall_right_pic =  wall_left_pic ,
        wall_mid_pic =    wall_right_pic;

    //Mat background = imread("/home/lev/data/projects/tgBotCpp/res/textures/room.png");

    std::map<std::string, cv::Mat> textures;
    textures["roof"]        =   roof_pic;
    textures["floor"]       =   floor_pic;
    textures["wall_left"]   =   wall_left_pic;
    textures["wall_right"]  =   wall_right_pic;
    textures["wall_mid"]    =   wall_mid_pic;


    Config config("/home/lev/data/projects/tgBotCpp/ImageBuilder/config.json");

    ImageProcessor processor(config);
    for(auto& tex : textures){
        auto floor = processor.createFinishing(tex.first, tex.second);
        if (!floor){
            std::cout<<"Can't create finishing\n";
        }
        processor.pasteFinishing(floor.value());

        auto room = processor.getRoom();

        imshow("room", room);
        waitKey();
        cv::destroyAllWindows();
    }


    return 0;
}