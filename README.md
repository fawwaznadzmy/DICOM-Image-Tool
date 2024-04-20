# DICOM Image Processing Tool


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

## MSBuild.exe

C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin
MSBuild.exe build/vs/DicomImageTool.vcxproj

,,,
cmake -G "MinGW Makefiles" -S . -B out/build
,,,

