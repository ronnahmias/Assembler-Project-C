#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include "parser.h"

/*
 * init variables for the whole file
 */
int init_every_file();

/*
 * free variables every file end
 */
void free_every_file();

/*
 * init variables that we need every row
 */
void init_every_row();

/*
 * checks range of register between 0-31
 */
int register_range(unsigned int num);

/*
 * checks range of immed number
 */
int immed_range(signed int num);

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
