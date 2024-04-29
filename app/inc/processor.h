#pragma once
#include <iostream>
#include "fileHandle.h"

#define _OPENCV_PROC 1

#ifdef _OPENCV_PROC
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
#endif
using namespace std;



class Processor {
public:
    Processor();

    virtual void displayImage(const std::string& title) const = 0;

    virtual void displayHistogram() const= 0;

    virtual void displayMetadata() const = 0;

    virtual void autoCropAndRotateImage() const =0;

    virtual std::string getImageSize() const =0 ;

    virtual void displayWait() const =  0;

    virtual void createImageFromPath (const std::string& path) const = 0;

    virtual void createImageFromPixel(int rows, int cols, uint8_t pixel) const = 0;
        
    static Processor * create();
};





#ifdef _OPENCV_PROC
class OpenCVImageProcessor : public Processor {
public:  
    OpenCVImageProcessor();
    
    void displayImage(const std::string& title) const override;

    void displayHistogram() const override;

    void displayMetadata() const override;

    void autoCropAndRotateImage() const override;

    std::string getImageSize() const override;

    void createImageFromPath (const std::string& path) const override;

    void createImageFromPixel(int rows, int cols, uint8_t pixel) const override;

    void displayWait() const override;

private:
    Mat processAndCropImage(const Mat& src) const;

    Point markingLocation(const Mat& src) const;

    bool isImageNeedToRotate(const Mat& src, Point pnt) const;

protected:
    Mat* m_Image;
};

#else
class CustoMmageProcessor : public Processor {
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