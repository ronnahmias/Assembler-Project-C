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
        struct{
            unsigned int address:25;
            unsigned int reg:1;
            unsigned int opcode:6;
        }InstructionsTypeJ;
    }InstCode;
}instructionNode;

typedef enum{
    R = 0,
    J,
    I
}inst_type_enum;

typedef enum{
    ADD = 0,
    SUB,
    AND,
    OR,
    NOR,
    MOVE,
    MVHI,
    MVLO
} instruction_r_enum;

typedef enum{
    JMP = 0,
    LA,
    CALL,
    STOP
}instruction_j_enum;

typedef enum{
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
}instruction_i_enum;

/*
 * init instruction variables
 */
int init_instruction_vars();

/*
 * free instruction variables
 */
int free_instruction_vars();

/*
 * reset inst variables every row
 */
void reset_instruction_vars();

/*
 * find instruction from 3 type and update type and action
 */
int find_instruction(char *data, int size);

/*
 * insert data to instruction node of r type instruction
 */
int Insert_R_Args();

/*
 * insert data to instruction node of j type instruction
 */
int Insert_J_Args(unsigned int address,int reg);

/*
 * adds the new node to linked list at the end
 */
void add_inst_node(instructionNode *newNode);

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
