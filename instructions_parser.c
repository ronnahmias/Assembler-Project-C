#include "instructions_parser.h"

extern int * Inst_Type;
extern int * Inst_Action;
extern unsigned int * help_argument_array;
extern signed int * immed;
extern int *RowNumber;

extern inst_type_enum instruction_type;
extern instruction_r_enum instruction_r;
extern instruction_j_enum instruction_j;
extern instruction_i_enum instruction_i;

/*
 * extract from string numbers that near the dollar sign
 * according to number of argument expected
*/
int r_instruction_parse(char * data, int num_args){
    /* help variables */
    char temp_data[TWO_ARGS];
    int data_index = 0;
    int temp_index = 0;
    int help_index = 0;
    unsigned int temp_num;

    if(init_help_array(num_args) == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* expect now $ sign */
    if (data[data_index] != '$'){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip '$' */
    /* take the first register */
    while (data[data_index] >= '0' && data[data_index] <= '9')
    {
        temp_data[temp_index] = data[data_index]; /* insert number to temp array array */
        data_index++;
        temp_index++;
    }
    /* no number insert or over 2 digits -> error */
    if (temp_index == 0 || temp_index > 2)
    {
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    temp_num = strtol(temp_data,NULL,10); /* convert to num */
    if(register_range(temp_num) == ERROR){
        /* register not in range */
        return ERROR;
    }else{
        /* insert number to array for future process */
        help_argument_array[help_index] = temp_num;
        help_index++;
    }
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* need to be , char */
    if (data[data_index] != ','){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip ',' */

    /* next number */
    memset(temp_data, 0, sizeof(temp_data));
    temp_index = 0;

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* expect now $ sign */
    if (data[data_index] != '$'){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip '$' */
    /* take the second register */
    while (data[data_index] >= '0' && data[data_index] <= '9')
    {
        temp_data[temp_index] = data[data_index]; /* insert number to temp array array */
        data_index++;
        temp_index++;
    }
    /* no number insert or over 2 digits -> error */
    if (temp_index == 0 || temp_index > 2)
    {
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    temp_num = strtol(temp_data,NULL,10); /* convert to num */
    if(register_range(temp_num) == ERROR){
        /* register not in range */
        return ERROR;
    }else{
        /* insert number to array for future process */
        help_argument_array[help_index] = temp_num;
        help_index++;
    }
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* we have the num args -> check for new line */
    if(help_index == num_args){
        /* no end for line -> error */
        if(data[data_index] != NEW_LINE || data[data_index] != '\r'){
            add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
            return ERROR;
        }else{
            /* line correct parsing */
            return OK;
        }
    }

    /* we have 1 more argument with $ */
    memset(temp_data, 0, sizeof(temp_data)); /* init temp again */
    temp_index = 0;

    /* check ',' sign */
    if (data[data_index] != ','){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip ',' */
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* expect now $ sign */
    if (data[data_index] != '$'){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip '$' */
    /* take the second register */
    while (data[data_index] >= '0' && data[data_index] <= '9')
    {
        temp_data[temp_index] = data[data_index]; /* insert number to temp array array */
        data_index++;
        temp_index++;
    }
    /* no number insert or over 2 digits -> error */
    if (temp_index == 0 || temp_index > 2)
    {
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    temp_num = strtol(temp_data,NULL,10); /* convert to num */
    if(register_range(temp_num) == ERROR){
        /* register not in range */
        return ERROR;
    }else{
        /* insert number to array for future process */
        help_argument_array[help_index] = temp_num;
        help_index++;
    }
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    if(help_index == num_args){
        /* no end for line -> error */
        if(data[data_index] == NEW_LINE || data[data_index] == '\r'){
            /* line correct parsing */
            return OK;
        }else{
            add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
            return ERROR;
        }
    }else{
        /* something went wrong */
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }


}

/*
 * parsing input label or number in the line
 */
int extract_label_or_number(char *data, int * reg){
    int i=0,dollar_flag =0, help_index=0, j=0, temp_num;
    char temp[3];
    if(init_help_array(TRUE) == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    while(data[i] != '\n'){
        if(isspace(data[i]) &&  data[i] != NEW_LINE){ /* white chars */
            i++;
            continue;
        }
        if(dollar_flag){
            temp[j++] = data[i++];
            continue;
        }
        if(data[i] == '$'){
            /* register */
            dollar_flag =1;
            i++;
            continue;
        }else{
            /* need to be label */
            i++;
        }
    }
    if(dollar_flag){
        temp_num = strtol(temp,NULL,10); /* convert to num */
        if(temp_num < MIN_REGISTER || temp_num>MAX_REGISTER){ /* registers between 0-31 */
            add_error(ERROR_PARSING_NUMBER,*RowNumber);
            return ERROR;
        }
        help_argument_array[help_index++] = temp_num;
        *reg = 1;
    }else{
        /* TODO label save check if the label is in symbol nodes */
        *reg = 0;
    }
}

/*
 * extract label from string data
 */
int extract_label(char *data){
    int i=0;
    if(init_help_array(TRUE) == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    data = delete_spaces(data);
    if(!label_start_char(data)){
        add_error(ERROR_LABEL_SYNTAX, *RowNumber);
        return ERROR;
    }
    while(data[i] != '\n'){
        if(isspace(data[i]) &&  data[i] != NEW_LINE){ /* white chars */
            if(i>FIRST_INDEX){/* there is white char in the label -> error */
                add_error(ERROR_LABEL_SYNTAX, *RowNumber);
                return ERROR;
            }
            i++;
            continue;
        }
        i++; /* count label size */
    }
    /* TODO check if label declared in symbol node*/
}

/*
 * checks that we don't have arguments in the line
 */
int no_args(char *data){
    int i=0;
    data = delete_spaces(data);
    while(data[i] != '\n'){
        if(!isspace(data[i]) &&  data[i] != NEW_LINE){ /* there is more chars -> errors */
            add_error(ERROR_STOP_ARGUMENT,*RowNumber);
            return ERROR;
        }
        i++;
    }
    return OK;
}

/*
 * extract from string numbers that near the dollar sign
 * according to number of argument expected
*/
int extract_immed_dollar(char * data, int num_args){
    int i=0,dollar_flag =0,char_num_index = 0;
    char temp_char_num[3];
    if(init_help_array(TWO_ARGS) == NULL_SIGN || init_immed() == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    while(data[i] != '\n') {
        if(dollar_flag){
            if(isspace(data[i])){ /* after dollar we need number */
                add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
                return ERROR;
            }
            temp_char_num[char_num_index++] = data[i]; /* insert the number to temp array */

        }
        if(isspace(data[i]) &&  data[i] != NEW_LINE){ /* white chars */
            i++;
            continue;
        }
        if(data[i] == '$'){
            dollar_flag = 1;
            i++;
            continue;
        }
    }
    /* we have run over all the arguments */
    return OK;
}



/*
 * process the data of the instruction row and check how many arguments
 * that match to instruction Action with the type
 */
int process_instruction(char * data,int iteration){
    int error_flag, reg=0;
    switch(*Inst_Type){
        case R:
            switch(*Inst_Action){
                case ADD:
                case SUB:
                case AND:
                case OR:
                case NOR:
                    /* we expect 3 arguments with $ */
                    error_flag = r_instruction_parse(data, THREE_ARGS);
                    break;
                case MOVE:
                case MVHI:
                case MVLO:
                    /* we expect 2 arguments */
                    error_flag = r_instruction_parse(data, TWO_ARGS);
                    break;
            }
            if(error_flag == ERROR){
                return ERROR;
            }
            /* insert the number to node and add the node to linked list */
            Insert_R_Args();
            break;
        case J:
            switch(*Inst_Action){
                case JMP:
                    /* 1 label or number as argument expect */
                    error_flag = extract_label_or_number(data, &reg);
                    break;
                case LA:
                case CALL:
                    /* label as argument expect */
                    error_flag = extract_label(data);
                    break;
                case STOP:
                    /* no arguments expected */
                    error_flag = no_args(data);
                    break;
            }
            if(error_flag == ERROR){
                return ERROR;
            }
            Insert_J_Args(reg);
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
                    /* expect 3 arguments 1 number in the center without $ */
                    error_flag = extract_immed_dollar(data,TWO_ARGS);
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
    if(error_flag == ERROR){
        return ERROR;
    }
    return OK;
}

