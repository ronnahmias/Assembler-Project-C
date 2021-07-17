#ifndef MAMAN14_PARSER_DATA_IMAGE_H
#define MAMAN14_PARSER_DATA_IMAGE_H

#include "data_functions.h"

/*
 * main function to parse if the input row is data image
 */
void process_data(char * data, int iteration);

/*
 * check if asciz row is in the correct syntax
 */
int asciz_input_check(char * data);

/*
 * copy the string from data input to array of chars in AscizRow struct
 */
char * extract_asciz_string(char * data);

#endif //MAMAN14_PARSER_DATA_IMAGE_H
