#ifndef MAMAN14_SYMBOL_FUNCTIONS_H
#define MAMAN14_SYMBOL_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "constants.h"
#include "error_handler.h"

extern int * RowNumber;
extern signed long * DC;
extern signed long * IC;

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
    signed long address;
    char symbol[LABEL_MAX_SIZE];
    int symbol_type;
    int symbol_entry;
    struct symbolNode *next;
}symbolNode;

typedef struct entryNode{
    char symbol[LABEL_MAX_SIZE];
    struct entryNode *next;
}entryNode;

/*
 * add entry label to entry list for future use
 */
int add_entry_node(char * label);

/*
 * save label to struct labels
 */
int save_label(char * label, int label_type);

/*
 * adds the new node to linked list at the end
 */
symbolNode * add_symbol_node(symbolNode **newNode);

/*
 * finds the label in the list and return the address
 */
signed long find_label(char *label);

/*
 * after first run over the rows file
 * update the data address after the IC
 */
int update_symbol_data_addresses();


#endif
