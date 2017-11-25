cmake_minimum_required(VERSION 3.8)
project(valley)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        menu.cpp
        menu.hpp
        utilities.cpp
        utilities.hpp)

add_executable(valley ${SOURCE_FILES})