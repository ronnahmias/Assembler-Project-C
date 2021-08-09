#ifndef MAMAN14_INSTRUCTIONS_FUNCTIONS_H
#define MAMAN14_INSTRUCTIONS_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handler.h"
#include "shared_data.h"
#include "symbol_functions.h"

typedef struct instructionNode{
    int address;
    struct instructionNode *next;
    int need_completion; /* for the second run */
    char * label; /* save the label for instruction for second run*/
    int instruction_type;
    int instruction_action;
    signed long code;
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
int Insert_J_Args(signed long address,unsigned int reg,int need_completion, char * label);

/*
 * insert data to instruction node of i type instruction
 */
int Insert_I_Args(signed int immed,int need_completion, char *label);

/*
 * init instruction counter
 */
int init_ic();

/*
 * return current ic
 */
signed long get_ic();

/*
 * free instruction counter
 */
void free_ic();

/*
 * init help arguments array before insert to nodes
 */
int init_help_array(int size);

/*
 * update the code in instructions with label as arguments
 */
int update_instructions_with_label();

/*
 * get the code of next node from head in linked list
 * and also free the node
 */
instructionNode * get_next_node_code();

/*
 * checks if there is instruction nodes list
 */
int code_exists();

/*
 * free instructions linked list
 */
void free_inst_nodes();


#endif
