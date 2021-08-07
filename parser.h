
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
 * extract label from input
 */
int extract_label(char *data,int label_size,char * dest_label);

#endif
