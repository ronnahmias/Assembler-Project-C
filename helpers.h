
#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include <stdio.h>
#include <ctype.h>
#include "constants.h"
#include "data_functions.h"
void read_by_line(FILE *cur_file, int iteration_num);
void process_input(char input_row[]);
char * delete_spaces(char* input); /* delete space */
char * split_word(char* input);
int is_dot(char ch);


#endif //MAMAN14_HELPERS_H
