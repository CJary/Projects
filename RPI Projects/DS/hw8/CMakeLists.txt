cmake_minimum_required(VERSION 3.24)
project(hw8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw8
        BPlusTree.h
        hw8_test.cpp)
