
#include "processorAdapter.h"

ProcessorAdapter::ProcessorAdapter(const std::string& path){
       file = FileHandle::create(path);
       processor = Processor::create();
       string ext= file->getFileExtension();

       if( ext == "dcm"){
            cout << "convert dcm to a format that can be process by processor";
       } 
       else if( (ext == "jpeg") || (ext == "png") || (ext == "tif") ){
            processor->createImageFromPath(path); 
       }
       else
            cout << "Unsupported file";
}

