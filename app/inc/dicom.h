#pragma once
#include <iostream>
#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/dcmimgle/dcmimage.h"
using namespace std;
class DicomReader{
public:
    DicomReader(void);
    
    void createDicomImage();

    void convertDcmToPixel(const std::string& path, int* row, int* cols, uint8_t* pixel );

};