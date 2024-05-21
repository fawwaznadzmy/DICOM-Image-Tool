
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)

set(ZLIB_ROOT "D:/DCMTK/dcmtk-3.6.8-win64-support-MD-msvc-17.4/zlib-1.3")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# search for DCMTK library and header files
SET(DCMTK_DIR "C:/Program Files/DCMTK") 
find_package(DCMTK REQUIRED)

link_directories("C:/Program Files/DCMTK/lib")
link_directories("D:/DCMTK/dcmtk-3.6.8-win64-support-MD-msvc-17.4/zlib-1.3/lib")

include_directories(${ZLIB_ROOT}/include)

include_directories(../app/inc)
include_directories(inc)
file(GLOB_RECURSE SRC_TEST_FILES src/*.cpp)
add_executable(unit_test ${SRC_TEST_FILES})

INCLUDE_DIRECTORIES(${DCMTK_INCLUDE_DIRS})

target_link_libraries(unit_test
 PRIVATE
  GTest::GTest
  dicom_lib 
  ${OpenCV_LIBS}
  ${DCMTK_LIBRARIES}
  wsock32 ws2_32 Netapi32 iphlpapi zlib_d)


add_test(dicom_gtest unit_test)