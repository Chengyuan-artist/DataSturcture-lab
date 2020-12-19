cmake_minimum_required(VERSION 3.17)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(BinaryTree main.cpp tree.h tree.cpp)

set(CMAKE_EXE_LINKER_FLAGS -static)

