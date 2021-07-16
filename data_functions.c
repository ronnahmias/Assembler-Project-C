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

dataNode * init_data_node(int data)
{
    dataNode * pt;
    pt = (dataNode *)calloc(sizeof(dataNode),1);
    if(pt == NULL){
        // TODO error allocation
    }
    switch (*row_data_type) {
        /* byte size */
        case DB:
        case ASCIZ:
            pt->db = data;
            break;
        /* half word */
        case DH:
            pt->dh = data;
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


