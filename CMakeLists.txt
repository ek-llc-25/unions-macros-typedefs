cmake_minimum_required(VERSION 4.0)
project(unionsjov C)

set(CMAKE_C_STANDARD 23)
include_directories(.)
add_executable(unionsjov main.c inventory.c inventory.h)
