#include "error_handler.h"

/* errors variables */
errorNode * ErrorNodes;
extern char * FileName;
/* private error handler variables */
int errors_count;

/* private functions */
/*
 * init error node for linked list for error
 */
errorNode * init_error_node(char * error_message, int line_number);

/*
 * adds the new node to linked list at the end
 */
errorNode * add_error_node(errorNode *newNode);

/* end - private functions */

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
}

/*
 * init error node for linked list for error
 */
errorNode * init_error_node(char * error_message, int line_number)
{
    errorNode * node;
    node = (errorNode *)calloc(1,sizeof(errorNode));
    if(node == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    node->next = NULL;
    node->error_message = error_message;
    node->file_name = FileName;
    node->line_number = line_number;
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
    return NULL;
}

/*
 * program error -> prints immediately
 */
void program_error(char * message){
    fprintf(stderr,"%s\n",message);
}

/*
 * print errors from error linked list
 */
void print_errors(){
    errorNode * node;
    if(ErrorNodes == NULL){ /* this is the first node in the data nodes */
        return;
    }else{
        fprintf(stderr,"Errors found in file %s \n",FileName);
        while(ErrorNodes){
            node = ErrorNodes;
            fprintf(stderr,"%s in line number %d\n",node->error_message,node->line_number);
            ErrorNodes = ErrorNodes->next;
            if(node != NULL){
                free(node);
                node = NULL;
            }

        }



    }
}