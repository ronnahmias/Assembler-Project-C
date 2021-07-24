#include "instructions_parser.h"

extern int * Inst_Type;
extern int * Inst_Action;
extern char * help_argument_array;
extern int *RowNumber;

extern inst_type_enum instruction_type;
extern instruction_r_enum instruction_r;
extern instruction_j_enum instruction_j;
extern instruction_i_enum instruction_i;

/*
 * extract from string numbers that near the dollar sign
 * according to number of argument expected
*/
int extract_numbers_dollars(char * data, int num_args){
    int i=0,dollar_flag =0, help_index=0, num_flag =0;
    if(init_help_array(num_args) == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    while(data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\r'){
        if(data[i] == ' '){
            i++;
            continue;
        }
        if(!dollar_flag && data[i] == '$'){
            /* next index need to be number */
            dollar_flag =1;
            i++;
            continue;
        }
        if(num_flag && data[i] == ','){
            num_flag = 0;
            i++;
            continue;
        }
        if(dollar_flag && isdigit(data[i])){
            /* need to be number -> save to help array */
            dollar_flag =0;
            num_flag = 1;
            help_argument_array[help_index++] = data[i++];
            continue;
        }
        /* there is chars that doesn't need to be or in wrong order */
        add_error(ERROR_ARGUMENTS_ERROR,*RowNumber);
        return FALSE;
    }
    if(help_argument_array[FIRST_INDEX] == NULL_SIGN){
        /* no argument -> error */
        add_error(ERROR_ARGUMENTS_ERROR,*RowNumber);
        return ERROR;
    }
    /* we have run over all the arguments */
    return OK;
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
                    extract_numbers_dollars(data, THREE_ARGS);
                    /* TODO continue */
                    break;
                case MOVE:
                case MVHI:
                case MVLO:
                    /* we expect 2 arguments */
                    extract_numbers_dollars(data, TWO_ARGS);
                    /* TODO continue */
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

