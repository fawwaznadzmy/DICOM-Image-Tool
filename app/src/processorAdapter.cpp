
#include "processorAdapter.h"
#include "dcmtk.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path, std::unique_ptr<IFileHandle> &file, 
                     std::unique_ptr<IProcessor> &proc, std::unique_ptr<IDicomReader> &dcm):
                     m_file(std::move(file)), m_processor(std::move(proc)), m_dicom(std::move(dcm)) { 
      
}

  ProcessorAdapter::~ProcessorAdapter(){

  }

std::string ProcessorAdapter::getPatientName(){
    return m_dicom->getPatientName();
}

void ProcessorAdapter::displayImage(const std::string& title){ 
    m_processor->displayImage(title);
}


void ProcessorAdapter::createImage(){
    if(m_file->getFileExtension() == "dcm"){
       if(m_dicom->isFileValid()){
        m_processor->createImageFromRaw(m_dicom->getImageWidth(),m_dicom->getImageHeight()
                                       ,m_dicom->getImageDepth(),(long*)m_dicom->getImageOutputData(),50);
       }
     // m_processor->createImagefromDicom(m_dicom.get());
    }else{
        m_processor->createImageFromPath(m_file->getFilePath());
    }
}
