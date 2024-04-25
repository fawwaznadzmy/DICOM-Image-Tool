
#include "processor.h"

Processor::Processor(const std::string& path){
     file = FileHandle::create(path);
}

Processor* Processor::create(const std::string& path) {
#ifdef _OPENCV_PROC
    return new OpenCVImageProcessor(path);
#else
    return new CustoMmageProcessor (path);
#endif
}

#ifdef _OPENCV_PROC
OpenCVImageProcessor::OpenCVImageProcessor(const std::string& path): Processor(path)
{
    std::string ext = file->getFileExtension();

    if(ext == ".dcm"){
        //convert o JPEG

    }

    // for .dcm need to do something
    //
   
    Mat img = imread(path,IMREAD_GRAYSCALE);

    if (img.empty()) {
        std::cerr << "Error: Unable to load image " << path << std::endl;
        return;
    }

    Mat processedImg = processAndCropImage(img);

    Point mark = markingLocation(processedImg);

    m_Image = processedImg ;
    if(isImageNeedToRotate(processedImg, mark ))
    {
       rotate(processedImg, m_Image, ROTATE_180);
    }          
}
    
void OpenCVImageProcessor::displayImage() const{
    imshow("Result", m_Image);
    waitKey(0);
}

void OpenCVImageProcessor::displayHistogram() const{
   // Define histogram parameters
    int histSize = 256; // Number of bins
    float range[] = {0, 256}; // Pixel value range
    const float* histRange = {range};

    // Compute histogram
    Mat hist;
    calcHist(&m_Image, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    // Set histogram plot parameters
    int histWidth = 512;
    int histHeight = 400;
    int binWidth = cvRound((double)histWidth / histSize);
    Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(255, 255, 255));

    // Normalize the histogram
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // Draw histogram
    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(binWidth * (i - 1), histHeight - cvRound(hist.at<float>(i - 1))),
            Point(binWidth * (i), histHeight - cvRound(hist.at<float>(i))),
            Scalar(0, 0, 255), 2, LINE_AA);
    }

        // Draw axes
    line(histImage, Point(0, histHeight), Point(histWidth, histHeight), Scalar(0, 0, 0), 2, LINE_AA); // X-axis
    line(histImage, Point(0, histHeight), Point(0, 0), Scalar(0, 0, 0), 2, LINE_AA); // Y-axis

    // Display the histogram
    imshow("Histogram", histImage);
    waitKey(0);

}

void OpenCVImageProcessor::displayMetadata() const{

}

std::string OpenCVImageProcessor::getImageSize() const{

  return "";
}


Mat OpenCVImageProcessor::processAndCropImage(const Mat& src) {
   
    Mat gray = src.clone();

    // Access and modify pixel values
    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            // Assuming it's a grayscale image
            if(((gray.at<uchar>(y, x) >=0 ) && (gray.at<uchar>(y, x) <= 100)) || 
              (gray.at<uchar>(y, x) >= 230) ) // Invert pixel value
              {
                  gray.at<uchar>(y, x) =255 ;
              }
                
        }
    }

     // Invert the image
    Mat invertedImage;
    bitwise_not(gray, invertedImage);
    
    // Apply Otsu's thresholding
    Mat binary;
    threshold(invertedImage, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // Find contours
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Find the largest contour
    double maxArea = 0;
    int maxContourIdx = -1;
    for(int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if(area > maxArea) {
            maxArea = area;
            maxContourIdx = i;
        }
    }

    // Crop the original image to include only the region within the largest contour
    if(maxContourIdx != -1) {
        Rect boundingRec = boundingRect(contours[maxContourIdx]);
        return src(boundingRec).clone(); // Clone to ensure independence
    }

    // If no contour found, return an empty image
    return Mat();
}


Point OpenCVImageProcessor::markingLocation(const Mat& src)
{

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
        // Get the bounding box of the contour
        Rect bRect = boundingRect(contours[minIdx]);
        Point markingCenter = bRect.tl() + (bRect.br() - bRect.tl()) / 2;

        return markingCenter;
    }

    return Point();
}


bool OpenCVImageProcessor::isImageNeedToRotate(const Mat& src, Point pnt)
{
    if (pnt.x > src.cols / 2 && pnt.y > src.rows / 2) {
        return true;
    }

    return false;
}

#endif