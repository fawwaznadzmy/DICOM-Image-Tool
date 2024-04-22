#include "thread.h"

MyThread::MyThread(const std::string& path){
   image = new Image(path);
}
 
MyThread::~MyThread(){

}
 
void MyThread::worker(){
   image->processor->displayImage();
   image->processor->displayHistogram();
}