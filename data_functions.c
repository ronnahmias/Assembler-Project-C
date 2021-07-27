#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

/* data_image variables */
dataNode * DataNodes;
asciz_row * AscizRow;
data_row * DataRow;

/*
 * init data counter
 */
int init_dc(){
    DC = (int *) calloc(sizeof(int),1);
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
    AscizRow = (asciz_row *)calloc(sizeof(asciz_row),1);
    if(AscizRow == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
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
int init_asciz_string(){
    AscizRow->string = (char*) calloc(sizeof(char),AscizRow->size);
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
    dataNode * pt;
    for(i=0;AscizRow->string[i];i++){
        pt = init_data_node(AscizRow->string[i]);
        if(pt == NULL_SIGN){
            program_error(ERROR_ALLOCATING_MEMORY);
            return ERROR;
        }
        add_data_node(pt);
    }
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
        add_data_node(newNode);
    }
    /* free data row */
    free(DataRow->array);
    free(DataRow);
}

/*
 * init data row struct for data input row
*/
int init_data_row(){
    DataRow = (data_row *)calloc(sizeof(data_row),1);
    if(DataRow == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    DataRow->array = (long *)calloc(sizeof(long),1);
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
    status = init_data_row();
    if(status== ERROR){
        return ERROR;
    }
    while (data[i] != '\n' && data[i] != '\0' && data[i] != 13 && data[i] != '\r')
    {
        /* backspace skip it*/
        if(data[i] == ' ' || data[i] == '\t'){
            i++;
            continue;
        }
        /* end of number -> insert to long array */
        if(data[i] == ','){
            /* convert to long number before insert */
            DataRow->array[DataRow->size-1] = strtol(DataRow->input_num,&ptr,10);
            status = realloc_data_row();
            if(status == ERROR){
                return ERROR;
            }
            zero_input_num();
        }else{ /* insert number to array */
            DataRow->input_num[DataRow->input_num_size] = data[i];
            DataRow->input_num_size ++;
            /* the number is bigger than 2^32 */
            if(DataRow->input_num_size > INPUT_NUM){
                add_error(ERROR_MAX_DATA,*RowNumber);
                return ERROR;
            }
        }
        i++;
    }
    /* more number to insert to array */
    if(DataRow->input_num[0] != '\0'){
        DataRow->array[DataRow->size-1] = strtol(DataRow->input_num,&ptr,10);
    }
    /* free input num  char array helper  TODO*/
    /*free(DataRow->input_num);*/
}

/*
 * copy the input data of string to AscizRow structure
 */
void copy_asciz_string(char * data){
    strncpy(AscizRow->string,data,AscizRow->size);
}

/*
 * update string input size to struct
 */
void update_asciz_row_size(int size){
    AscizRow->size = size;
}

/*
 * init data node for linked list for data input
 */
dataNode * init_data_node(long data)
{
    dataNode * pt;
    pt = (dataNode *)calloc(sizeof(dataNode),1);
    if(pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL_SIGN;
    }
    switch (*row_data_type) {
        /* byte size */
        case DB:
        case ASCIZ: /* TODO check asciz again*/
            pt->data_u.db = (char)data;

            break;
        /* half word */
        case DH:
            pt->data_u.data_dh.dh = (int)data;
            break;
        /* whole word */
        case DW:
            pt->data_u.data_dw.dw = data;
            break;

    }
    pt->address = *DC++;
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

/* TODO only test remove end*/
void test_binary_dec(){
    unsigned i;
    dataNode * cur = DataNodes;
    while(cur != NULL) {
/*                    for (i = 1 << 31; i > 0; i = i / 2)
                        (DataNodes->db & i) ? printf("1") : printf("0");*/
        printf("%d", cur->data_u.db);
        cur = cur->next;
        putchar('\n');
    }
}


