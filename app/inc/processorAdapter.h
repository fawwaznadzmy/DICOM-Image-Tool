#pragma once

#include "imageProcessor.h"
#include "dicomInterface.h"
#include "fileHandle.h"



class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path);

    ~ProcessorAdapter();
   
    void displayImage(const std::string& title);

    void autoCropAndRotateImage(){processor->autoCropAndRotateImage();}

    void displayHistogram(){ processor->displayHistogram();}
   
    void displayWait(){ processor->displayWait();}

    std::string getFileMetadata(){return dicom->getMetaData();}

    std::string getPatientName();

    void createImage();

private:
    std::unique_ptr<IFileHandle> file;

    std::unique_ptr<IProcessor> processor;

    std::unique_ptr<IDicomReader> dicom;
 
};


