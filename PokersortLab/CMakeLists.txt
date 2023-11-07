cmake_minimum_required(VERSION 3.26)
project(PokersortLab)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(PokersortLab
        PokersortLab.cpp
        PokersortLabTester.cpp
        )

# allow the make executable to open the files in the TestCases folder
file(COPY ${CMAKE_SOURCE_DIR}/TestCases DESTINATION ${CMAKE_BINARY_DIR})

