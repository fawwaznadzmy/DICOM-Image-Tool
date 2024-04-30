
#include "processorAdapter.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path) { 
    file = FileHandle::create(path);
    processor = Processor::create();
    dicom = new DicomReader(path);
      
}

string ProcessorAdapter::getPatientName(){
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
