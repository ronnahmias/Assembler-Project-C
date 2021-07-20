#ifndef MAMAN14_ERROR_HANDLER_H
#define MAMAN14_ERROR_HANDLER_H

#include "stdio.h"
#include "stdlib.h"
#include "shared_data.h"
#include "constants.h"

typedef struct errorNode{
    int line_number;
    char * error_message;
    char * file_name;
    struct errorNode *next;
}errorNode;

/*
 * init error counter to zero
 */
void init_errors_data();

/*
 * get number of errors
 */
int get_errors_count();

/*
 * add error message to linked list
 */
void add_error(char * error_message, int line_number);

/*
 * init error node for linked list for error
 */
errorNode * init_error_node(char * error_message, int line_number);

/*
 * adds the new node to linked list at the end
 */
errorNode * add_error_node(errorNode *newNode);

/*
 * program error -> prints immediately
 */
void program_error(char * message);

/* Error Messages */
#define ERROR_ALLOCATING_MEMORY "Error allocating memory"
#define ERROR_NO_DATA_TYPE "Error data type not found"
#define ERROR_MISSING_FILES "Error missing files"
#define ERROR_EXT_ERROR "Error input file extension not compatible"

#endif
