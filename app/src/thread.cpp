#include "thread.h"

void displayMetadata(MessageQueue& messageQueue) {
    while (true) {
        // Pop a message from the queue
        MetadataMessage message = messageQueue.pop();

        if (message.isValid) {
            std::string tempFileName = "dicom_metadata.txt";
            std::ofstream outputFile(tempFileName);
            if (outputFile.is_open()) {
                outputFile << "DICOM Metadata:" << std::endl << message.metadata;
                outputFile.close();
            }
            std::cout << "DICOM Metadata:" << std::endl;
            std::cout << message.metadata << std::endl;
        } else {
            std::cerr << "Error: cannot read DICOM file" << std::endl;
        }
    }
}

MyThread::MyThread (const std::string& path, std::unique_ptr<IFileHandle>& file, 
                   std::unique_ptr<IProcessor>& proc, std::unique_ptr<IDicomReader>& dcm) : m_path(path){
   image = std::make_unique<ProcessorAdapter>(path,file,proc,dcm);

}
 
void MyThread::worker(MessageQueue& mq){

    m_message.metadata= image->getFileMetadata();
    m_message.isValid = true;
    mq.push(m_message);
    
    image->createImage();
    image->displayImage("Original");
    image->autoCropAndRotateImage();
    image->displayImage("Auto Crop and Rotate");
    image->displayHistogram();
    image->displayWait();
}