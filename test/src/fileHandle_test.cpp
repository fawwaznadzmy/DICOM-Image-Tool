#include "gtest/gtest.h"
#include <stdio.h>
#include "fileHandle.h"


TEST(fileHandleTest, CheckPngExtension){
    std::string path = "C:/pic/2174d2be-ccf6-4235-bd5f-afd400d96f86.png";
    FileHandle* H_FILE= FileHandle::create(path);
    EXPECT_EQ(H_FILE->getFileExtension(), "png");
}

TEST(fileHandleTest, CheckJpegExtension){
    std::string path = "C:/pic/2174d2be-ccf6-4235-bd5f-afd400d96f86.jpeg";
    FileHandle* H_FILE= FileHandle::create(path);
    EXPECT_EQ(H_FILE->getFileExtension(), "jpeg");
}

TEST(fileHandleTest, CheckDicomExtension){
    std::string path = "C:/pic/2174d2be-ccf6-4235-bd5f-afd400d96f86.dcm";
    FileHandle* H_FILE= FileHandle::create(path);
    EXPECT_EQ(H_FILE->getFileExtension(), "dcm");
}