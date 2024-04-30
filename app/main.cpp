#include <iostream>
#include <thread>
#include "thread.h"

#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/dcmimgle/dcmimage.h"

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
        // Create a message queue
    MessageQueue messageQueue;


    // Start the metadata display thread
    std::thread displayThread(displayMetadata, std::ref(messageQueue));

    MyThread myThread(imagePath);
    std::thread processingThread(&MyThread::worker, &myThread, std::ref(messageQueue));
    processingThread.join();
    displayThread.join();

    return 0;
}
