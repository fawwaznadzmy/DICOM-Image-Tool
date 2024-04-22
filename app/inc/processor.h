#pragma once
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

class Processor {
public:
    Processor(const std::string& path);

    virtual void displayImage() const = 0;

    virtual void displayHistogram() const= 0;

    virtual void displayMetadata() const = 0;

    virtual std::string getImageSize() const =0 ;
        
    // Factory method to create ImageProcessor object based on OS
    static Processor * create(const std::string& path);
};


class OpenCVImageProcessor : public Processor {
public:  
    OpenCVImageProcessor(const std::string& path);
    
    void displayImage() const override;

    void displayHistogram() const override;

    void displayMetadata() const override;

    std::string getImageSize() const override;

private:
    Mat processAndCropImage(const Mat& src);

    Point markingLocation(const Mat& src);

    bool isImageNeedToRotate(const Mat& src, Point pnt);

    Mat m_Image;
};


class CustoMmageProcessor : public Processor {
public:
    CustoMmageProcessor(const std::string& path):Processor(path){};
    
    void displayImage() const override;

    void displayHistogram() const override;

    void displayMetadata() const override;

    std::string getImageSize() const override;

};