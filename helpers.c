#include "helpers.h"
/*
 * init variables
 */
void init(){
    RowNumber = (int*) calloc(sizeof (int),1);
    if(RowNumber == NULL){
        add_error(ERROR_ALLOCATING_MEMORY,NO_LINE_NUMBER);
    }
}

/*
 *  update file name for the current file open
 */
void update_current_file_name(char * name){
    FileName = malloc(strlen(name) + EXT_LEN + 1);
}