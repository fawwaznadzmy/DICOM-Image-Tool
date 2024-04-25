
#include "image.h"

Image::Image (const std::string& path){
    
    processor = Processor::create(path);
}