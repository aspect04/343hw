cmake_minimum_required(VERSION 3.31)
project(MidnightSnack)

set(CMAKE_CXX_STANDARD 20)

# Add compiler warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Main executable
add_executable(MidnightSnack main.cpp)

# Test executable
add_executable(MidnightSnackTests TestCode.cpp)
