cmake_minimum_required(VERSION 3.29.3)

project(test_datetime_utils)

set(CMAKE_CXX_STANDARD 17)
include_directories(../../include/cpp-datetime)
add_executable(
    test 
    test.cpp 
    ../../src/datetime.cpp
    ../../src/timedelta.cpp
    ../../src/errors.cpp
    ../../src/utils.cpp
    ../../src/tenor.cpp)