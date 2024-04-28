
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(../app/inc)
file(GLOB_RECURSE SRC_TEST_FILES src/*.cpp)
add_executable(unit_test ${SRC_TEST_FILES})

target_link_libraries(unit_test
 PRIVATE
  GTest::GTest
  dicom_lib 
  ${OpenCV_LIBS})

add_test(dicom_gtest unit_test)