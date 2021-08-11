#ifndef MAMAN14_ERROR_HANDLER_H
#define MAMAN14_ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
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
 * program error -> prints immediately
 */
void program_error(char * message);

/*
 * print errors from error linked list
 */
void print_errors();

/* Error Messages */
#define ERROR_ALLOCATING_MEMORY "Error allocating memory"
#define ERROR_NO_DATA_TYPE "Error data type not found"
#define ERROR_MISSING_FILES "Error missing files"
#define ERROR_OPEN_FILE "Error while open the file"
#define ERROR_EXT_ERROR "Error input file extension not compatible"
#define ERROR_LABEL_OVERSIZE "Error label more than 31 characters"
#define ERROR_LABEL_SYNTAX "Error label syntax not correct"
#define ERROR_LABEL_EXISTS "Error label already exists"
#define ERROR_INSTRUCTION_NOT_FOUND "Error Instruction Not found"
#define ERROR_ARGUMENTS_ERROR "Error syntax arguments in line"
#define ERROR_IMMED_SYNTAX "Error immed value need to be integer type"
#define ERROR_REGISTER_RANGE "Error register not in range"
#define ERROR_IMMED_RANGE "Error immed not in range"
#define ERROR_MAX_DATA "Error max data long"
#define ERROR_ASCIZ_SYNTAX "Error data row not in the correct syntax"
#define ERROR_ENTRY_ERROR "Error entry label not found in label list"
#define ERROR_OPEN_FILE_EXPORT "Error while open the file for export"
#endif
