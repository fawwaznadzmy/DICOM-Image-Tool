
#include "imageProcessor.h"
#include "matplotlibcpp.h"

#include "Python.h"
#include <vector>
namespace plt = matplotlibcpp;


IProcessor::IProcessor(){

}

std::unique_ptr<IProcessor> IProcessor::create() {
#ifdef _OPENCV_PROC
    return std::make_unique<OpenCVImageProcessor>();
#else
    return std::make_unique<CustoMmageProcessor> ();
#endif
}

#ifdef _OPENCV_PROC
OpenCVImageProcessor::OpenCVImageProcessor(): IProcessor()
{
   m_Image = std::make_unique<cv::Mat>();
}

OpenCVImageProcessor::~OpenCVImageProcessor(){

}
void OpenCVImageProcessor::createImageFromPath(const std::string& path) const {
   
    *m_Image  = cv::imread(path,cv::IMREAD_GRAYSCALE);

    if (m_Image->empty()) {
        std::cerr << "Error: Unable to load image " << path << std::endl;
    } 
}

void OpenCVImageProcessor::createImagefromDicom(IDicomReader* dcm) const{
 
 if(dcm->isFileValid()){}
    cv::Mat imgDcm(int(dcm->getImageHeight()), int(dcm->getImageWidth()), 
    CV_MAKETYPE(dcm->getImageDepth(), 1), (long*)dcm->getImageOutputData());

    // Define the desired width for the resized image
    int target_width = 900;

    // Calculate the corresponding height to maintain the aspect ratio
    int target_height = static_cast<int>(imgDcm.rows * static_cast<double>(target_width) / imgDcm.cols);

    // Resize the image
    cv::Mat resized_image;
    cv::resize(imgDcm, resized_image, cv::Size(target_width, target_height));
    *m_Image = resized_image;
}
    
void OpenCVImageProcessor::createImageFromRaw(int width, int height, int depth, long* data, int resize) const{
    cv::Mat img(height, width, CV_MAKETYPE(depth,1), data);

    if(resize > 0){
        cv::Mat resized_image;

        int newWidth = static_cast<int>(img.cols  * (resize / 100.0));
        int newHeight = static_cast<int>(img.rows  * (resize / 100.0));
        cv::resize(img, resized_image, cv::Size(newWidth,newHeight));

        *m_Image = resized_image;
    }else{
        *m_Image = img;
    }
}

void OpenCVImageProcessor::displayImage(const std::string& title) const{
    cv::imshow(title, *m_Image);
}

void OpenCVImageProcessor::displayHistogram() const{


    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Pixel value range
    const float* histRange = {range};

    cv::Mat hist;
    calcHist(m_Image.get(), 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    int histWidth = 512;
    int histHeight = 400;
    int binWidth = cvRound((double)histWidth / histSize);
    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; i++) {
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(hist.at<float>(i - 1))),
            cv::Point(binWidth * (i), histHeight - cvRound(hist.at<float>(i))),
            cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
    }


    cv::imshow("Histogram", histImage);

}


void OpenCVImageProcessor::displayWait() const{
   cv::waitKey(0);
}

void OpenCVImageProcessor::autoCropAndRotateImage() const{

    cv::Mat img = *m_Image;

    const cv::Mat processedImg = processAndCropImage(img);
    const cv::Point mark = markingLocation(processedImg);

    if(isImageNeedToRotate(processedImg, mark ))
    {
       cv::rotate(processedImg, img, cv::ROTATE_180);
    }  

    *m_Image = img;
}

std::string OpenCVImageProcessor::getImageSize() const{

  return "";
}


cv::Mat OpenCVImageProcessor::processAndCropImage(const cv::Mat& src) const{
   
    cv::Mat gray = src.clone();

    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            if(((gray.at<uchar>(y, x) >=0 ) && (gray.at<uchar>(y, x) <= 100)) || 
              (gray.at<uchar>(y, x) >= 230) ) // Invert pixel value
              {
                  gray.at<uchar>(y, x) =255 ;
              }
                
        }
    }

    cv::Mat invertedImage;
    cv::bitwise_not(gray, invertedImage);
    
    cv::Mat binary;
    cv::threshold(invertedImage, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    double maxArea = 0;
    int maxContourIdx = -1;
    for(int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if(area > maxArea) {
            maxArea = area;
            maxContourIdx = i;
        }
    }

    if(maxContourIdx != -1) {
        cv::Rect boundingRec = cv::boundingRect(contours[maxContourIdx]);
        return src(boundingRec).clone(); 
    }

    return cv::Mat();
}


cv::Point OpenCVImageProcessor::markingLocation(const cv::Mat& src) const {

    cv::Mat binary;
    double minArea = DBL_MAX;
    int minIdx = -1;

    cv::threshold(src, binary, 240, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours,  cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) 
    {
        double area = cv::contourArea(contours[i]);
       
        if (area < minArea && area != 0.00) {
            minArea = area;
            minIdx = i;
        }
    }

    if (minIdx != -1) 
    {
        cv::Rect bRect = cv::boundingRect(contours[minIdx]);
        cv::Point markingCenter = bRect.tl() + (bRect.br() - bRect.tl()) / 2;

        return markingCenter;
    }

    return cv::Point();
}


bool OpenCVImageProcessor::isImageNeedToRotate(const cv::Mat& src, cv::Point pnt)const {
    if (pnt.x > src.cols / 2 && pnt.y > src.rows / 2) {
        return true;
    }

    return false;
}

#endif