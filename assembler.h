#ifndef MAMAN14_ASSEMBLER_H
#define MAMAN14_ASSEMBLER_H

#include "export_handler.h"
#include "constants.h"
#include "helpers.h"

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
