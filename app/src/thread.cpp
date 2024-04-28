#include "thread.h"

MyThread::MyThread(const std::string& path){
   image = new MyImage(path);
}
 
void MyThread::worker(){
   image->processor->displayImage("Original");

   image->processor->autoCropAndRotateImage();
   image->processor->displayImage("Auto Crop and Rotate");
   image->processor->displayHistogram();
   
   image->processor->displayWait();
}