#pragma once
#include "fileHandle.h"
#include "processor.h"

class MyImage{ 
public:
    MyImage (const std::string& path);
    
    Processor *processor;
};