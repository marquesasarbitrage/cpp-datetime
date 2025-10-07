# tests DateTime and TimeDelta
add_executable(datetime-test1 ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.cpp)
target_link_libraries(datetime-test1 PUBLIC cpp-datetime)
