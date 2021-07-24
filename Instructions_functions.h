#ifndef MAMAN14_INSTRUCTIONS_FUNCTIONS_H
#define MAMAN14_INSTRUCTIONS_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"
#include "shared_data.h"

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

enum inst_type_enum{
    R = 0,
    J,
    I
};

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

enum instruction_j_enum
{
    JMP = 0,
    LA,
    CALL,
    STOP
};

enum instruction_i_enum
{
    ADDI = 0,
    SUBI,
    ANDI,
    ORI,
    NORI,
    BEQ,
    BNE,
    BLT,
    BGT,
    LB,
    SB,
    LW,
    SW,
    LH,
    SH
};

/*
 * init instruction variables
 */
init_instruction_vars();

/*
 * find instruction from 3 type and update type and action
 */
int find_instruction(char *data, int size);

/*
 * init instruction node for linked list
 */
instructionNode * init_instruction_node();

/*
 * init instruction counter
 */
int init_ic();

/*
 * init help arguments array before insert to nodes
 */
int init_help_array(int size);

#endif
