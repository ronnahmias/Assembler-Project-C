#include "Instructions_functions.h"

char * inst_r[6] = { "add", "sub", "and", "or", "nor", "move","mvhi","mvlo" };
char * inst_j[4] = { "jmp", "la", "call", "stop" };
char * inst_i[15] = { "addi", "subi", "andi", "ori", "nori", "beq","bne","blt","bgt","lb","sb","lw","sw","lh","sh" };

extern int * Inst_Type;
extern int * Inst_Action;
extern int * IC;
extern char * help_argument_array;

/*
 * init instruction variables
 */
init_instruction_vars(){
    Inst_Type = (int*) calloc(sizeof (int),1);
    Inst_Action = (int*) calloc(sizeof (int),1);
    if(Inst_Type == NULL || Inst_Action == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    return TRUE;
}

/*
 * find instruction from 3 type and update type and action
 */
int find_instruction(char *data, int size){
    int i;
    *Inst_Type = NO_INSTRUCTION_FOUND;
    *Inst_Action = NO_INSTRUCTION_FOUND;

    /* run over R instructions */
    for (i = 0; i < INST_R_NUMBER; i++)
    {
        if (!strncmp(inst_r[i], data,size) && strlen(inst_r[i]) == size)
        {
            /* found instruction r type */
            *Inst_Type = R;
            *Inst_Action = i;
            return OK;
        }
    }

    for (i = 0; i < INST_J_NUMBER; i++)
    {
        if (!strncmp(inst_j[i], data,size) && strlen(inst_j[i]) == size)
        {
            /* found instruction j type */
            *Inst_Type = J;
            *Inst_Action = i;
            return OK;
        }
    }

    for (i = 0; i < INST_I_NUMBER; i++)
    {
        if (!strncmp(inst_i[i], data,size) && strlen(inst_i[i]) == size)
        {
            /* found instruction i type */
            *Inst_Type = I;
            *Inst_Action = i;
            return OK;
        }
    }

    return NO_INSTRUCTION_FOUND;
}

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

/*
 * init instruction counter
 */
int init_ic(){
    IC = (int *) calloc(sizeof(int),1);
    if(IC == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    *IC = 100; /* init ic to address 100*/
    return TRUE;
}

/*
 * init help arguments array before insert to nodes
 */
int init_help_array(int size){
    help_argument_array = (char *) calloc(sizeof(char),size);
    if(help_argument_array == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    return TRUE;
}