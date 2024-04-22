#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class ImageProcessor {
public:
    ImageProcessor(const std::string& imagePath);

    void processImage();

    std::string getImageInfo() const;
    Mat getOriginalImage() const;

private:
    Mat processAndCropImage(const Mat& inputImage);
    Point markingLocation(const Mat& inputImage);
    Mat markingSegmentation(const Mat& inputImage);
    bool isImageNeedToRotate(const Mat& inputImage, Point marking);
    Mat m_originalImage;
    string m_imageInfo;
};