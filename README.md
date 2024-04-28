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

- [x] Write unit test (TDD/BDD)

## Description

This Application developed with C++ and the setup was done using CMake. It is  `a console application` that can be compiled and run in `Windows and Linux`. Once run, the application will crop, auto rotate and display the given image file `(.jpeg, tiff or .png)` and the histogram.

### How to run

Example, for Windows application, type command line below to launch the application:

```
DicomImageTool.exe <path/of/image/>
```
### Results
![original!](pictures/postprocess/original.png)
![rotate!](pictures/postprocess/cropAndRotate.png)
![histogram!](pictures/postprocess/histogram.png)

## How to Setup, Compile and Run

Checkout the git repository and install the following dependencies in order to run it on Windows:

### Install CMAKE
- Download [cmake](https://cmake.org/download/) for Windows  
- During installation, in installation option select "Add CMake to the system PATH for all users"

### Install VS C++ Complier
- Install visual studio msvc 2017 [compiler](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSFeaturesPage&passive=false&cid=2030)

### Setting up Open CV
- Download open CV source files [here](https://opencv.org/releases/) 
- Extract the folder to specific location `(e.g C:/OpenCv)`


## Compile, build and run the test

After checking out the repository, use commands below to compile, build or run the unit test
```
cmake -S . -B build  
```

```
MSBuild.exe build/DicomImageTool.vcxproj 
```

```
ctest --test-dir build --output-on-failure -j12
```


