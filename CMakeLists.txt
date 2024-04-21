cmake_minimum_required(VERSION 3.10.0)
project(DicomImageTool VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB_RECURSE SRC_FILES app/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/app/inc )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
