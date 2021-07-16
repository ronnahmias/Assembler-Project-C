
#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include <stdio.h>
#include <ctype.h>
#include "constants.h"
#include "data_functions.h"
#include "shared_data.h"


/* parser functions */
void read_by_line(FILE *cur_file, int iteration);
void process_input(char *input_row, int iteration);
char * delete_spaces(char* input); /* delete space */
char * skip_word(char* input);
int is_dot(char ch);
void process_data(char * data, int iteration);
int has_label(char * data);

/* parser asciz functions */
int asciz_input_check(char * data);
char * skip_label(char* input); /* skip the label */
char * extract_asciz_string(char * data);

/* parser (db,dh,dw) function*/
void convert_data_to_array(char * data);


#endif //MAMAN14_HELPERS_H
