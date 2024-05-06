#include "gtest/gtest.h"
#include <stdio.h>
#include "fileHandle.h"

// Define a test fixture for the WindowsFileHandle class
class FileHandleTest : public ::testing::Test {
protected:
    // Member variables accessible within the fixture
    FileHandle* fileHandle; // Pointer to WindowsFileHandle instance

    // This method will be called before each test case
    void SetUp() override {
        // Perform any necessary setup actions here
        // For example, create a new WindowsFileHandle instance
        fileHandle = FileHandle::create("test_file.txt");
    }

    // This method will be called after each test case
    void TearDown() override {
        // Perform any necessary teardown actions here
        // For example, delete the WindowsFileHandle instance
        delete fileHandle;
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

// Define test cases using the WindowsFileHandleTest fixture
TEST_F(FileHandleTest, TestSaveFile) {
    // Test saving a file using WindowsFileHandle
    EXPECT_TRUE(fileHandle->saveFile("Test content"));
}

TEST_F(FileHandleTest, TestDeleteFile) {
    // Test deleting a file using WindowsFileHandle
    // Assuming saveFile method is tested separately and works
    fileHandle->saveFile("Test content");
    EXPECT_TRUE(fileHandle->deleteFile());
}

TEST_F(FileHandleTest, TestGetFileSize) {
    // Test getting the file size using WindowsFileHandle
    // Assuming saveFile method is tested separately and works
    fileHandle->saveFile("Test content");
    EXPECT_GT(fileHandle->getFileSize(), 0); // File size should be greater than 0
}