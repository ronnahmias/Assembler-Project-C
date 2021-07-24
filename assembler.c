#include "assembler.h"
#include "Instructions_functions.h"

/*
 * logic function for the first run over the current file
 */
void first_run(FILE *file)
{
    /* TODO remove*/
    instructionNode *pt;
    pt = init_instruction_node();
    pt->InstCode.InstructionsTypeR.opcode = 1;
    pt->InstCode.InstructionsTypeR.funct = 80;

    init();
    init_errors_data(); /* init errors variables */
    init_data(); /* init data variables */
    read_by_line(file,FIRST_ITER);
}

void second_run(FILE *file)
{
    read_by_line(file,SECOND_ITER);
}

