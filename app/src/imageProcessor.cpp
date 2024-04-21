
#include "imageProcessor.h"

ImageProcessor::ImageProcessor(const std::string& imagePath){
    m_originalImage = imread(imagePath);

    if (m_originalImage.empty()) {
        std::cerr << "Error: Unable to load image " << imagePath << std::endl;
        return;
    }
}

void ImageProcessor::processImage() {

    // Process the image (Example: Convert to grayscale)
    Mat invertImage;
    bitwise_not(m_originalImage, invertImage);

    // Convert the image to grayscale
    Mat gray;
    cvtColor(invertImage, gray, COLOR_BGR2GRAY);

    // Apply Otsu's thresholding
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // Find contours
    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Find the largest contour
    double maxArea = 0;
    int maxContourIdx = -1;
    for(size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if(area > maxArea) {
            maxArea = area;
            maxContourIdx = i;
        }
    }

    if(maxContourIdx != -1) {
        Rect boundingRect = cv::boundingRect(contours[maxContourIdx]);
        Mat croppedImage = m_originalImage(boundingRect).clone(); // Clone to ensure independence
        // Display the cropped image
        imshow("Cropped Image", croppedImage);
        waitKey(0);
    }
    waitKey(0);

   // resize(processedImage, processedImage, Size(), 0.75, 0.75);

    // Access and modify pixel values
  /*  for (int y = 0; y < processedImage.rows; ++y) {
        for (int x = 0; x < processedImage.cols; ++x) {
            // Assuming it's a grayscale image
            processedImage.at<unsigned char>(y, x) = 255 - processedImage.at<unsigned char>(y, x); // Invert pixel value
            if( (processedImage.at<unsigned char>(y, x) <= 255) && (processedImage.at<unsigned char>(y, x) >= 155))
                processedImage.at<unsigned char>(y, x) = 0;
        }
    } 
    
     Mat img_bw;
     threshold(processedImage, img_bw, 0, 255, THRESH_OTSU);
    // Show result
    imshow("Result", img_bw);
    waitKey(0);*/
    // Pass the processed image information back to the main thread
    //m_imageInfo = "Image Size: " + std::to_string(processedImage.rows) + "x" + std::to_string(processedImage.cols);
}

std::string ImageProcessor::getImageInfo() const 
{
    return m_imageInfo;
}

Mat ImageProcessor::getOriginalImage() const 
{
    return m_originalImage;
}
