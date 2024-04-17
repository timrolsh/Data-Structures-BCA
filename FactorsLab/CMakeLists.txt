cmake_minimum_required(VERSION 3.26)
project(FactorsLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64")

include_directories(.)

add_executable(FactorsLab
        FactorsLab.cpp
        FactorsLabTester.cpp
        FactorsLab.hpp)
