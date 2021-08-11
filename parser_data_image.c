#include "parser_data_image.h"
/* private functions */
/*
 * check if asciz row is in the correct syntax
 */
int asciz_input_check(char * data);

/*
 * copy the string from data input to array of chars in AscizRow struct
 */
int extract_asciz_string(char * data);
/* end - private functions */

/*
 * main function to parse if the input row is data image
 */
int process_data(char * data){
    int status;
    char label[LABEL_MAX_SIZE] = {NULL_SIGN};
    switch ((*row_data_type)) {
        case DB:
        case DH:
        case DW:
            status = convert_data_to_array(data);
            if(status == ERROR){
                return ERROR;
            }
            status = insert_data_row(data);
            if(status == ERROR){
                return ERROR;
            }
            break;

        case ASCIZ:
            status = init_asciz_row(); /* init row helper for string */
            if(status == ERROR){
                return ERROR;
            }
            if(asciz_input_check(data) != ERROR){
                /* if the asciz is in the correct syntax */
                status = extract_asciz_string(data); /* insert asciz row in helper variable */
                if(status == ERROR){
                    return ERROR;
                }
                status = insert_asciz_row(); /* add asciz row to linked list */
                if(status == ERROR){
                    return ERROR;
                }
            }else{
                free_asciz_row();
                return ERROR;
            }
            free_asciz_row();
            break;

        case EXTERN:
            status = get_label(data,label); /* extract the label */
            if(status == ERROR){
                return ERROR;
            }
            status = save_label(label,EXTERNAL); /* save into label list with external */
            if(status == ERROR){
                return ERROR;
            }
            break;

            /* entry will be process in the second iteration */
        case ENTRY:
            status = get_label(data,label); /* extract the label */
            if(status == ERROR){
                return ERROR;
            }
            status = add_entry_node(label); /* save into entry list */
            if(status == ERROR){
                return ERROR;
            }
            break;
    }
    return OK;
}

/*
 * copy the string from data input to array of chars in AscizRow struct
 */
int extract_asciz_string(char * data){
    int status;
    data = data + 1; /* skip first bracket */
    status = init_asciz_string();
    if(status == ERROR){
        return ERROR;
    }
    status = copy_asciz_string(data);
    if(status == ERROR){
        return ERROR;
    }
}

/*
 * check if asciz row is in the correct syntax
 */
int asciz_input_check(char * data){
    int i=1;/* start after the first bracket */
    if(*data != '\"'){
        add_error(ERROR_ASCIZ_SYNTAX,*RowNumber);
        return ERROR;
    }
    /* start after the first bracket -> counts the length of the string */
    while (data[i] != '\t' && data[i] != NEW_LINE && data[i] != NULL_SIGN && data[i] != 13 && data[i] != '\"')
    {
        i++;
    }
    if(data[i] != '\"'){ /* no end bracket on the string */
        add_error(ERROR_ASCIZ_SYNTAX,*RowNumber);
        return ERROR;
    }
    update_asciz_row_size(i); /* with \0 */
    return OK;
}
