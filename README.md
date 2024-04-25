# DICOM Image Processing Tool

Create an application (command line or GUI based) that can be used to display DICOM image as well as perform image processing technique/algorithm to enhance the default image

Requirements:
- [X] Use C++ as main programming language
- [x] Setup project using CMake
- [x] Use any UI framework and/or image processing library where applicable
- [x] Application runs on Windows and/or Linux
- [x] Project code is stored in Git repository (github or Gitlab)
- [x] Provide documentation for anyone to setup, compile and run the application on other machine

- [x] Read and display dental x-ray image file (.jpeg, tiff or .png) from local storage
- [x] Display image histogram information of the dental x-ray image
- [x] Auto rotate the image when displaying whereby the indicator on the image should be on the top left corner

- [ ] Read and display dental x-ray image file using DICOM format (.dcm)
- [ ] Read and display DICOM metadata of the DICOM file from local storage
- [ ] Perform some basic image processing technique to enhance the details of the existing DICOM image

- [ ] Write unit test (TDD/BDD)

## How to Setup, Compile and Run
### Installing CMAKE

- download cmake here for Windows  https://cmake.org/download/
- for installation option select "Add CMake to the system PATH for all users"

- Installing MinGW to build C++ Code https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites
- Installing make with command 'winget install ezwinports.make' or can install ttps://chocolatey.org/install then type choco install make

## Setting up project in VS code
- CMake Tool Extension (https://code.visualstudio.com/docs/cpp/cmake-linux)
- C++ Extension
- Makefile Tool Extension
- Open command [SHIFT] + [CTRL] + [P] 

### Setting up wxWidget

https://docs.wxwidgets.org/latest/overview_cmake.html

### Setting up Open CV
- Download open CV here and extract it. Copy the folder to C:\ drive 
- Add into environment variable path
    1. C:\opencv\build\x64\vc16\bin
    2. C:\opencv\build\x64\vc16\lib

### MSBuild.exe

C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin
MSBuild.exe build/vs/DicomImageTool.vcxproj

### DICOM DCMTK Library

- Download here https://dicom.offis.de/en/dcmtk/dcmtk-tools/
https://dicom.offis.de/dcmtk.php.en
https://dicom.offis.de/en/dcmtk/dcmtk-software-development/

https://support.dcmtk.org/redmine/projects/dcmtk/wiki/howto_cmakeconfiguration
- C:\dcmtk-3.6.8-win64-dynamic\bin


,,,
cmake -G "MinGW Makefiles" -S . -B out/build
,,,

