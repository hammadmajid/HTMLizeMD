cmake_minimum_required(VERSION 3.27)
project(HTMLizeMD)

set(CMAKE_CXX_STANDARD 23)

add_executable(HTMLizeMD src/main.cpp
        src/clap.h)
