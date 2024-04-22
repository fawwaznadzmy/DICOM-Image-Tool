#pragma once
#include "fileHandle.h"
#include "processor.h"

class Image{ 
public:
    Image (const std::string& path);
    ~Image ();
    FileHandle * file;
    Processor *processor;
};