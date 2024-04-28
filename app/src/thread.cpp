#include "thread.h"
//#include "matplotlibcpp.h"
//namespace plt = matplotlibcpp;

MyThread::MyThread(const std::string& path){
   image = new MyImage(path);
}
 
void MyThread::worker(){

  // plt::plot({1,2,3,4}, "*");
  //  plt::show();
   image->processor->displayImage("Original");

   image->processor->autoCropAndRotateImage();
   image->processor->displayImage("Auto Crop and Rotate");
   image->processor->displayHistogram();
   
   image->processor->displayWait();
}