#include "instructions_parser.h"

extern int * Inst_Type;
extern int * Inst_Action;

extern enum inst_type_enum;
extern enum instruction_r_enum;
extern enum instruction_j_enum;
extern enum instruction_i_enum;

/*
 * extract from string numbers that near the dollar sign
 * according to number of argument expected
*/
int extract_numbers_dollars(char * data, int num_args){
    int i=0;
    char *help_arr;
    help_arr = init_help_array(num_args);
    /* TODO continue */
    while(data[i] != '\n' || data[i] != '\t'){
        if(data[i] == ' '){
            i++;
            continue;
        }
        i++;
    }
}

/*
 * process the data of the instruction row and check how many arguments
 * that match to instruction Action with the type
 */
int process_instruction(char * data,int iteration){
    switch(*Inst_Type){
        case R:
            switch(*Inst_Action){
                case ADD:
                case SUB:
                case AND:
                case OR:
                case NOR:
                    /* we expect 3 arguments with $ */
                    break;
                case MOVE:
                case MVHI:
                case MVLO:
                    /* we expect 2 arguments */
                    break;
            }
            break;
        case J:
            switch(*Inst_Action){
                case JMP:
                    /* 1 label or number as argument expect */
                    break;
                case LA:
                case CALL:
                    /* label as argument expect */
                    break;
                case STOP:
                    /* no arguments expected */
                    break;
            }
            break;
        case I:
            switch(*Inst_Action){
                case ADDI:
                case SUBI:
                case ANDI:
                case ORI:
                case NORI:
                case LB:
                case SB:
                case LW:
                case SW:
                case LH:
                case SH:
                    /* expect 3 arguments 1 in number in the center without $ */
                    break;
                case BEQ:
                case BNE:
                case BLT:
                case BGT:
                    /* expect 2 argument with $ and label at end */
                    break;
            }
            break;
    }
}

