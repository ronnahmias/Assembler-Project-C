#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

void init_data(){
    row_data_type = (int *)calloc(1,sizeof(int)); /* data type for each row */ // TODO replace 1 with define
    if(row_data_type == NULL) {
        printf("null");
        // TODO error alocation
    }
}

void init_asciz_row(){
    AscizRow = (asciz_row *)calloc(sizeof(asciz_row),1);
    if(AscizRow == NULL){
        // TODO error allocation
    }
    AscizRow->size = 0;
}

void free_asciz_row(){
    free(AscizRow);
}

void init_asciz_string(){
    AscizRow->string = (char*) calloc(sizeof(char),AscizRow->size);
    if(AscizRow->string == NULL){
        // tODO Error allocating
    }
}

/* add asciz array of chars to linked list data nodes */
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
    for (i = 0; i < DataRow->array[i]; i++) {
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


