//
// Created by lev on 06.05.23.
//

#pragma once
#include "Config.h"
#include "ImageBuilder.h"

namespace ImageBuilder{
    class ImageProcessor {
    public:
        ImageProcessor(const Config& config) : config_(config) {}

        int loadConfig(const Config& config);
        std::optional<Finishing> createFinishing(const std::string& type, const cv::Mat& texture);
        int pasteFinishing(const Finishing& finishing);
        cv::Mat getRoom();
    private:
        Config config_;
        ImageBuilder builder_;
    };
}
