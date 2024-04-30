#pragma once

#include "processor.h";
#include "dicom.h";

using namespace std;

class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path);
   
    void displayImage(const std::string& title);

    void autoCropAndRotateImage(){processor->autoCropAndRotateImage();}

    void displayHistogram(){ processor->displayHistogram();}
   
    void displayWait(){ processor->displayWait();}

    std::ostringstream getFileMetadata(){return dicom->displayMetaData();}

    string getPatientName();

    void createImage();

private:
    FileHandle *file;

    Processor* processor;

    DicomReader *dicom;
 
};


