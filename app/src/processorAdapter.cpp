
#include "processorAdapter.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path){
      
       file = FileHandle::create(path);
       processor = Processor::create();
       dicom = new DicomReader();
      
       string ext= file->getFileExtension();

       if( ext == "dcm"){

            int rows, cols;
            uint8_t* pixel;

            dicom ->convertDcmToPixel(path,&rows,&cols,pixel);
            processor->createImageFromPixel(rows,cols,*pixel);
            cout << "convert dcm to a format that can be process by processor";
       } 
       else if( (ext == "jpeg") || (ext == "png") || (ext == "tif") ){
            processor->createImageFromPath(path); 
       }
       else
            cout << "Unsupported file";
}

