#include "Instructions_functions.h"

char * inst_r[6] = { "add", "sub", "and", "or", "nor", "move","mvhi","mvlo" };
char * inst_j[4] = { "jmp", "la", "call", "stop" };
char * inst_i[15] = { "addi", "subi", "andi", "ori", "nori", "beq","bne","blt","bgt","lb","sb","lw","sw","lh","sh" };

/*
 * init instruction node for linked list
 */
instructionNode * init_instruction_node()
{
    instructionNode * pt;
    pt = (instructionNode *)calloc(sizeof(instructionNode),1);
    if(pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    pt->address = 0; /* TODO address counter*/
    return pt;
}