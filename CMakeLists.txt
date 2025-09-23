cmake_minimum_required(VERSION 3.15)
project(cpp-datetime VERSION 1.0 LANGUAGES CXX)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cpp-datetime 
    STATIC 
        src/datetime.cpp
        src/timedelta.cpp
        src/errors.cpp
        src/tenor.cpp
        src/utils.cpp)

target_include_directories(cpp-datetime PUBLIC include)