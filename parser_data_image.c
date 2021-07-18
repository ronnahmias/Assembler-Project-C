#include "parser_data_image.h"

/*
 * main function to parse if the input row is data image
 */
void process_data(char * data, int iteration){
    if(iteration == FIRST_ITER){ /* process data -> first iteration*/
        switch ((*row_data_type)) {

            case DB:
            case DH:
            case DW:
                convert_data_to_array(data);
                insert_data_row(data);
                break;

            case ASCIZ:
                init_asciz_row();
                if(asciz_input_check(data)){
                    /* if the asciz is in the correct syntax */
                    extract_asciz_string(data);
                    insert_asciz_row();
                }else{
                    /* TODO error asciz string*/
                }
                free_asciz_row();
                break;

            case EXTERN:
                break;

                /* entry will be process in the second iteration */
            case ENTRY:
                return;
        }
    }
}

/*
 * copy the string from data input to array of chars in AscizRow struct
 */
char * extract_asciz_string(char * data){
    data = data + 1; /* skip first bracket */
    init_asciz_string();
    copy_asciz_string(data);
}

/*
 * check if asciz row is in the correct syntax
 */
int asciz_input_check(char * data){
    int i=1;/* start after the first bracket */
    if(*data != '\"'){
        /* TODO Error string*/
        return FALSE;
    }
    /* start after the first bracket -> counts the length of the string */
    while (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\"')
    {
        i++;
    }
    if(data[i] != '\"'){ /* no end bracket on the string */
        /* TODO error string return*/
        return FALSE;
    }
    update_asciz_row_size(i-1); /* without end bracket */
    return TRUE;
}
