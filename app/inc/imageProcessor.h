#pragma once
#include <iostream>
#include "dicomInterface.h"

#define _OPENCV_PROC 1

#ifdef _OPENCV_PROC
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
//using namespace cv;
#endif


class IProcessor {
public:
    IProcessor();

    virtual ~IProcessor() = default;

    virtual void displayImage(const std::string& title) const = 0;

    virtual void displayHistogram() const= 0;

    virtual void autoCropAndRotateImage() const =0;

    virtual std::string getImageSize() const =0 ;

    virtual void displayWait() const =  0;

    virtual void createImageFromPath (const std::string& path) const =  0;

    virtual void createImagefromDicom(IDicomReader* dcm) const = 0;

    virtual void createImageFromRaw(int width, int height, int depth, long* data, int resize) const = 0;
        
    static std::unique_ptr<IProcessor> create();
};



#ifdef _OPENCV_PROC

class OpenCVImageProcessor : public IProcessor {
public:  
    OpenCVImageProcessor();

    ~OpenCVImageProcessor();
    
    void displayImage(const std::string& title) const override;

    void displayHistogram() const override;

    void autoCropAndRotateImage() const override;

    std::string getImageSize() const override;

    void createImageFromPath (const std::string& path) const override;

    void createImagefromDicom(IDicomReader* dcm) const override;

    void createImageFromRaw(int width, int height, int depth, long* data, int resize) const override;

    void displayWait() const override;

private:
    cv::Mat processAndCropImage(const cv::Mat& src) const;

    cv::Point markingLocation(const cv::Mat& src) const;

    bool isImageNeedToRotate(const cv::Mat& src, cv::Point pnt) const;

    std::unique_ptr<cv::Mat> m_Image;
    
};

#else
class CustoMmageProcessor : public IProcessor {
public:
    CustoMmageProcessor():Processor(){};
    
    void displayImage() const override;

    void displayHistogram() const override;

    void displayMetadata() const override;

    std::string getImageSize() const override;

    void createImageFromPath (const std::string& path) const override;

    void displayWait() const override;

};

#endif