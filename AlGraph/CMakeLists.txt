cmake_minimum_required(VERSION 3.17)
project(AdjList)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdjList main.cpp algraph.h algraph.cpp queue.h hashtable.h)

set(CMAKE_EXE_LINKER_FLAGS -static)