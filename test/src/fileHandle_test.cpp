#include "gtest/gtest.h"
#include <stdio.h>
#include "fileHandle.h"

namespace {
    int ReturnValue(){return 88;}
}

TEST(fileHandleTest, Return){
    EXPECT_EQ(ReturnValue(), 88);
}

TEST(fileHandle, CheckExtension){
    std::string path = "C:/pic/2174d2be-ccf6-4235-bd5f-afd400d96f86.png";
    FileHandle* H_FILE= FileHandle::create(path);
    EXPECT_EQ(H_FILE->getFileExtension(), ".png");
}