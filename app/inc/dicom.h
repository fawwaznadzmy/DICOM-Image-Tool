#pragma once
#include <iostream>
#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/dcmimgle/dcmimage.h"

class DicomReader{
public:
    DicomReader(const std::string& path);
    ~DicomReader();
    
    std::string displayMetaData();

    std::string displayPatientName();

    bool isFileValid();

    void* getImageData(int& width, int& height, int& depth);

    long getImageWidth(){ return m_DCMImage->getWidth();}

    long getImageHeight(){ return m_DCMImage->getHeight();}

    long getImageDepth(){ return m_DCMImage->getDepth();}

    void* getImageOutputData(){ return (void*)m_DCMImage->getOutputData(8);}
  
private:
    DcmFileFormat m_fileformat;
    std::unique_ptr<DicomImage> m_DCMImage; 
    bool  m_isFileValid;
    std::string m_path;
};