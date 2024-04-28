
#include "myImage.h"

MyImage::MyImage (const std::string& path){
    
    processor = Processor::create(path);
}