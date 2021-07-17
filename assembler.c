#include "assembler.h"

/*
 * logic function for the first run over the current file
 */
void first_run(FILE *file)
{
    init_data();
    read_by_line(file,FIRST_ITER);
}