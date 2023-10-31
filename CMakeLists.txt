cmake_minimum_required(VERSION 3.23)
include_directories(analyser)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c)
add_executable(test test.cpp)

add_executable(analyzer analyzer.cpp)
