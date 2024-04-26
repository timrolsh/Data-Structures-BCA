cmake_minimum_required(VERSION 3.26)
project(QuadModLab)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(QuadModLab
        QuadModLab.cpp
#        QuadModLab.hpp
#        QuadModLabTester.cpp
)
