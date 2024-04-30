#pragma once
#include <iostream>
#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/dcmimgle/dcmimage.h"
using namespace std;
class DicomReader{
public:
    DicomReader(const std::string& path);
    
    std::ostringstream displayMetaData();

    string displayPatientName();

    bool isFileValid();

    void* image(int& width, int& height, int& depth);

    DicomImage* image(){return m_DCMImage;}

private:
    DcmFileFormat m_fileformat;
    DicomImage* m_DCMImage; 
    bool  m_isFileValid;
    string m_path;
    
};