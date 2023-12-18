cmake_minimum_required(VERSION 3.26)
project(ProbabilityLab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ProbabilityLab
        ProbabilityLab.cpp
        ProbabilityLab.hpp)
