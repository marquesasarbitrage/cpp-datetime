add_library(cpp-datetime 
    STATIC 
        src/datetime.cpp
        src/timedelta.cpp
        src/errors.cpp
        src/tenor.cpp
        src/utils.cpp)

target_include_directories(cpp-datetime PUBLIC include)