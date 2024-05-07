#include "gtest/gtest.h"
#include "dicom.h"

// Fixture class for DicomReader tests
class DicomReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary DICOM file for testing
        // Ensure that "test_dicom.dcm" exists with some valid DICOM data
        testFilePath = "D:/Project/Git/DICOM_V2/DICOM-Image-Tool/pictures/dicom/dicom/2248d6d6-4f4f-4aba-8695-afd400d96f36.dcm";
        // Initialize the DicomReader with the test DICOM file
        reader = new DicomReader(testFilePath);
    }

    void TearDown() override {
        // Clean up resources
        delete reader;
    }

    DicomReader* reader;
    std::string testFilePath;
};

// Test fixture for DicomReader constructor
TEST_F(DicomReaderTest, Constructor) {
    // Check if the DicomReader is constructed successfully
    EXPECT_TRUE(reader->isFileValid());
}

// Test fixture for DicomReader displayMetaData method
TEST_F(DicomReaderTest, DisplayMetaData) {
    // Check if displayMetaData returns non-empty string for a valid DICOM file
    EXPECT_FALSE(reader->displayMetaData().empty());
}

// Test fixture for DicomReader displayPatientName method
TEST_F(DicomReaderTest, DisplayPatientName) {
    // Check if displayPatientName returns non-empty string for a valid DICOM file
    EXPECT_FALSE(reader->displayPatientName().empty());
}

// Test fixture for DicomReader getImageData method
TEST_F(DicomReaderTest, GetImageData) {
    int width, height, depth;
    void* imageData = reader->getImageData(width, height, depth);
    // Check if the image data pointer is not null
    EXPECT_NE(imageData, nullptr);
    // Check if the width, height, and depth are greater than 0
    EXPECT_GT(width, 0);
    EXPECT_GT(height, 0);
    EXPECT_GT(depth, 0);
}

