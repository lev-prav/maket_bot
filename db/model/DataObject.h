#pragma once

#include <string>
#include <vector>
#include "Material.h"

namespace models{
    struct DataObject {
        Material material;
        virtual std::vector<std::string> getMaterials(){};
    };
}