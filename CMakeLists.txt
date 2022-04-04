cmake_minimum_required(VERSION 3.10)
project(send C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS -pthread)

add_executable(send main.c h264.h)
