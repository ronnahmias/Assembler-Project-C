#ifndef MAMAN14_SYMBOL_FUNCTIONS_H
#define MAMAN14_SYMBOL_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "constants.h"
#include "error_handler.h"

extern int * RowNumber;
extern int * DC;

enum symbol_type_enum
{
    CODE = 0,
    DATA,
    EXTERNAL
};

enum symbol_entry_enum
{
    YES = 0,
    NO
};

typedef struct symbolNode{
    int address;
    char * symbol;
    int symbol_type;
    int symbol_entry;
    struct symbolNode *next;

}symbolNode;

/*
 * init char string to symbol
 */
char * init_symbol_string(int size);

/*
 * save label to struct labels
 */
int save_label(char *data, int size);

/*
 * init data node for linked list for symbol
 */
symbolNode * init_symbol_node(char* label);

/*
 * adds the new node to linked list at the end
 */
symbolNode * add_symbol_node(symbolNode *newNode);

#endif
