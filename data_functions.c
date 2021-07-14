#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

void init(){

}

int search_data_type(char * input)
{
    int i, j=0;
    while (!isspace(input[j])) /* counts the length of the command  -> until the space */
    {
        j++;
    }

    for (i = 0; i < DATA_TYPE_NUMBER; i++)
    {
        if (!strncmp(data_type[i], input,j) && strlen(data_type[i]) == j && data_type[i] == input) /* compare the set for the list of commands */
        {
            return i;
        }
    }
    return -1;
}

dataNode * init_data_node(int data,int data_type)
{
    dataNode * pt;
    pt = (dataNode *)calloc(sizeof(dataNode),1);
    if(pt == NULL){
        // TODO error allocation
    }
    pt->next = NULL;
    switch (data_type) {
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
    pt->address = NULL; // TODO address counter
    return pt;
}

dataNode * add_node(dataNode *newNode)
{
    if(DataNodes->next == NULL){ /* this is the first node in the data nodes */
        DataNodes->next = newNode;
    }else{
        dataNode * cur_node = DataNodes;
        while(cur_node != NULL){ /* insert to tail of the linked list of data nodes */
            cur_node->next = newNode;
        }
    }
}

