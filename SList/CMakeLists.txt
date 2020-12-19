cmake_minimum_required(VERSION 3.16)
project(LinearList_Sequence_)

set(CMAKE_CXX_STANDARD 11)

add_executable(LinearList_Sequence_ main.cpp sqlist.h)
set(CMAKE_EXE_LINKER_FLAGS -static)