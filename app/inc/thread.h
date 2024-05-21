#pragma once


#include <fstream>
#include <cstdlib>

#include "processorAdapter.h"
#include "dcmtk.h"
#include "imageProcessor.h"
#include "messageQueue.h"


void displayMetadata(MessageQueue& messageQueue);

class MyThread{
public:
    MyThread(const std::string& path, std::unique_ptr<IFileHandle> &file, std::unique_ptr<IProcessor> &proc, std::unique_ptr<IDicomReader> &dcm);
    void worker(MessageQueue& messageQueue);
private:
    std::unique_ptr<ProcessorAdapter> image;
    std::string m_path;
    MetadataMessage m_message;
};




