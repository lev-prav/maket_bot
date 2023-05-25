
#pragma once
#include "IBConfig.h"
#include "ImageBuilder.h"

namespace ImageBuilder{
    class ImageProcessor {
    public:
        explicit ImageProcessor(const IBConfig& config){
            loadConfig(config);
        }

        int loadConfig(const IBConfig& config);
        std::optional<Finishing> createFinishing(const std::string& type, const cv::Mat& texture);
        int pasteFinishing(const Finishing& finishing);
        cv::Mat getRoom();
    private:
        int updateBuilder(const IBConfig &config);

        IBConfig config_;
        ImageBuilder builder_;
    };
}
