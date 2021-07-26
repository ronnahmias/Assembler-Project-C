#include "helpers.h"
/*
 * init variables
 */
int init(){
    RowNumber = (int*) calloc(sizeof (int),1);
    if(RowNumber != NULL && init_row_has_error() && init_dc()
    && init_instruction_vars() && init_ic()){
        return OK;
    }
    /* we have found error in init functions */
    program_error(ERROR_ALLOCATING_MEMORY);
    return FALSE;
}

/*
 * counts white spaces
 */
int skip_white_spaces(char * data,int index){
    int i=0;
    while (data[index] == ' ' || data[index] == '\t')
    {
        index++;
        i++;
    }
    return i;
}

/*
 * checks range of register between 0-31
 */
int register_range(unsigned int num){
    if(num > MAX_REGISTER || num < MIN_REGISTER){
        add_error(ERROR_REGISTER_RANGE, *RowNumber);
        return ERROR;
    }
    return OK;
}

/*
 * checks range of immed number
 */
int immed_range(signed int num){
    if(num > MAX_IMMED || num < MIN_IMMED){
        add_error(ERROR_IMMED_RANGE, *RowNumber);
        return ERROR;
    }
    return OK;
}

/*
 * checks that label is start with char and not a number
 */
int label_start_char(char * data){
    if(isalpha(data[FIRST_INDEX])){
        return TRUE;
    }
    return FALSE;
}

/*
 *  update file name for the current file open
 */
void update_current_file_name(char * name){
    FileName = malloc(strlen(name) + EXT_LEN + 1);
    FileName = name;
}

/*
 * checks input file extension .as
 */
int check_file_extension(){
    char *ext;
    ext = strstr(FileName,DOT);
    /* good file ext */
    if(ext == NULL || strcmp(ext,EXT_INPUT_FILES) != 0){
        return 0;
    }
    return 1;
}

/* TODO free vars */