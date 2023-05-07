//
// Created by lev on 06.05.23.
//

#include "ImageProcessor.h"

std::optional<ImageBuilder::Finishing>
ImageBuilder::ImageProcessor::createFinishing(const std::string &type, const cv::Mat& texture) {
    if (!config_.checkForType(type))
        return {};

    return Finishing(type, texture);
}

int ImageBuilder::ImageProcessor::pasteFinishing(const Finishing &finishing) {
    auto type = config_.getTypeCoordinate(finishing.getType());
    if (!type)
        return EXIT_FAILURE;

    return builder_.addFinishing(finishing, type.value());;
}

cv::Mat ImageBuilder::ImageProcessor::getRoom() {
    return builder_.getRoom();
}

int ImageBuilder::ImageProcessor::loadConfig(const Config &config) {
    config_ = config;
    return 0;
}
