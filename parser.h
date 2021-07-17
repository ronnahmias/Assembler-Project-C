
#ifndef MAMAN14_PARSER_H
#define MAMAN14_PARSER_H

#include <stdio.h>
#include <ctype.h>
#include "constants.h"
#include "data_functions.h"
#include "shared_data.h"
#include "parser_data_image.h"

extern int * RowNumber;
extern char * FileName;

/* parser functions */

/*
 * function that reads from the current file line
 */
void read_by_line(FILE *cur_file, int iteration);

/*
 * process the input and check different options of the input
 */
void process_input(char *input_row, int iteration);

/*
 * delete spaces from input
 */
char * delete_spaces(char* input);

/*
 * skip the word from input row
 */
char * skip_word(char* input);

/*
 * checks if the char is dot or not
 */
int is_dot(char ch);

/*
 * checks if the input has label
 */
int has_label(char * data);

/*
 * skip the label -> cut the label from the input
 */
char * skip_label(char* input);

#endif //MAMAN14_PARSER_H
