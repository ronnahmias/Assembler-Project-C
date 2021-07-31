#include "instructions_parser.h"

extern int * Inst_Type;
extern int * Inst_Action;
extern unsigned int * help_argument_array;
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
        if(data[data_index] == NEW_LINE || data[data_index] == '\r'){
            /* line correct parsing */
            return OK;
        }else{
            add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
            return ERROR;
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
int extract_label_or_number(char *data,unsigned int * reg, char *label_dest){
    /* help variables */
    char temp_data[TRUE];
    int data_index = 0;
    int temp_index = 0;
    int help_index = 0;
    int temp_num;

    if(init_help_array(TRUE) == NULL_SIGN){
        /* error allocate*/
        return ERROR;
    }
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);

    /* expect now $ sign or alphbetical for label */
    if (!isalpha(data[data_index])){
        if(data[data_index] != '$'){
            add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
            return ERROR;
        }
    }
    /* register expect */
    if(data[data_index] == '$'){
        data_index++; /* skip '$' */
        /* take the register */
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
            *reg = 1;   /* for jmp register */
            return OK;
        }
        /* label expected */
    } else{
        /* counts label size */
        while ((data[data_index] >= '0' && data[data_index] <= '9') || isalpha(data[data_index]))
        {
            data_index++;
        }
        if(data_index > LABEL_MAX_SIZE || data_index == FALSE){ /* label over size or no label */
            add_error(ERROR_LABEL_OVERSIZE,*RowNumber);
            return ERROR;
        }
        strncpy(label_dest,data,data_index); /* copies label to label destination */
        return OK;
    }
}

/*
 * checks that we don't have arguments in the line
 */
int no_args(char *data){
    int data_index = 0;
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* no end for line -> error */
    if(data[data_index] == NEW_LINE || data[data_index] == '\r'|| data[data_index] == NULL_SIGN){
        /* line correct parsing */
        return OK;
    }else{
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
}

/*
 * extract 2 reg args and immed number 16 bits signed
*/
int extract_immed_row(char * data, signed int *immed){
    /* help variables */
    char temp_data[IMMED_DIGITS];
    int data_index = 0;
    int temp_index = 0;
    int help_index = 0;
    unsigned int temp_num;
    signed int temp_immed;

    if(init_help_array(TWO_ARGS) == NULL_SIGN){
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

    /* next need to be immed */
    memset(temp_data, 0, sizeof(temp_data)); /* init temp again */
    temp_index = 0;

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    /* check ',' sign */
    if (data[data_index] != ','){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip ',' */
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);

    /* maybe minus sign first */
    if(data[data_index] == '-'){
        temp_data[temp_index] = data[data_index]; /* insert minus */
        data_index++;
        temp_index++;
    }

    /* expect  number  sign */
    while (data[data_index] >= '0' && data[data_index] <= '9')
    {
        temp_data[temp_index] = data[data_index]; /* insert number to temp array array */
        data_index++;
        temp_index++;
    }

    /* no number insert -> error */
    if (temp_index == 0)
    {
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    temp_immed = strtol(temp_data,NULL,10); /* convert to num */
    if(immed_range(temp_immed) == ERROR){
        /* immed not in range */
        return ERROR;
    }else{
        /* insert insert to immed variable */
        *immed = temp_immed;
    }

    /* now we have another reg number */

    /* next need to be immed */
    memset(temp_data, 0, sizeof(temp_data)); /* init temp again */
    temp_index = 0;

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
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
    if(help_index == TWO_ARGS){
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
 * extract label from line input
 */
int get_label(char * data, char *label_dest){
    /* help variables */
    int data_index = 0;

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);

    /* expect now alphabetical for label */
    if (!isalpha(data[data_index])){
            add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
            return ERROR;
    }
    /* counts label size */
    while ((data[data_index] >= '0' && data[data_index] <= '9') || isalpha(data[data_index]))
    {
        data_index++;
    }
    if(data_index > LABEL_MAX_SIZE || data_index == FALSE){ /* label over size or no label */
        add_error(ERROR_LABEL_OVERSIZE,*RowNumber);
        return ERROR;
    }
    strncpy(label_dest,data,data_index); /* copies label to label destination */
    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    if(data[data_index] == NULL_SIGN || data[data_index] == '\r'){ /* the line doesnt end */
        return OK;
    }
    add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
    return ERROR;
}

/*
 * extract 2 registers numbers and one label at end
 */
int extract_numbers_label(char * data, char *label_dest){
    /* help variables */
    char temp_data[TWO_ARGS];
    int data_index = 0;
    int temp_index = 0;
    int help_index = 0;
    unsigned int temp_num;

    if(init_help_array(TWO_ARGS) == NULL_SIGN){
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
    /* need to be , char */
    if (data[data_index] != ','){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data_index++; /* skip ',' */

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);

    /* expect now alphabetical for label */
    if (!isalpha(data[data_index])){
        add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
        return ERROR;
    }
    data = data + data_index; /* skip numbers */
    data_index = 0;
    /* counts label size */
    while ((data[data_index] >= '0' && data[data_index] <= '9') || isalpha(data[data_index]))
    {
        data_index++;
    }
    if(data_index > LABEL_MAX_SIZE || data_index == FALSE){ /* label over size or no label */
        add_error(ERROR_LABEL_OVERSIZE,*RowNumber);
        return ERROR;
    }
    strncpy(label_dest,data,data_index); /* copies label to label destination */

    /* skip white chars */
    data_index += skip_white_spaces(data,data_index);
    if(data[data_index] == NULL_SIGN || data[data_index] == '\r'){ /* the line doesnt end */
        return OK;
    }
    add_error(ERROR_ARGUMENTS_ERROR, *RowNumber);
    return ERROR;
}

/*
 * process the data of the instruction row and check how many arguments
 * that match to instruction Action with the type
 */
int process_instruction(char * data){
    int error_flag,need_completion=0;
    unsigned int reg=0;
    signed int immed;
    char label[LABEL_MAX_SIZE] = {NULL_SIGN};
    signed long address = 0;
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
            error_flag = Insert_R_Args();
            if(error_flag == ERROR){
                return ERROR;
            }
            break;
        case J:
            switch(*Inst_Action){
                case JMP:
                    /* 1 label or number as argument expect */
                    error_flag = extract_label_or_number(data, &reg, label);
                    if(error_flag == ERROR){
                        return ERROR;
                    }
                    /* only if we have label as argument */
                    if(label[FIRST_INDEX] != NULL_SIGN){
                        need_completion = TRUE;
                    }
                    break;
                case LA:
                case CALL:
                    /* label as argument expect */
                    error_flag = get_label(data,label);
                    if(error_flag == ERROR){
                        return ERROR;
                    }
                    need_completion = TRUE;
                    break;
                case STOP:
                    /* no arguments expected */
                    error_flag = no_args(data);
                    break;
            }
            if(error_flag == ERROR){
                return ERROR;
            }
            Insert_J_Args(address,reg,need_completion,label);
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
                    error_flag = extract_immed_row(data,&immed);
                    break;
                case BEQ:
                case BNE:
                case BLT:
                case BGT:
                    /* expect 2 argument with $ and label at end */
                    error_flag = extract_numbers_label(data,label);
                    immed = 0;
                    need_completion = TRUE;
                    break;
            }
            Insert_I_Args(immed,need_completion,label);
            break;
    }
    if(error_flag == ERROR){
        return ERROR;
    }
    return OK;
}

