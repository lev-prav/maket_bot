//
// Created by lev on 06.05.23.
//

#pragma once
#include "Config.h"
#include "ImageBuilder.h"

namespace ImageBuilder{
    class ImageProcessor {
    public:
        explicit ImageProcessor(const Config& config){
            loadConfig(config);
        }

        int loadConfig(const Config& config);
        std::optional<Finishing> createFinishing(const std::string& type, const cv::Mat& texture);
        int pasteFinishing(const Finishing& finishing);
        cv::Mat getRoom();
    private:
        int updateBuilder(const Config &config);

        Config config_;
        ImageBuilder builder_;
    };
}
