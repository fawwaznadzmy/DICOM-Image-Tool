#include "thread.h"

MyThread::MyThread(const std::string& path){
   image = new MyImage(path);
}
 
void MyThread::worker(){

   image->displayImage("Original");

   image->autoCropAndRotateImage();
   image->displayImage("Auto Crop and Rotate");
   image->displayHistogram();
   
   image->displayWait();
}