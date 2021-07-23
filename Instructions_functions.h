#ifndef MAMAN14_INSTRUCTIONS_FUNCTIONS_H
#define MAMAN14_INSTRUCTIONS_FUNCTIONS_H

#include "stdio.h"
#include "stdlib.h"
#include "error_handler.h"

typedef struct instructionNode{
    int address;
    struct instructionNode *next;
    union InstCode{
        unsigned int bits32:32;
        struct{
            unsigned int unused:6;
            unsigned int funct:5;
            unsigned int rd:5;
            unsigned int rt:5;
            unsigned int rs:5;
            unsigned int opcode:6;
        }InstructionsTypeR;
    }InstCode;
}instructionNode;

enum instruction_r_enum
{
    ADD = 0,
    SUB,
    AND,
    OR,
    NOR,
    MOVE,
    MVHI,
    MVLO
};

/*
 * init instruction node for linked list
 */
instructionNode * init_instruction_node();

#endif
