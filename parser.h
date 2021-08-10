
#ifndef MAMAN14_PARSER_H
#define MAMAN14_PARSER_H

#include "data_functions.h"
#include "helpers.h"
#include "parser_data_image.h"
#include <ctype.h>


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
