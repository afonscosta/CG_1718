cmake_minimum_required(VERSION 3.9)
project(generator)

set(CMAKE_CXX_STANDARD 11)

add_executable(generator main.cpp point.cpp point.h generator.cpp generator.h)