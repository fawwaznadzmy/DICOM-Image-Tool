#pragma once

#include "processor.h";
#include "dicom.h";



class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path);

    ~ProcessorAdapter();
   
    void displayImage(const std::string& title);

    void autoCropAndRotateImage(){processor->autoCropAndRotateImage();}

    void displayHistogram(){ processor->displayHistogram();}
   
    void displayWait(){ processor->displayWait();}

    std::string getFileMetadata(){return dicom->displayMetaData();}

    std::string getPatientName();

    void createImage();

private:
    std::unique_ptr<FileHandle> file;

    std::unique_ptr<IProcessor> processor;

    DicomReader *dicom;
 
};


