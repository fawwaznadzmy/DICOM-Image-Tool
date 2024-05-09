#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "processor.h"
#include "dicom.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::NiceMock;

class MockDicomReader : public DicomReader {
public:
    // Constructor
    MockDicomReader(const std::string& path) : DicomReader(path) {}

    MOCK_METHOD0(isFileValid, bool());

    // Mocked method for getting image height
    MOCK_METHOD0(getImageHeight, int());

    // Mocked method for getting image width
    MOCK_METHOD0(getImageWidth, int());

    // Mocked method for getting image depth
    MOCK_METHOD0(getImageDepth, int());

    // Mocked method for getting image output data
    MOCK_METHOD0(getImageOutputData, void*());
};

class MockProcessor: public IProcessor {
public:


    MOCK_METHOD(void, displayImage,(const std::string& title), (const, override));
    MOCK_METHOD(void, displayHistogram,(), (const,override));
    MOCK_METHOD(void, displayMetadata,(),(const,override));
    MOCK_METHOD(void, autoCropAndRotateImage,(), (const,override));
    MOCK_METHOD(std::string, getImageSize,(), (const,override));
    MOCK_METHOD(void, displayWait,(), (const,override));
    MOCK_METHOD(void, createImageFromPath, (const std::string& path),(const,override));
    MOCK_METHOD(void, createImagefromDicom,(DicomReader *dcm),(const,override));
        
};


class ProcessorTest : public ::testing::Test {
protected:

    NiceMock<MockProcessor> mockProcessor;
};


TEST_F(ProcessorTest, DisplayImage) {
    const std::string title = "Test Image";
 
    EXPECT_CALL(mockProcessor, displayImage(title));
    mockProcessor.displayImage(title);
}


TEST_F(ProcessorTest, DisplayHistogram) {

    EXPECT_CALL(mockProcessor, displayHistogram());

    mockProcessor.displayHistogram();
}


TEST_F(ProcessorTest, DisplayMetadata) {
 
    EXPECT_CALL(mockProcessor, displayMetadata());

    mockProcessor.displayMetadata();
}


TEST_F(ProcessorTest, AutoCropAndRotateImage) {

    EXPECT_CALL(mockProcessor, autoCropAndRotateImage());

    mockProcessor.autoCropAndRotateImage();
}


TEST_F(ProcessorTest, GetImageSize) {

    EXPECT_CALL(mockProcessor, getImageSize())
        .WillOnce(Return("100x100")); 

    std::string size = mockProcessor.getImageSize();

    EXPECT_EQ(size, "100x100");
}


TEST_F(ProcessorTest, DisplayWait) {

    EXPECT_CALL(mockProcessor, displayWait());

    mockProcessor.displayWait();
}


TEST_F(ProcessorTest, CreateImageFromPath) {
    const std::string path = "path/to/your/image.jpg";

    EXPECT_CALL(mockProcessor, createImageFromPath(path));

    mockProcessor.createImageFromPath(path);
}





