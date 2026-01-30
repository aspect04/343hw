cmake_minimum_required(VERSION 3.31)
project(ThePhantomThread)

set(CMAKE_CXX_STANDARD 20)

# Main executable for the assignment
add_executable(ThePhantomThread main.cpp)

# Test executable
add_executable(tests tests.cpp)
