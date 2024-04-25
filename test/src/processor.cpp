#include "gtest/gtest.h"

namespace {
    int ReturnValue(){return 88;}
}

TEST(ProcessorTest, Return){
    EXPECT_EQ(ReturnValue(), 88);
}