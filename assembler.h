#ifndef MAMAN14_ASSEMBLER_H
#define MAMAN14_ASSEMBLER_H

#include <stdio.h>
#include "parser.h"
#include "data_functions.h"
#include "shared_data.h"
#include "error_handler.h"
#include "helpers.h"
#include "export_handler.h"

/*
 * logic function for the first run over the current file
 */
int first_run(FILE *file);

/*
 * second run
 * do update of entry, and labels as args to complete the code
 */
int second_run();

/*
 * export file and free variables
 */
int export_free();

#endif
