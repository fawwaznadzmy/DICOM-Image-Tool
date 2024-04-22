#include "fileHandle.h"


std::string FileHandle::getFileExtension() const {
    size_t dotIndex = filePath.find_last_of(".");
    if (dotIndex != std::string::npos) {
        return filePath.substr(dotIndex + 1);
    }
    return "";
}

// Factory method implementation
FileHandle* FileHandle::create(const std::string& path) {
#ifdef _WIN32
    return new WindowsFileHandle(path);
#else
    return new LinuxFileHandle(path);
#endif
}

#ifdef _WIN32
bool WindowsFileHandle::saveFile(const std::string& content) const{
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return false;
    }
    file << content;
    file.close();
    return true;
}

bool WindowsFileHandle::deleteFile() const{
    if (DeleteFileA(filePath.c_str())) {
        std::cout << "File deleted successfully." << std::endl;
        return true;
    }
    else {
        std::cerr << "Error: Failed to delete file." << std::endl;
        return false;
    }
}

long long WindowsFileHandle::getFileSize()const {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (GetFileAttributesExA(filePath.c_str(), GetFileExInfoStandard, &fileInfo)) {
        LARGE_INTEGER fileSize;
        fileSize.LowPart = fileInfo.nFileSizeLow;
        fileSize.HighPart = fileInfo.nFileSizeHigh;
        return fileSize.QuadPart;
    }
    else {
        std::cerr << "Error: Failed to get file size." << std::endl;
        return -1;
    }
}

#else
bool LinuxFileHandle::saveFile(const std::string& content) const{
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return false;
    }
    file << content;
    file.close();
    return true;
}

bool LinuxFileHandle::deleteFile() const{
    if (remove(filePath.c_str()) == 0) {
        std::cout << "File deleted successfully." << std::endl;
        return true;
    }
    else {
        std::cerr << "Error: Failed to delete file." << std::endl;
         return false;
    }
}

long long LinuxFileHandle::getFileSize()const{
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) == 0) {
         return fileStat.st_size;
    }
    else {
        std::cerr << "Error: Failed to get file size." << std::endl;
        return -1;
    }
}
#endif