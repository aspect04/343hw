#!/bin/bash
date -u > valgrind.out
g++ -g -std=c++11 -Wall -Wextra main.cpp 2>&1 | tee -a valgrind.out
valgrind --leak-check=full ./a.out  2>&1 | tee -a valgrind.out