#include "assembler.h"
#include "Instructions_functions.h"

/*
 * logic function for the first run over the current file
 */
int first_run(FILE *file)
{
    int status;
    status = init_every_file();
    if(status == ERROR){
        return ERROR;
    }
    read_by_line(file);
    free_every_file();
    return OK;
}

void second_run(FILE *file)
{
    read_by_line(file);
}

