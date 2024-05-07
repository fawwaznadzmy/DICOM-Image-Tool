# CMake generated Testfile for 
# Source directory: D:/Project/Git/DICOM_V2/DICOM-Image-Tool/test
# Build directory: D:/Project/Git/DICOM_V2/DICOM-Image-Tool/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[dicom_gtest]=] "unit_test")
set_tests_properties([=[dicom_gtest]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Project/Git/DICOM_V2/DICOM-Image-Tool/test/CMakeLists.txt;43;add_test;D:/Project/Git/DICOM_V2/DICOM-Image-Tool/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
