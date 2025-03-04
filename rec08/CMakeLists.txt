cmake_minimum_required(VERSION 3.29)
project(rec08)

set(CMAKE_CXX_STANDARD 20)

add_executable(rec08 rec08.cpp
                     student.cpp
                     registrar.cpp
                     course.cpp)
add_executable(rec08_single rec08_single.cpp)
