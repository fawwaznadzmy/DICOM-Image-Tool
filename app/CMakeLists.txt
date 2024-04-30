cmake_minimum_required(VERSION 3.29.0)
project(DicomImageTool VERSION 0.1.0 LANGUAGES C CXX)

#include(CTest)
#enable_testing()

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


#find_package(Python2 COMPONENTS Interpreter Development REQUIRED)
#include_directories("C:/Python27/Lib/site-packages/numpy/core/include")
#include_directories("C:/Python27/include")
# Specify the path to zlib
set(ZLIB_ROOT "D:/DCMTK/dcmtk-3.6.8-win64-support-MD-msvc-17.4/zlib-1.3")

# search for DCMTK library and header files
SET(DCMTK_DIR "C:/Program Files/DCMTK") 
find_package(DCMTK REQUIRED)

link_directories("C:/Program Files/DCMTK/lib")
link_directories("D:/DCMTK/dcmtk-3.6.8-win64-support-MD-msvc-17.4/zlib-1.3/lib")

include_directories(${ZLIB_ROOT}/include)
#find_package(ZLIB REQUIRED)

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#file(GLOB_RECURSE INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
include_directories(inc)

add_library(dicom_lib 
   src/fileHandle.cpp src/myImage.cpp src/thread.cpp src/processor.cpp src/processorAdapter.cpp src/dicom.cpp
   inc/fileHandle.h inc/myImage.h inc/thread.h inc/processor.h inc/processorAdapter.h inc/dicom.h
   )

add_executable(${PROJECT_NAME} main.cpp )

# Use the INCLUDE_DIRS variable populated by the DCMTK find module.
INCLUDE_DIRECTORIES(${DCMTK_INCLUDE_DIRS})



target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_link_libraries( ${PROJECT_NAME} dicom_lib)
#target_link_libraries( ${PROJECT_NAME} ${Python2_LIBRARIES})
#link_directories("C:/Python27/libs")
target_link_libraries( ${PROJECT_NAME} ${DCMTK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} wsock32 ws2_32 Netapi32 iphlpapi zlib_d)
variable_watch(${DCMTK_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
