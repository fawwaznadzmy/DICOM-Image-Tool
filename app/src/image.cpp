
#include "image.h"

Image::Image (const std::string& path){
    file = FileHandle::create(path);
    processor = Processor::create(path);
}