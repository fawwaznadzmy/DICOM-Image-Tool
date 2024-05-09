
#include "processorAdapter.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path) { 
    file = FileHandle::create(path);
    processor = IProcessor::create();
    dicom = new DicomReader(path);
      
}

std::string ProcessorAdapter::getPatientName(){
    return dicom->displayPatientName();
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
