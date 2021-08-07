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
    NO = 0,
    YES
};

typedef struct symbolNode{
    signed long address;
    char symbol[LABEL_MAX_SIZE];
    int symbol_type;
    int symbol_entry;
    struct symbolNode *next;
}symbolNode;

typedef struct entryNode{
    signed long address;
    char symbol[LABEL_MAX_SIZE];
    struct entryNode *next;
}entryNode;

typedef struct externNode{
    signed long address;
    char symbol[LABEL_MAX_SIZE];
    struct externNode *next;
}externNode;

/*
 * add extern label to extern list for future use
 */
int add_extern_node(char * label, signed long address);

/*
 * add entry label to entry list for future use
 */
int add_entry_node(char * label);

/*
 * update entry labels addresses for ent export files
 */
int check_entry_labels();

/*
 * save label to struct labels
 */
int save_label(char * label, int label_type);

/*
 * finds the label in the list and return the address
 */
signed long find_label(char * label, int* external);
/*
 * after first run over the rows file
 * update the data address after the IC
 */
int update_symbol_data_addresses();

/*
 * return the next head node for export file entry
 */
entryNode * get_next_entry_node();

/*
 * checks if there is entry nodes for export ent file
 */
int entry_nodes_exists();

/*
 * return the next head node for export file extern
 */
externNode * get_next_extern_node();

/*
 * checks if there is extern node for export ext file
 */
int extern_nodes_exists();

/*
 * free symbol linked list
 */
void free_symbol_node();

#endif
