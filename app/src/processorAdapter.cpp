
#include "processorAdapter.h"
#include "dcmtk.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path) { 
    file = IFileHandle::create(path);
    processor = IProcessor::create();
    dicom = std::make_unique<Dcmtk>(path);
      
}

  ProcessorAdapter::~ProcessorAdapter(){

  }

std::string ProcessorAdapter::getPatientName(){
    return dicom->getPatientName();
}

void ProcessorAdapter::displayImage(const std::string& title){ 
    processor->displayImage(title);
}



void ProcessorAdapter::createImage(){
    if(file->getFileExtension() == "dcm"){
        processor->createImagefromDicom(dicom);
    }else{
        processor->createImageFromPath(file->getFilePath());
    }
}
