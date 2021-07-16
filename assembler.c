#include "assembler.h"


void first_run(FILE *file)
{
    init_data();
    read_by_line(file,FIRST_ITER);
}