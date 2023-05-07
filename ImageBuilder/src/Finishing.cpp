#include "Finishing.h"

void ImageBuilder::Finishing::updateCoords() {
    coords_ = {
            .topLeft =        {0.f,                   0.f},
            .topRight =       {texture_.cols - 1.f,   0.f},
            .bottomLeft =     {0.f,                   texture_.rows - 1.f},
            .bottomRight =    {texture_.cols - 1.f,   texture_.rows - 1.f}
    };
}
