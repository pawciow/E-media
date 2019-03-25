cmake_minimum_required(VERSION 3.13)
project(CMakeProject1)

set(CMAKE_CXX_STANDARD 14)

include_directories(CMakeProject1)

add_executable(CMakeProject1
        CMakeProject1/CMakeProject1.cpp
        CMakeProject1/CMakeProject1.h
        .gitattributes
        .gitignore
        CMakeLists.txt
        robot_opiekunczy.jpg)
