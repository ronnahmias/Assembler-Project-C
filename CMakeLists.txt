cmake_minimum_required(VERSION 3.5)
project(maman14 C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS -pedantic)

add_executable(maman14 main.c assembler.c assembler.h parser.c parser.h constants.h data_functions.c data_functions.h shared_data.c shared_data.h parser_data_image.c parser_data_image.h error_handler.c error_handler.h helpers.c helpers.h symbol_functions.c symbol_functions.h Instructions_functions.c Instructions_functions.h instructions_parser.c instructions_parser.h export_handler.c export_handler.h)