#ifndef MAMAN14_HELPERS_H
#define MAMAN14_HELPERS_H

#include "parser.h"

/*
 * init variables
 */
int init();

/*
 *  update file name for the current file open
 */
void update_current_file_name(char * name);

/*
 * checks input file extension .as
 */
int check_file_extension();

#endif
