#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include "parser.h"

/*
 * init variables
 */
int init();

/*
 * checks that labe is start with char and not a number
 */
int label_start_char(char * data);

/*
 * checks range of register between 0-31
 */
int register_range(unsigned int num);

/*
 * counts white spaces from index
 */
int skip_white_spaces(char * data,int index);

/*
 *  update file name for the current file open
 */
void update_current_file_name(char * name);

/*
 * checks input file extension .as
 */
int check_file_extension();

#endif
