cmake_minimum_required(VERSION 3.5)
project(maman14 C)

set(CMAKE_C_STANDARD 90)

add_executable(maman14 main.c assembler.c assembler.h helpers.c helpers.h constants.h data_functions.c data_functions.h)