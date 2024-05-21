#pragma once
#include <iostream>

class IDicomReader{
public:
    IDicomReader(const std::string& path): m_path(path){}
    
    virtual ~IDicomReader() = default;

    virtual bool isFileValid() const = 0;
    
    virtual std::string getMetaData() const = 0;

    virtual std::string getPatientName() const = 0;

    virtual long getImageWidth() const = 0;

    virtual long getImageHeight() const = 0;

    virtual long getImageDepth()const = 0;

    virtual void* getImageOutputData() const = 0;
  
protected:
    std::string m_path;
};