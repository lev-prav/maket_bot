#pragma once

#include "DataObject.h"

namespace models{
    struct Room : public DataObject{
        Room(int width, int length, int height) :
        width_(width), length_(length), height_(height)
        {}
        std::vector<std::string> getMaterials() override {
            return  {"Default"};
        }

        int width_, length_, height_;
    };
}