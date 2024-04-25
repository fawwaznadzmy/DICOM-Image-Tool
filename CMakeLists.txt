cmake_minimum_required(VERSION 3.16.0)
project(DicomProject LANGUAGES CXX)

include(CTest)
enable_testing()

add_subdirectory(app)
add_subdirectory(test)