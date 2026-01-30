cmake_minimum_required(VERSION 3.31)
project(TheHotDogFactory)

set(CMAKE_CXX_STANDARD 20)

# Main executable for the hot dog factory
add_executable(TheHotDogFactory main.cpp)

# Test executable
add_executable(tests Tests.cpp)
