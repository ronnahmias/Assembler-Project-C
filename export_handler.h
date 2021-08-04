#ifndef MAMAN14_EXPORT_HANDLER_H
#define MAMAN14_EXPORT_HANDLER_H

#include "shared_data.h"
#include "Instructions_functions.h"
#include "data_functions.h"

extern char * FileName;
extern signed long * IC;
extern data_enum dataEnum;

/*
 * function that handler all export files
 */
int export_files();

#endif
