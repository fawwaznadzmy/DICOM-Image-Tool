#include "gtest/gtest.h"
#include <stdio.h>
#include "fileHandle.h"


class FileHandleTest : public ::testing::Test {
protected:

    std::unique_ptr<IFileHandle> fileHandle; 

    void SetUp() override {
        fileHandle = IFileHandle::create("test_file.txt");
    }

    void TearDown() override {
    }
};

TEST_F(FileHandleTest, checkTxtExtension){
    EXPECT_EQ(fileHandle->getFileExtension(), "txt");
}

TEST_F(FileHandleTest, checkSetGetFilePath){
   std::string path = "C:/pic/2174d2be-ccf6-4235-bd5f-afd400d96f86.dcm";
   EXPECT_EQ(fileHandle->getFilePath(),"test_file.txt");
   fileHandle->setFilePath(path);
   EXPECT_EQ(fileHandle->getFilePath(),path);
}

TEST_F(FileHandleTest, TestSaveFile) {
    EXPECT_TRUE(fileHandle->saveFile("Test content"));
}

TEST_F(FileHandleTest, TestDeleteFile) {
    fileHandle->saveFile("Test content");
    EXPECT_TRUE(fileHandle->deleteFile());
}

TEST_F(FileHandleTest, TestGetFileSize) {
    fileHandle->saveFile("Test content");
    EXPECT_GT(fileHandle->getFileSize(), 0);
}