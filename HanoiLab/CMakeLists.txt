cmake_minimum_required(VERSION 3.26)
project(HanoiLab)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(HanoiLab
        HanoiLab.cpp
        HanoiLabTester.cpp)
