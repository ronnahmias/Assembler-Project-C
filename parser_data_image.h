#ifndef MAMAN14_PARSER_DATA_IMAGE_H
#define MAMAN14_PARSER_DATA_IMAGE_H

#include "data_functions.h"
#include "instructions_parser.h"

/*
 * main function to parse if the input row is data image
 */
int process_data(char * data);

/*
 * check if asciz row is in the correct syntax
 */
int asciz_input_check(char * data);

/*
 * copy the string from data input to array of chars in AscizRow struct
 */
int extract_asciz_string(char * data);

#endif
