
#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include <stdio.h>
#include <ctype.h>
#include "constants.h"
#include "data_functions.h"
#include "shared_data.h"



void read_by_line(FILE *cur_file, int iteration);
void process_input(char *input_row, int iteration);
char * delete_spaces(char* input); /* delete space */
char * skip_word(char* input);
int is_dot(char ch);
void process_data(char * data, int iteration);
char * asciz_input_check(char * data);
int has_label(char * data);
char * skip_label(char* input); /* skip the label */
char * extract_asciz_string(char * data);


#endif //MAMAN14_HELPERS_H
