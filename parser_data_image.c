#include "parser_data_image.h"

/*
 * main function to parse if the input row is data image
 */
int process_data(char * data){
    int status;
    char label[LABEL_MAX_SIZE];
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
            status = save_label(label,EXTERNAL); /* save into label list with external */
            break;

            /* entry will be process in the second iteration */
        case ENTRY:
            break;
    }
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
    copy_asciz_string(data);
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
    while (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\"')
    {
        i++;
    }
    if(data[i] != '\"'){ /* no end bracket on the string */
        add_error(ERROR_ASCIZ_SYNTAX,*RowNumber);
        return ERROR;
    }
    update_asciz_row_size(i-1); /* without end bracket */
    return OK;
}
