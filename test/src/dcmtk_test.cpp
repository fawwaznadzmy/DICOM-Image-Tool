#include "gtest/gtest.h"
#include "dicomInterface.h"
#include "dcmtk.h"


class DicomReaderTest : public ::testing::Test {
protected:
    void SetUp() override {

        testFilePath = "D:/Project/Git/DICOM_V2/DICOM-Image-Tool/pictures/dicom/dicom/2248d6d6-4f4f-4aba-8695-afd400d96f36.dcm";

        reader = new Dcmtk(testFilePath);
    }

    void TearDown() override {

        delete reader;
    }

    IDicomReader* reader;
    std::string testFilePath;
};



TEST_F(DicomReaderTest, Constructor) {
    EXPECT_TRUE(reader->isFileValid());
}


TEST_F(DicomReaderTest, DisplayMetaData) {
    EXPECT_FALSE(reader->getMetaData().empty());
}


TEST_F(DicomReaderTest, DisplayPatientName) {
    EXPECT_FALSE(reader->getPatientName().empty());
}



