#pragma once
#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

class FileHandle {
protected:
    std::string filePath;

public:
    FileHandle(const std::string& path) : filePath(path) {}

    virtual ~FileHandle() = default;

    // Method to get file extension
    virtual std::string getFileExtension() const;
    // Method to save file
    virtual bool saveFile(const std::string& content) const = 0;

    // Method to delete file
    virtual bool deleteFile() const = 0;

    // Method to get file size
    virtual long long getFileSize() const = 0;

    // Factory method to create FileHandle object based on OS
    static FileHandle* create(const std::string& path);

};

// Windows implementation
#ifdef _WIN32
class WindowsFileHandle : public FileHandle {
public:
    WindowsFileHandle(const std::string& path) : FileHandle(path) {}

    bool saveFile(const std::string& content) const override ;

    bool deleteFile() const override ;

    long long getFileSize() const override ;

};

#else
// Linux implementation
class LinuxFileHandle : public FileHandle {
public:
    LinuxFileHandle(const std::string& path) : FileHandle(path) {}

    bool saveFile(const std::string& content) const override ;

    bool deleteFile() const override ;

    long long getFileSize() const override;
};
#endif


