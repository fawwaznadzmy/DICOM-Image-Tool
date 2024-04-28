#pragma once

#include "myImage.h"

class MyThread{
public:
    MyThread(const std::string& path);
   
    void worker();

private:
    MyImage* image;
};