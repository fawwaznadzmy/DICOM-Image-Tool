
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
        m_processor->createImagefromDicom(m_dicom);
    }else{
        m_processor->createImageFromPath(m_file->getFilePath());
    }
}
