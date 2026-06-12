cmake_minimum_required(VERSION 4.0)
project(lab11)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab11 main.cpp
        lab11.cpp
        lab11.h
        Node.cpp
        Node.h
        CircleList.cpp
        CircleList.h
        DoublList.cpp
        DoublList.h
        cirbar.cpp
        cirbar.h)
