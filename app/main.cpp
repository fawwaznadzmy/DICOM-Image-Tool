#include <iostream>
#include <thread>
#include "thread.h"


void printHelp() {
    std::cout << "Usage: image_processor [image_path]" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printHelp();
        return 1;
    }

    std::string arg = argv[1];
    if (arg == "-help" || arg == "--help") {
        printHelp();
        return 0;
    }

    std::string imagePath = argv[1];
    MessageQueue messageQueue;
    // Start the metadata display thread
    std::thread displayThread(displayMetadata, std::ref(messageQueue));

    // Processor Thread
    std::unique_ptr<IFileHandle> file = IFileHandle::create(imagePath);
    std::unique_ptr<IProcessor> imageProcessor = IProcessor::create();
    std::unique_ptr<IDicomReader> dcmReader = std::make_unique<Dcmtk>(imagePath);

    MyThread myThread(imagePath,file,imageProcessor,dcmReader);
    std::thread processingThread(&MyThread::worker, &myThread, std::ref(messageQueue));

    processingThread.join();
    displayThread.join();

    return 0;
}
