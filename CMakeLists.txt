cmake_minimum_required(VERSION 3.15)
project(String_C C)

set(CMAKE_C_STANDARD 99)

add_library(String_C SHARED lib/src/library.c lib/src/library.h)