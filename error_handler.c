#include "error_handler.h"

/* errors variables */
errorNode * ErrorNodes;
/* flag for error in the current row */
int * RowHasError; /* TODO Init and zero each row*/
extern char * FileName;

/* private error handler variables */
int errors_count;

/*
 * determines if the current row has error
 */
int row_has_error(){
    return *RowHasError;
}

/*
 * init row has error int number
 */
int init_row_has_error(){
    RowHasError = (int *)calloc(sizeof(int), 1);
    if (RowHasError == NULL){
        add_error(ERROR_ALLOCATING_MEMORY,NO_LINE_NUMBER);
        return ERROR;
    }
    return OK;
}

/*
 * reset row has error after end the current row
 */
void reset_row_has_error(){
    *RowHasError = 0;
}

/*
 * init error counter to zero
 */
void init_errors_data(){
    errors_count = 0;
}

/*
 * get number of errors
 */
int get_errors_count(){
    return errors_count;
}


/*
 * add error message to linked list
 */
void add_error(char * error_message, int line_number){
    errorNode * newNode;
    newNode = init_error_node(error_message, line_number);
    if(newNode != NULL){
        add_error_node(newNode);
        errors_count ++;
        return;
    }
    /* TODO add error*/
}

/*
 * init error node for linked list for error
 */
errorNode * init_error_node(char * error_message, int line_number)
{
    errorNode * node;
    node = (errorNode *)calloc(sizeof(errorNode), 1);
    if(node == NULL){
        /* TODO error allocation*/
    }
    node->next = NULL;
    node->error_message = error_message;
    node->file_name = FileName;
    return node;
}

/*
 * adds the new node to linked list at the end
 */
errorNode * add_error_node(errorNode *newNode)
{
    errorNode * cur_node;
    if(ErrorNodes == NULL){ /* this is the first node in the data nodes */
        ErrorNodes = newNode;
    }else{
        cur_node = ErrorNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of data nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = newNode;
    }
}

/*
 * program error -> prints immediately
 */
void program_error(char * message){
    fprintf(stderr,"%s\n",message);
}