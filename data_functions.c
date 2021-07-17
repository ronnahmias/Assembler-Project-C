#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

/*
 * init required variables
 */
void init_data(){
    row_data_type = (int *)calloc(1,sizeof(int)); /* data type for each row */ // TODO replace 1 with define
    if(row_data_type == NULL) {
        printf("null");
        // TODO error alocation
    }
}

/*
 * init struct helper for string input row
 */
void init_asciz_row(){
    AscizRow = (asciz_row *)calloc(sizeof(asciz_row),1);
    if(AscizRow == NULL){
        // TODO error allocation
    }
    AscizRow->size = 0;
}

/*
 * free struct helper for string input
 */
void free_asciz_row(){
    free(AscizRow);
}

/*
 * init char array in struct of string input row
 */
void init_asciz_string(){
    AscizRow->string = (char*) calloc(sizeof(char),AscizRow->size);
    if(AscizRow->string == NULL){
        // tODO Error allocating
    }
}

/*
 * add asciz array of chars to linked list data nodes
 */
void insert_asciz_row(){
    int i;
    dataNode * pt;
    for(i=0;AscizRow->string[i];i++){
        pt = init_data_node(AscizRow->string[i]);
        // TODO check pointer
        add_data_node(pt);
    }
}

/*
 * insert from long array of numbers to data nodes
 * after -> connect to linked data list
 */
void insert_data_row(){
    int i;
    dataNode *newNode;
    for (i = 0; DataRow->array[i] ; i++) {
        newNode = init_data_node(DataRow->array[i]);
        add_data_node(newNode);
    }
    /* free data row */
    free(DataRow->array);
    free(DataRow);
}

/*
 * init data row struct for data input row
*/
void init_data_row(){
    DataRow = (data_row *)calloc(sizeof(data_row),1);
    if(DataRow == NULL){
        // TODO error allocation
    }
    DataRow->array = (long *)calloc(sizeof(long),1);
    if(DataRow->array == NULL){
        // TODO error allocation
    }
    DataRow->size = 1;
}

 /*
  * realloc array long of the row input data
 */
void realloc_data_row(){
    DataRow->array = (long *)realloc(DataRow->array,(DataRow->size +1));
    if(DataRow->array == NULL){
        // TODO error allocation
    }
    DataRow->size ++;
}

/*
 * zero all input num for the next number in the input
 */
void zero_input_num(){
    int i;
    for(i=0;i<INPUT_NUM;i++){
        DataRow->input_num[i] = '\0';
    }
    DataRow->input_num_size = 0;
}

/*
 * find the data type of the input row from array
 */
void search_data_type(char * input)
{
    int i, j=0;
    while (!isspace(input[j])) /* counts the length of the command  -> until the space */
    {
        j++;
    }

    for (i = 0; i < DATA_TYPE_NUMBER; i++)
    {
        if (!strncmp(data_type[i], input,j) && strlen(data_type[i]) == j) /* compare the set for the list of commands */
        {
            *row_data_type = i;
            return;
        }
    }
    *row_data_type= NO_DATA_TYPE;
}

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
            /* the number is bigger than 2^32 */
            if(DataRow->input_num_size > INPUT_NUM){
                // TODO error over size
            }
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

/*
 * init data node for linked list for data input
 */
dataNode * init_data_node(long data)
{
    dataNode * pt;
    pt = (dataNode *)calloc(sizeof(dataNode),1);
    if(pt == NULL){
        // TODO error allocation
    }
    switch (*row_data_type) {
        /* byte size */
        case DB:
        case ASCIZ: // TODO check asciz again
            pt->db = (char)data;
            break;
        /* half word */
        case DH:
            pt->dh = (int)data;
            break;
        /* whole word */
        case DW:
            pt->dw = data;
            break;

    }
    pt->address = 0; // TODO address counter
    return pt;
}

/*
 * adds the new node to linked list at the end
 */
dataNode * add_data_node(dataNode *newNode)
{
    dataNode * cur_node;
    if(DataNodes == NULL){ /* this is the first node in the data nodes */
        DataNodes = newNode;
    }else{
        cur_node = DataNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of data nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = newNode;
    }
}


