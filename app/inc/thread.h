#pragma once

#include "image.h";

class MyThread{
public:
    MyThread(const std::string& path);
   
    ~MyThread();
   
    void worker();

private:
    Image* image;
};