#pragma once

#include "processor.h";
#include "dicom.h";



class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path);
   
    void displayImage(const std::string& title);

    void autoCropAndRotateImage(){processor->autoCropAndRotateImage();}

    void displayHistogram(){ processor->displayHistogram();}
   
    void displayWait(){ processor->displayWait();}

    std::string getFileMetadata(){return dicom->displayMetaData();}

    std::string getPatientName();

    void createImage();

private:
    FileHandle *file;

    Processor* processor;

    DicomReader *dicom;
 
};


