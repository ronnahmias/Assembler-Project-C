
#ifndef MAMAN14_PARSER_H
#define MAMAN14_PARSER_H

#include <stdio.h>
#include <ctype.h>
#include "constants.h"
#include "data_functions.h"
#include "shared_data.h"
#include "parser_data_image.h"
#include "symbol_functions.h"
#include "Instructions_functions.h"
#include "instructions_parser.h"

extern int * RowNumber;
extern char * FileName;

/* parser functions */

/*
 * function that reads from the current file line
 */
int read_by_line(FILE *cur_file);

/*
 * process the input and check different options of the input
 */
int process_input(char *input_row);

/*
 * delete spaces from input
 */
char * delete_spaces(char* input);

/*
 * extract label from input
 */
int extract_label(char *data,int label_size,char * dest_label);

/*
 * checks if line is comment row
 */
int check_comment_line(char * input_row);

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

/* instructions parser functions */
/*
 * count the long of the instruction
 */
int count_instruction_long(char *data);

#endif
