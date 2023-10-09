cmake_minimum_required(VERSION 3.26)
project(FlojoLab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FlojoLab
        FlojoLab.cpp
        FlojoLab.hpp
        FlojoLabTester.cpp
        JosephusTestCases.txt)
