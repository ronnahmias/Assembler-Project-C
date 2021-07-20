#include "helpers.h"
/*
 * init variables
 */
void init(){
    RowNumber = (int*) calloc(sizeof (int),1);
    if(RowNumber == NULL){
        add_error(ERROR_ALLOCATING_MEMORY,NO_LINE_NUMBER);
    }
    init_row_has_error();
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