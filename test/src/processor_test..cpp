#include "gtest/gtest.h"
#include "processor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Declare test class as a friend to access private members
/*class ProcessorTest : public testing::Test {
protected:
    bool isImageNeedToRotate(Processor& obj, const Mat& src, Point pnt) {
        return obj.isImageNeedToRotate(const Mat& src, Point pnt);
    }
};

TEST(ProcessorTest, ImageRotation) {
    Processor obj;
    ProcessorTest tester; // Create a tester object to access private members
    bool result = tester.isImageNeedToRotate(obj, 3, 4);
    ASSERT_EQ(result, TRUE);
}*/

