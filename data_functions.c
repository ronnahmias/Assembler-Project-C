#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

/* data_image variables */
dataNode * DataNodes;
asciz_row * AscizRow;
data_row * DataRow;

/* private data functions */
/*
 * init data node for linked list for data input
 */
dataNode * init_data_node(long data);

/*
 * adds the new node to linked list at the end
 */
dataNode * add_data_node(dataNode **newNode);

/*
 * realloc array long of the row input data
*/
int realloc_data_row();

/*
 * init data row struct for data input row
*/
int init_data_row();

/*
 * zero all input num for the next number in the input
 */
void zero_input_num();

/*
 * checks size limit of data
 */
int check_data_size(long num);

/* end - private data functions */

/*
 * init data counter
 */
int init_dc(){
    DC = (signed long*) calloc(1,sizeof(signed long));
    if(DC == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    return TRUE;
}

/*
 * free data counter
 */
void free_dc(){
    free(DC);
}

/*
 * init required variables
 */
int init_data(){
    row_data_type = (int *)calloc(1,sizeof(int)); /* data type for each row */
    if(row_data_type == NULL) {
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
}

/*
 * reset data variables
 */
void reset_data(){
    memset(row_data_type,0,sizeof(row_data_type));
}

/*
 * free data variables
 */
void free_data(){
    free(row_data_type);
}

/*
 * init struct helper for string input row
 */
int init_asciz_row(){
    AscizRow = (asciz_row *)calloc(1,sizeof(asciz_row));
    if(AscizRow == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    return OK;
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
int init_asciz_string(){
    AscizRow->string = (char*) calloc(AscizRow->size,sizeof(char));
    if(AscizRow->string == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
}

/*
 * add asciz array of chars to linked list data nodes
 */
int insert_asciz_row(){
    int i;
    dataNode * node;
    for(i=0;i<AscizRow->size;i++){ /* also takes 1 null at the end */
        node = NULL;
        node = init_data_node(AscizRow->string[i]);
        if(node == NULL_SIGN){
            program_error(ERROR_ALLOCATING_MEMORY);
            return ERROR;
        }
        add_data_node(&node);
    }
    free(AscizRow->string);
    return OK;
}

/*
 * insert from long array of numbers to data nodes
 * after -> connect to linked data list
 */
int insert_data_row(){
    int i;
    dataNode *newNode;
    for (i = 0; DataRow->array[i] ; i++) {
        newNode = init_data_node(DataRow->array[i]);
        if(newNode == NULL_SIGN){
            return ERROR;
        }
        add_data_node(&newNode);
    }
    /* free data row */
    free(DataRow->array);
    free(DataRow);
}

/*
 * init data row struct for data input row
*/
int init_data_row(){
    DataRow = (data_row *)calloc(1,sizeof(data_row));
    if(DataRow == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    DataRow->array = (long *)calloc(1,sizeof(long));
    if(DataRow->array == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    DataRow->size = 1;
}

 /*
  * reallocate array long of the row input data
 */
int realloc_data_row(){
    DataRow->array = (long *)realloc(DataRow->array,(DataRow->size +1));
    if(DataRow->array == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
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
        if (!strncmp(data_type[i], input,j) && strlen(data_type[i]) == j)
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
int convert_data_to_array(char * data){
    int i=0, status;
    char * ptr;
    long num;
    if(init_data_row() == ERROR){
        return ERROR;
    }
    while (data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\r') {
        /* backspace skip it*/
        if (data[i] == ' ' || data[i] == '\t') {
            i++;
            continue;
        }
        /* end of number -> insert to long array */
        if (data[i] == ',') {
            /* convert to long number before insert */
            num = strtol(DataRow->input_num, &ptr, 10);
            if(check_data_size(num)== ERROR){
                add_error(ERROR_MAX_DATA,*RowNumber);
                return ERROR;
            }
            DataRow->array[DataRow->size - 1] = num;
            status = realloc_data_row();
            if (status == ERROR) {
                return ERROR;
            }
            zero_input_num();
        } else { /* insert number to array */
            DataRow->input_num[DataRow->input_num_size] = data[i];
            DataRow->input_num_size++;
            /* the number is bigger with number of digits */
            if (DataRow->input_num_size > INPUT_NUM) {
                add_error(ERROR_MAX_DATA, *RowNumber);
                return ERROR;
            }
        }
        i++;
    }
    /* there is number to insert to array */
    if (DataRow->input_num[0] != '\0') {
        DataRow->array[DataRow->size - 1] = strtol(DataRow->input_num, &ptr, 10);
    }
    /* free input num  char array helper */
    return OK;
}

/*
 * checks size limit of data
 */
int check_data_size(long num){
    double n;
    double  BLimit,TLimit;
    switch (*row_data_type) {
        case DB:
            n= ONE_BYTE_SIZE;
            break;
        case DH:
            n= HALF_WORD_SIZE;
            break;
        case DW:
            n=WHOLE_WORD_SIZE;
            break;
    }
    BLimit = -(pow((double)2,n) / 2);
    TLimit = (pow((double)2,n) / 2) - 1;
    if(num >= BLimit && num <= TLimit){
        return OK;
    }
    return ERROR;
}

/*
 * copy the input data of string to AscizRow structure
 */
void copy_asciz_string(char * data){
    strncpy(AscizRow->string,data,AscizRow->size-1);
    AscizRow->string[AscizRow->size-1] = NULL_SIGN;
}

/*
 * update string input size to struct
 */
void update_asciz_row_size(int size){
    AscizRow->size = size;
}

/*
 * init data for the data code
 */
dataNode * init_data_code(dataNode ** newNode, long data){
    switch (*row_data_type) {
        case DB:
        case ASCIZ:
            (*newNode)->db = (char *) calloc(1,sizeof(char));
            if((*newNode)->db == NULL){
                program_error(ERROR_ALLOCATING_MEMORY);
                return NULL;
            }
            *((*newNode)->db) = (char)data;
            *DC = *DC + 1; /* increase DC */
            break;
            /* half word */
        case DH:
            (*newNode)->dh = (int *) calloc(1,sizeof(int));
            if((*newNode)->dh == NULL){
                program_error(ERROR_ALLOCATING_MEMORY);
                return NULL;
            }
            *((*newNode)->dh) = (int)data;
            *DC = *DC + 2; /* increase DC */
            break;
            /* whole word */
        case DW:
            (*newNode)->dw = (signed long *) calloc(1,sizeof(signed long));
            if((*newNode)->dw == NULL){
                program_error(ERROR_ALLOCATING_MEMORY);
                return NULL;
            }
            *((*newNode)->dw) = data;
            *DC = *DC + 4; /* increase DC */
            break;
    }
    return *newNode;
}

/*
 * init data node for linked list for data input
 */
dataNode * init_data_node(long data)
{
    dataNode * newNode = NULL;
    newNode = (dataNode *)calloc(1,sizeof(dataNode));
    if(newNode == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL_SIGN;
    }
    newNode->datatype = *row_data_type; /* save the data type in the node */
    newNode->address = *DC;
    newNode = init_data_code(&newNode,data); /* init the data size in the node */
    return newNode;
}

/*
 * adds the new node to linked list at the end
 */
dataNode * add_data_node(dataNode **newNode)
{
    dataNode * cur_node;
    if(DataNodes == NULL){ /* this is the first node in the data nodes */
        DataNodes = *newNode;
    }else{
        cur_node = DataNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of data nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = *newNode;
    }
}

/*
 * update addresses in data list add the current IC
 */
int update_data_list_addresses(){
    dataNode *cur_node;
    cur_node = DataNodes;
    while(cur_node){
        cur_node->address += get_ic();
        cur_node = cur_node->next;
    }
}

/*
 * get the data node of next node from head in linked list
 */
dataNode * get_next_node_data(){
    dataNode * node;
    if(DataNodes == NULL){
        return NULL;
    }
    node = DataNodes;
    DataNodes = DataNodes->next;
    return node;
}

/*
 * checks if there is data nodes for export
 */
int data_exists(){
    if(DataNodes == NULL){
        return FALSE;
    }
    return TRUE;
}

/*
 * free data linked list
 */
void free_data_nodes(){
    dataNode * node;
    if(DataNodes == NULL){
        return;
    }

    while(DataNodes){
        node = DataNodes;
        DataNodes = DataNodes->next;
        free(node);
    }
}