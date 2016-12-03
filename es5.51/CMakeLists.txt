cmake_minimum_required(VERSION 2.6)
project(es551 CXX)

option(test "Build all tests." OFF) # Makes boolean 'test' available.

file(GLOB all_SRC
    "src/*.h"
    "src/*.cpp"
)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_compile_options(-std=c++11)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(main ${all_SRC} main.cpp)
target_link_libraries(main ${GTEST_LIBRARIES} boost_regex pthread)

if (test)
  enable_testing()
  add_executable(runUnitTests tests/GotoTest.cpp ${all_SRC})
  target_link_libraries(runUnitTests ${GTEST_LIBRARIES} boost_regex pthread)
  target_link_libraries(runUnitTests gtest gtest_main)
endif()
