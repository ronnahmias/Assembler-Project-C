#include "helpers.h"

void read_by_line(FILE *cur_file, int iteration){
    char data[ROW_LINE];
    //fscanf(cur_file, "%c", &data);
    while(fgets(data, sizeof(data),cur_file)) /* read from file line by line */
    {
        *row_data_type = NO_DATA_TYPE;
        process_input(data,iteration);
    }
}

void process_input(char *input_row, int iteration){
    printf("%s", input_row); // TODO remove
    input_row = delete_spaces(input_row); /* delete white spaces if have */
    if(has_label(input_row)){ /* check if it has label first */
        //TODO save label
        input_row = skip_label(input_row); /* skip the label from the row */
        input_row = delete_spaces(input_row); /* delete white spaces if have */
    }
    if(is_dot(*input_row)){ /* check if it is data row */
        input_row = input_row + 1; /* skip the dot */
        search_data_type(input_row);
        if(*row_data_type == NO_DATA_TYPE){
            // TODO ERROR NO DATA TYPE FOUND
        }
        input_row = skip_word(input_row);/* skip the word in the line to have data */
        input_row = delete_spaces(input_row);
        process_data(input_row,iteration);
    }
}

char * skip_label(char* input) /* skip the label */
{
    int i = 0;
    while (input[i] != ':')
    {
        i++;
    }
    i++; /* skip also : sign */
    return input + i;
}

int has_label(char * data){
    int i=0;
    while (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != ':')
    {
        i++;
    }
    if(data[i] != ':'){ /* not label found in the row */
        return FALSE;
    }
    return i; /* return size of label */

}

void process_data(char * data, int iteration){
    if(iteration == FIRST_ITER){ /* process data -> first iteration*/
        switch ((*row_data_type)) {

            case DB:
            case DH:
            case DW:
                convert_data_to_array(data);
                insert_data_row(data);
                // TODO remove after check binary
                unsigned i;
                dataNode * cur = DataNodes;
                while(cur != NULL) {
//                    for (i = 1 << 31; i > 0; i = i / 2)
//                        (DataNodes->db & i) ? printf("1") : printf("0");
                    printf("%d", cur->db);
                    cur = cur->next;
                    putchar('\n');
                }
                // TODO end removing
                break;

            case ASCIZ:
                init_asciz_row();
                if(asciz_input_check(data)){
                    /* if the asciz is in the correct syntax */
                    extract_asciz_string(data);
                    insert_asciz_row();
                }else{
                    // TODO error asciz string
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
/* // TODO remove
 * convert data array of chars to long number
 */
//long array_char_to_long(){
//    long res
//}

/*
 * convert data row numbers (db,dw,dh) to long array before insert to linked list
 */
void convert_data_to_array(char * data){
    int i=0;
    char * ptr;
    init_data_row();
    while (data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13)
    {
        /* backspace skip it*/
        if(data[i] == ' '){
            i++;
            continue;
        }
        /* end of number -> insert to long array */
        if(data[i] == ','){
            /* convert to long number before insert */
            DataRow->array[DataRow->size-1] = strtol(DataRow->input_num,&ptr,10);
            realloc_data_row();
            zero_input_num();
        }else{ /* insert number to array */
            DataRow->input_num[DataRow->input_num_size] = data[i];
            DataRow->input_num_size ++;
        }
        i++;
    }
    /* more number to insert to array */
    if(DataRow->input_num[0] != '\0'){
        DataRow->array[DataRow->size-1] = strtol(DataRow->input_num,&ptr,10);

    }
    /* free input num  char array helper */ // TODO
    //free(DataRow->input_num);
}

char * extract_asciz_string(char * data){
    data = data + 1; /* skip first bracket */
    init_asciz_string();
    strncpy(AscizRow->string,data,AscizRow->size);
}

int asciz_input_check(char * data){
    int i=1;/* start after the first bracket */
    if(*data != '\"'){
        // TODO Error string
        return FALSE;
    }
    /* start after the first bracket -> counts the length of the string */
    while (data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\"')
    {
        i++;
    }
    if(data[i] != '\"'){ /* no end bracket on the string */
        // TODO error string return
        return FALSE;
    }
    AscizRow->size = i-1; /* without end bracket */
    return TRUE;
}

int is_dot(char ch){
    int res;
    return (ch==46) ?  1 : 0;
}

char * skip_word(char* input){ /* skip the word */
    int i = 0;
    while (!isspace(input[i]))
    {
        i++;
    }
    return input + i;
}

char * delete_spaces(char* input) /* delete space */{
    int i = 0;
    while (input[i] != 0 && isspace(input[i]))
    {
        i++;
    }
    return input + i;
}