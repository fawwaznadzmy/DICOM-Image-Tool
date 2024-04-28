#pragma once

#include "processor.h";
#include "dicom.h";

using namespace std;

class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path);
   
    void displayImage(const std::string& title){ processor->displayImage(title);}

    void autoCropAndRotateImage(){processor->autoCropAndRotateImage();}

    void displayHistogram(){ processor->displayHistogram();}
   
    void displayWait(){ processor->displayWait();}
private:

    FileHandle *file;
    Processor* processor;
    DicomReader *dicom;
 
};


