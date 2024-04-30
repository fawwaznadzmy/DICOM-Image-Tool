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


    virtual std::string getFileExtension() const;

    virtual bool saveFile(const std::string& content) const = 0;


    virtual bool deleteFile() const = 0;

    virtual long long getFileSize() const = 0;

    virtual std::string getFilePath() const =0;

    static FileHandle* create(const std::string& path);

};


#ifdef _WIN32
class WindowsFileHandle : public FileHandle {
public:
    WindowsFileHandle(const std::string& path) : FileHandle(path) {}

    bool saveFile(const std::string& content) const override ;

    bool deleteFile() const override ;

    long long getFileSize() const override ;

    std::string getFilePath() const {return filePath;}

};

#else

class LinuxFileHandle : public FileHandle {
public:
    LinuxFileHandle(const std::string& path) : FileHandle(path) {}

    bool saveFile(const std::string& content) const override ;

    bool deleteFile() const override ;

    long long getFileSize() const override;
};
#endif


