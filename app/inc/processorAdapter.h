#pragma once

#include "imageProcessor.h"
#include "dicomInterface.h"
#include "fileHandle.h"

class ProcessorAdapter {
public:
    ProcessorAdapter(const std::string& path, std::unique_ptr<IFileHandle> &file, std::unique_ptr<IProcessor> &proc, std::unique_ptr<IDicomReader> &dcm);

    ~ProcessorAdapter();
   
    void displayImage(const std::string& title);

    void autoCropAndRotateImage(){m_processor->autoCropAndRotateImage();}

    void displayHistogram(){ m_processor->displayHistogram();}
   
    void displayWait(){ m_processor->displayWait();}

    std::string getFileMetadata(){return m_dicom->getMetaData();}

    std::string getPatientName();

    void createImage();

private:
    std::unique_ptr<IFileHandle> m_file;

    std::unique_ptr<IProcessor> m_processor;

    std::unique_ptr<IDicomReader> m_dicom;
 
};


