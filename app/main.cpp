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

    // Image processing in a separate thread
    MyThread myThread(imagePath);
    std::thread processingThread(&MyThread::worker, &myThread);
    processingThread.join();

    // Get processed image information from the ImageProcessor object

    return 0;
}
