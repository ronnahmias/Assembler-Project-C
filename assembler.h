#ifndef MAMAN14_ASSEMBLER_H
#define MAMAN14_ASSEMBLER_H

#include <stdio.h>
#include "parser.h"
#include "data_functions.h"
#include "shared_data.h"
#include "error_handler.h"
#include "helpers.h"

/*
 * logic function for the first run over the current file
 */
int first_run(FILE *file);

#endif
