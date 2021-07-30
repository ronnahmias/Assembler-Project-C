#include "helpers.h"

/*
 * init variables for the whole file
 */
int init_every_file(){
    RowNumber = (int*) calloc(1,sizeof(int));
    init_errors_data();
    if(RowNumber != NULL && init_row_has_error() && init_dc()
    && init_instruction_vars() && init_ic() && init_data()){
        return OK;
    }
    /* we have found error in init functions */
    program_error(ERROR_ALLOCATING_MEMORY);
    return ERROR;
}

/*
 * free variables every file end
 */
void free_every_file(){
    /*free(RowNumber);*/
    free_ic();
    free_dc();
    free_row_has_error();
    free_instruction_vars();
    free_data();

}

/*
 * init variables that we need every row
 */
void init_every_row(){
    reset_instruction_vars();
    reset_data();
    reset_row_has_error();
    *row_data_type = NO_DATA_TYPE;
    *RowNumber++;
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
        return FALSE;
    }
    return TRUE;
}