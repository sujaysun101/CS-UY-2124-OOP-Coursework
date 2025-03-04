cmake_minimum_required(VERSION 3.29)
project(hw07)

set(CMAKE_CXX_STANDARD 20)
#[===[
add_executable(hw07 hw07.cpp
        Noble.cpp
        Warrior.cpp
        Warrior.h
        Noble.h)
]===]
add_executable(hw07 hw07_single.cpp)
