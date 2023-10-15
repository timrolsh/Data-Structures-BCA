# Cmake file for LoopTailTester only
# Josephus Tests involve reading from a file, and do not work with Make.
# Run those with the following command instead:
# g++ FlojoLab.cpp JosephusTester.cpp; ./a.out
cmake_minimum_required(VERSION 3.26)
project(LoopTailTester)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LoopTailTester
        FlojoLab.cpp
        LoopTailTester.cpp)
