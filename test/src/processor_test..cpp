#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include "imageProcessor.h"
#include "dcmtk.h"
#include "dicomInterface.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::NiceMock;

class MockProcessor: public IProcessor {
public:

    MOCK_METHOD(void, displayImage,(const std::string& title), (const, override));
    MOCK_METHOD(void, displayHistogram,(), (const,override));
    MOCK_METHOD(void, autoCropAndRotateImage,(), (const,override));
    MOCK_METHOD(std::string, getImageSize,(), (const,override));
    MOCK_METHOD(void, displayWait,(), (const,override));
    MOCK_METHOD(void, createImageFromPath, (const std::string& path),(const,override));
    MOCK_METHOD(void, createImagefromDicom,(IDicomReader* dcm),(const,override));
    MOCK_METHOD(void, createImageFromRaw,(int width, int height, int depth, long* data, int size),(const,override));
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





