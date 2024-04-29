
#include "processor.h"

Processor::Processor(){
     
}

Processor* Processor::create() {
#ifdef _OPENCV_PROC
    return new OpenCVImageProcessor();
#else
    return new CustoMmageProcessor (path);
#endif
}

#ifdef _OPENCV_PROC
OpenCVImageProcessor::OpenCVImageProcessor(): Processor()
{
  m_Image = new cv::Mat;
}

void OpenCVImageProcessor::createImageFromPath (const std::string& path) const{
   
    *m_Image = imread(path,IMREAD_GRAYSCALE);

    if (m_Image->empty()) {
        std::cerr << "Error: Unable to load image " << path << std::endl;
    }   
}

void OpenCVImageProcessor::createImageFromPixel(int rows, int cols, uint8_t pixel) const{

     Mat image(rows, cols, CV_8UC1, pixel); 
     *m_Image = image;

}
    
void OpenCVImageProcessor::displayImage(const std::string& title) const{
    imshow(title, *m_Image);
}

void OpenCVImageProcessor::displayHistogram() const{


    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Pixel value range
    const float* histRange = {range};


    Mat hist;
    calcHist(m_Image, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    int histWidth = 512;
    int histHeight = 400;
    int binWidth = cvRound((double)histWidth / histSize);
    Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());


    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(binWidth * (i - 1), histHeight - cvRound(hist.at<float>(i - 1))),
            Point(binWidth * (i), histHeight - cvRound(hist.at<float>(i))),
            Scalar(255, 255, 255), 2, LINE_AA);
    }

    imshow("Histogram", histImage);

}



void OpenCVImageProcessor::displayMetadata() const{

}

void OpenCVImageProcessor::displayWait() const{
   waitKey(0);
}

void OpenCVImageProcessor::autoCropAndRotateImage() const{

    Mat img = *m_Image;

    const Mat processedImg = processAndCropImage(img);
    const Point mark = markingLocation(processedImg);

    if(isImageNeedToRotate(processedImg, mark ))
    {
       rotate(processedImg, img, ROTATE_180);
    }  

    *m_Image = img;
}

std::string OpenCVImageProcessor::getImageSize() const{

  return "";
}


Mat OpenCVImageProcessor::processAndCropImage(const Mat& src) const{
   
    Mat gray = src.clone();

    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            if(((gray.at<uchar>(y, x) >=0 ) && (gray.at<uchar>(y, x) <= 100)) || 
              (gray.at<uchar>(y, x) >= 230) ) // Invert pixel value
              {
                  gray.at<uchar>(y, x) =255 ;
              }
                
        }
    }

    Mat invertedImage;
    bitwise_not(gray, invertedImage);
    
    Mat binary;
    threshold(invertedImage, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    double maxArea = 0;
    int maxContourIdx = -1;
    for(int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if(area > maxArea) {
            maxArea = area;
            maxContourIdx = i;
        }
    }

    if(maxContourIdx != -1) {
        Rect boundingRec = boundingRect(contours[maxContourIdx]);
        return src(boundingRec).clone(); 
    }

    return Mat();
}


Point OpenCVImageProcessor::markingLocation(const Mat& src) const {

    Mat binary;
    double minArea = DBL_MAX;
    int minIdx = -1;

    threshold(src, binary, 240, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(binary, contours,  RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++) 
    {
        double area = contourArea(contours[i]);
       
        if (area < minArea && area != 0.00) {
            minArea = area;
            minIdx = i;
        }
    }

    if (minIdx != -1) 
    {
        Rect bRect = boundingRect(contours[minIdx]);
        Point markingCenter = bRect.tl() + (bRect.br() - bRect.tl()) / 2;

        return markingCenter;
    }

    return Point();
}


bool OpenCVImageProcessor::isImageNeedToRotate(const Mat& src, Point pnt)const {
    if (pnt.x > src.cols / 2 && pnt.y > src.rows / 2) {
        return true;
    }

    return false;
}

#endif