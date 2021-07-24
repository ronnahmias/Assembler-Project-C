#include "parser.h"

/*
 * function that reads from the current file line
 */
void read_by_line(FILE *cur_file, int iteration){
    char data[ROW_LINE];
    while(fgets(data, sizeof(data),cur_file)) /* read from file line by line */
    {
        *row_data_type = NO_DATA_TYPE;
        RowNumber ++;
        process_input(data,iteration);
        reset_row_has_error();
    }
}

/*
 * process the input and check different options of the input
 */
int process_input(char *input_row, int iteration){
    int label_size, status, instruction_size, has_error = 0;
    input_row = delete_spaces(input_row); /* delete white spaces if have */
    label_size = has_label(input_row); /* check if it has label first */
    if(row_has_error()){ /* fount error in syntax of label */
        return ERROR;
    }
    if(label_size != FALSE){ /* we have found label */
        if(label_size > LABEL_MAX_SIZE){
            add_error(ERROR_LABEL_OVERSIZE,*RowNumber);
            return ERROR;
        }
        status = save_label(input_row, label_size);
        if(status == FALSE){ /* error return */
            return ERROR;
        }
        input_row = skip_label(input_row); /* skip the label from the row */
        input_row = delete_spaces(input_row); /* delete white spaces if have */
    }
    if(is_dot(*input_row)){ /* check if it is data row */
        input_row = input_row + 1; /* skip the dot */
        search_data_type(input_row);
        if(*row_data_type == NO_DATA_TYPE){
            add_error(ERROR_NO_DATA_TYPE, *RowNumber);
            return ERROR; /* continue to next line because error */
        }
        input_row = skip_word(input_row);/* skip the word in the line to have data */
        input_row = delete_spaces(input_row);
        process_data(input_row,iteration);
    }else{
        /* check the long of instruction */
        if(instruction_size = count_instruction_long(input_row)){
            /* find the instruction from 3 arrays */
            has_error = find_instruction(input_row, instruction_size);
            if(has_error == NO_INSTRUCTION_FOUND){
                add_error(ERROR_INSTRUCTION_NOT_FOUND, *RowNumber);
                return ERROR;
            }
            input_row = skip_word(input_row);
            input_row = delete_spaces(input_row);
            process_instruction(input_row,iteration);
        }else{
            add_error(ERROR_INSTRUCTION_NOT_FOUND, *RowNumber);
            return ERROR;
        }
    }
}

/*
 * count the long of the instruction
 */
int count_instruction_long(char *data){
    int i = 0;
    while (data[i] != ' ') /* until space */
    {
        i++;
    }
    if(i> INSTRUCTION_MAX_SIZE){
        add_error(ERROR_INSTRUCTION_NOT_FOUND, *RowNumber);
        return FALSE;
    }
    return i;
}

/*
 * skip the label -> cut the label from the input
 */
char * skip_label(char* input){
    int i = 0;
    while (input[i] != ':')
    {
        i++;
    }
    i++; /* skip also : sign */
    save_label(input, i);
    return input + i;
}

/*
 * checks if the input has label
 */
int has_label(char * data){
    int i=0;
    while (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != ':')
    {
        i++;
    }
    if(data[i] != ':'){ /* not label found in the row */
        return FALSE;
    }
    if(data[i] == ':' && data[i-1] != ' '){ /* there is label */
        return i;
    }
    add_error(ERROR_LABEL_SYNTAX, *RowNumber);
    return FALSE; /* return size of label */

}

/*
 * checks if the char is dot or not
 */
int is_dot(char ch){
    int res;
    return (ch==46) ?  1 : 0;
}

/*
 * skip the word from input row until the space
 */
char * skip_word(char* input){
    int i = 0;
    while (!isspace(input[i]))
    {
        i++;
    }
    return input + i;
}

/*
 * delete spaces from input
 */
char * delete_spaces(char* input){
    int i = 0;
    while (input[i] != 0 && isspace(input[i]))
    {
        i++;
    }
    return input + i;
}
