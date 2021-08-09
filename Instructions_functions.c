#include "Instructions_functions.h"

char * inst_r[8] = { "add", "sub", "and", "or", "nor", "move","mvhi","mvlo" };
char * inst_j[4] = { "jmp", "la", "call", "stop" };
char * inst_i[15] = { "addi", "subi", "andi", "ori", "nori", "bne","beq","blt","bgt","lb","sb","lw","sw","lh","sh" };
int op_code_r[8] = { 0,0,0,0,0,1,1,1 };
int op_code_j[4] = { 30,31,32,63 };
int op_code_i[15] = { 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };
int funct_r[8] = { 1,2,3,4,5,1,2,3 };

/* instruction variables */
instructionNode * InstructionNodes;
extern int * Inst_Type;
extern int * Inst_Action;
extern signed long * IC;
extern unsigned long * help_argument_array;

/* instruction private functions */

/*
 * init instruction node for linked list
 */
instructionNode * init_instruction_node();



/* end - instruction private functions */


/*
 * init instruction variables
 */
int init_instruction_vars(){
    Inst_Type = (int*) calloc(1,sizeof(int));
    Inst_Action = (int*) calloc(1,sizeof(int));
    if(Inst_Type == NULL || Inst_Action == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    return TRUE;
}

/*
 * free instruction variables
 */
int free_instruction_vars(){
    free(Inst_Type);
    free(Inst_Action);
}

/*
 * reset inst variables every row
 */
void reset_instruction_vars(){
    memset(Inst_Type,0,sizeof(Inst_Type));
    memset(Inst_Action,0,sizeof(Inst_Action));
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
void add_inst_node(instructionNode **newNode){
    instructionNode * cur_node;
    if(InstructionNodes == NULL){ /* this is the first node in the int nodes */
        InstructionNodes = *newNode;
    }else{
        cur_node = InstructionNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of inst nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = *newNode;
    }
}

/*
 * insert data to instruction node of r type instruction
 */
int Insert_R_Args(){
    instructionNode * newNode;
    unsigned char rd,rs,rt;
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
            rs = help_argument_array[i++];
            rd = help_argument_array[i++];
            rt = UNUSED;
            break;
    }
    newNode->instruction_action = *Inst_Action;
    newNode->instruction_type = *Inst_Type;
    newNode->code = (op_code_r[*Inst_Action] << OPCODE) |
                    (rs << RS) |
                    (rt << RT) |
                    (rd << RD_R) |
                    (funct_r[*Inst_Action] << FUNCT_R);
    add_inst_node(&newNode);
    free(help_argument_array);
    return OK;
}

/*
 * insert data to instruction node of j type instruction
 */
int Insert_J_Args(signed long address,unsigned int reg,int need_completion,char *label){
    instructionNode * newNode;
    int i=0;
    newNode = init_instruction_node();
    if(newNode == NULL){
        return ERROR;
    }
    switch(*Inst_Action){
        case JMP:
            if(reg == TRUE){ /* takes the register number to address */
                address = help_argument_array[i++];
            }
            free(help_argument_array);
            break;
        case LA:
        case CALL:
            break;
        case STOP:
            break;
    }
    if(*label != NULL_SIGN){ /* save label for second run process */
        newNode->label = (char *) calloc(LABEL_MAX_SIZE,sizeof(char));
        if(newNode->label != NULL){
            strncpy(newNode->label,label, sizeof(newNode->label)-1);
        }else{
            program_error(ERROR_ALLOCATING_MEMORY);
            return ERROR;
        }
    }
    newNode->need_completion = need_completion; /* sign for second run */
    newNode->instruction_action = *Inst_Action;
    newNode->instruction_type = *Inst_Type;
    newNode->code = (op_code_j[*Inst_Action] << OPCODE) |
                    (((reg & 0x1) << 25)) |
                    (address & 0xFFFFFF);
    add_inst_node(&newNode);
    return OK;
}

/*
 * insert data to instruction node of i type instruction
 */
int Insert_I_Args(signed int immed, int need_completion, char *label){
    instructionNode * newNode;
    int i=0;
    unsigned char rs,rt;
    newNode = init_instruction_node();
    if(newNode == NULL){
        return ERROR;
    }
    rs = help_argument_array[i++];
    rt = help_argument_array[i];
    newNode->need_completion = need_completion; /* sign for second run */
    if(*label != NULL_SIGN){ /* save label for second run process */
        newNode->label = (char *) calloc(LABEL_MAX_SIZE,sizeof(char));
        if(newNode->label != NULL){
            strncpy(newNode->label,label, sizeof(newNode->label)-1);
        }else{
            program_error(ERROR_ALLOCATING_MEMORY);
            return ERROR;
        }
    }
    newNode->instruction_action = *Inst_Action;
    newNode->instruction_type = *Inst_Type;
    newNode->code = (op_code_i[*Inst_Action] << OPCODE) |
                    (rs << RS) |
                    (rt << RT) |
                    ((immed & 0xFFFF));
    add_inst_node(&newNode);
    free(help_argument_array);
    return OK;
}

/*
 * init instruction node for linked list
 */
instructionNode * init_instruction_node()
{
    instructionNode * pt;
    pt = (instructionNode *)calloc(1,sizeof(instructionNode));
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
    IC = (signed long *) calloc(1,sizeof(signed long));
    if(IC == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    *IC = ADDRESS_INIT; /* init ic to address 100*/
    return TRUE;
}

/*
 * return current ic
 */
signed long get_ic(){
    return *IC;
}



/*
 * free instruction counter
 */
void free_ic(){
    free(IC);
}

/*
 * init help arguments array before insert to nodes
 */
int init_help_array(int size){
    int i=0;
    help_argument_array = (unsigned long *) calloc(size,sizeof(unsigned long));
    if(help_argument_array == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    return TRUE;
}

/*
 * update the code in instructions with label as arguments
 */
int update_instructions_with_label(){
    instructionNode *cur_inst;
    signed long address;
    int external;
    cur_inst = InstructionNodes;
    while(cur_inst){
        external = 0;
        /* work only on instructions that need second code changes */
        if(cur_inst->need_completion){
            address = find_label(cur_inst->label,&external); /* find the label in symbol list */
            switch (cur_inst->instruction_type) {
                case J:
                    /* update the address to label address. if not found add zero */
                     if(address == NOT_FOUND){ /* label not found */
                         program_error(ERROR_ARGUMENTS_ERROR);
                         return ERROR;
                     }else{
                         cur_inst->code |= (address & 0xFFFFFF);
                         /* add external node for future use */
                         if(external){
                             add_extern_node(cur_inst->label,cur_inst->address);
                         }
                     }
                    break;
                case I:
                    if(address == NOT_FOUND){ /* label not found */
                        program_error(ERROR_ARGUMENTS_ERROR);
                        return ERROR;
                    }else{
                        /* update address to range from label address to instruction address */
                        address -= cur_inst->address;
                        cur_inst->code |= (address & 0xFFFF);
                    }
                    break;
            }
        }
        cur_inst = cur_inst->next;
    }
}

/*
 * get the node of next node from head in linked list
 */
instructionNode * get_next_node_code(){
    instructionNode * node;
    if(InstructionNodes == NULL){
        return NULL;
    }
    node = InstructionNodes;
    InstructionNodes = InstructionNodes->next;
    return node;
}

/*
 * checks if there is instruction nodes list
 */
int code_exists(){
    if(InstructionNodes == NULL){
        return FALSE;
    }
    return TRUE;
}
