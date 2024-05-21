#include "gtest/gtest.h"
#include "dicomInterface.h"
#include "dcmtk.h"

class DicomFileTest : public ::testing::Test {
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


TEST_F(DicomFileTest, Constructor) {
    EXPECT_TRUE(reader->isFileValid());
}


TEST_F(DicomFileTest, GetMetaData) {
    EXPECT_FALSE(reader->getMetaData().empty());
}

TEST_F(DicomFileTest, GetPatientName) {
    EXPECT_FALSE(reader->getPatientName().empty());
    EXPECT_EQ(reader->getPatientName(),"Dental^Dennis");
}

TEST_F(DicomFileTest, GetImageHeight) {
    EXPECT_NE(reader->getImageHeight(), 0);
}

TEST_F(DicomFileTest, GetImageWidth) {
    EXPECT_NE(reader->getImageWidth(), 0);
}

TEST_F(DicomFileTest, GetImageDepth) {
    EXPECT_NE(reader->getImageDepth(), 0);
}

/*Non dicom file test exception test*/
class NonDicomFileTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFilePath = "D:/Project/Git/DICOM_V2/DICOM-Image-Tool/pictures/dicom/dicom/2174d2be-ccf6-4235-bd5f-afd400d96f86.jpeg";
        reader = new Dcmtk(testFilePath);
    }
    void TearDown() override {
        delete reader;
    }

    IDicomReader* reader;
    std::string testFilePath;
};

TEST_F(NonDicomFileTest, Construction) {
    EXPECT_FALSE(reader->isFileValid());
}

TEST_F(NonDicomFileTest, GetMetaData) {
    EXPECT_THROW(reader->getMetaData(), std::runtime_error);
}

TEST_F(NonDicomFileTest, GetPatientName) {
    EXPECT_THROW(reader->getPatientName(), std::runtime_error);
}

TEST_F(NonDicomFileTest, GetImageHeight) {
    EXPECT_THROW(reader->getImageHeight(), std::runtime_error);
}

TEST_F(NonDicomFileTest, GetImageWidth) {
    EXPECT_THROW(reader->getImageWidth(), std::runtime_error);
}

TEST_F(NonDicomFileTest, GetImageDepth) {
    EXPECT_THROW(reader->getImageDepth(), std::runtime_error);
}


