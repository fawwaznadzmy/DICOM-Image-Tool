
#include "imageProcessor.h"

ImageProcessor::ImageProcessor(const std::string& imagePath){
    m_originalImage = imread(imagePath,IMREAD_GRAYSCALE);

    if (m_originalImage.empty()) {
        std::cerr << "Error: Unable to load image " << imagePath << std::endl;
        return;
    }
}

Mat ImageProcessor::markingSegmentation(const Mat& inputImage)
{

    Mat binary;
    threshold(inputImage, binary, 240, 255, THRESH_BINARY);

    return binary;
}

Point ImageProcessor::markingLocation(const Mat& inputImage)
{

    Mat binary;
    double minArea = DBL_MAX;
    int minIdx = -1;

    threshold(inputImage, binary, 240, 255, THRESH_BINARY);

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

Mat ImageProcessor::processAndCropImage(const Mat& inputImage) {
   
    // Convert the image to grayscale
    Mat gray = inputImage.clone();

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
        return inputImage(boundingRec).clone(); // Clone to ensure independence
    }

    // If no contour found, return an empty image
    return Mat();
}

bool ImageProcessor::isImageNeedToRotate(const Mat& inputImage, Point marking)
{
        if (marking.x > inputImage.cols / 2 && marking.y > inputImage.rows / 2) {
          return true;
        }

    return false;
}

void ImageProcessor::processImage() {

    // Process and crop the image
    Mat croppedImage = processAndCropImage(m_originalImage);
    Point mark = markingLocation(croppedImage);

  
     Mat rotated = croppedImage ;
    if(isImageNeedToRotate(croppedImage, mark ))
    {
       rotate(croppedImage, rotated, ROTATE_180);
    }   
            
    
    // Iterate through each pixel
    imshow("Result",  rotated);
    waitKey(0);
}

std::string ImageProcessor::getImageInfo() const 
{
    return m_imageInfo;
}

Mat ImageProcessor::getOriginalImage() const 
{
    return m_originalImage;
}
