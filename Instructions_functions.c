#include "Instructions_functions.h"

char * inst_r[8] = { "add", "sub", "and", "or", "nor", "move","mvhi","mvlo" };
char * inst_j[4] = { "jmp", "la", "call", "stop" };
char * inst_i[15] = { "addi", "subi", "andi", "ori", "nori", "beq","bne","blt","bgt","lb","sb","lw","sw","lh","sh" };
int op_code_r[8] = { 0,0,0,0,0,1,1,1 };
int op_code_j[4] = { 30,31,32,63 };
int op_code_i[15] = { 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
int funct_r[8] = { 1,2,3,4,5,1,2,3 };

/* instruction variables */
instructionNode * InstructionNodes;

extern int * Inst_Type;
extern int * Inst_Action;
extern int * IC;
extern unsigned int * help_argument_array;

/*
 * init instruction variables
 */
int init_instruction_vars(){
    Inst_Type = (int*) calloc(sizeof (int),1);
    Inst_Action = (int*) calloc(sizeof (int),1);
    if(Inst_Type == NULL || Inst_Action == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
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
 * adds the new node to linked list at the end
 */
void add_inst_node(instructionNode *newNode){
    instructionNode * cur_node;
    if(InstructionNodes == NULL){ /* this is the first node in the int nodes */
        InstructionNodes = newNode;
    }else{
        cur_node = InstructionNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of inst nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = newNode;
    }
}

/*
 * insert data to instruction node of r type instruction
 */
int Insert_R_Args(){
    instructionNode * newNode;
    unsigned int rd,rs,rt;
    int i=0;
    newNode = init_instruction_node();
    if(newNode == NULL){
        return ERROR;
    }
    switch (*Inst_Action) {
        case ADD:
        case SUB:
        case AND:
        case OR:
        case NOR:
            rs = help_argument_array[i++];
            rt = help_argument_array[i++];
            rd = help_argument_array[i++];
            break;
        case MOVE:
        case MVHI:
        case MVLO:
            rd = help_argument_array[i++];
            rs = help_argument_array[i++];
            rt = UNUSED;
            break;
    }
    newNode->InstCode.InstructionsTypeR.unused = UNUSED;
    newNode->InstCode.InstructionsTypeR.funct = funct_r[*Inst_Action];
    newNode->InstCode.InstructionsTypeR.rd = rd;
    newNode->InstCode.InstructionsTypeR.rt = rt;
    newNode->InstCode.InstructionsTypeR.rs = rs;
    newNode->InstCode.InstructionsTypeR.opcode = op_code_r[*Inst_Action];
    add_inst_node(newNode);
    return OK;
}

/*
 * insert data to instruction node of j type instruction
 */
int Insert_J_Args(char * label_address,int reg){
    instructionNode * newNode;
    unsigned int address;
    int i=0;
    newNode = init_instruction_node();
    if(newNode == NULL){
        return ERROR;
    }
    switch(*Inst_Action){
        case JMP:
            address = help_argument_array[i++];
            break;
        case LA:
        case CALL:
            address = strtol(label_address,NULL,10); /* convert to num */
            break;
        case STOP:
            /* no arguments expected */
            break;
    }
    newNode->InstCode.InstructionsTypeJ.address = address;
    newNode->InstCode.InstructionsTypeJ.reg = reg;
    newNode->InstCode.InstructionsTypeJ.opcode = op_code_j[*Inst_Action];
    add_inst_node(newNode);
    return OK;
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
    pt->address = *IC;
    *IC = *IC + 4; /* increment ic counter in 4 */
    return pt;
}

/*
 * init instruction counter
 */
int init_ic(){
    IC = (int *) calloc(sizeof(int),1);
    if(IC == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL_SIGN;
    }
    *IC = 100; /* init ic to address 100*/
    return TRUE;
}

/*
 * init help arguments array before insert to nodes
 */
int init_help_array(int size){
    int i=0;
    help_argument_array = (unsigned int *) calloc(sizeof(unsigned int),size);
    if(help_argument_array == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    return TRUE;
}