#pragma once
#include <iostream>
#include "dicomInterface.h"

#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/dcmimgle/dcmimage.h"


class Dcmtk : public IDicomReader{
public:
    Dcmtk(const std::string& path);
    ~Dcmtk();
    
    std::string getMetaData()  const override;

    std::string getPatientName()  const override;

    bool isFileValid() const override;

    long getImageWidth() const override { 
        return m_DCMImage->getWidth();
    }

    long getImageHeight() const override { 
        return m_DCMImage->getHeight();
    }

    long getImageDepth() const override { 
        return m_DCMImage->getDepth();
    }

    void* getImageOutputData() const override{ 
        return (void*)m_DCMImage->getOutputData(8);
    }
    
private:
    std::unique_ptr<DcmFileFormat> m_fileformat;
    std::unique_ptr<DicomImage> m_DCMImage; 
    bool  m_isFileValid;
    std::string m_path;
};