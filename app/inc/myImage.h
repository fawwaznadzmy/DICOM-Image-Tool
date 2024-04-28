#pragma once
#include "fileHandle.h"
#include "processorAdapter.h"

class MyImage: public ProcessorAdapter{ 
public:
    MyImage (const std::string& path);
    

};