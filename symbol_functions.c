#include "symbol_functions.h"

 /* symbol variables */
symbolNode * SymbolNodes;

void save_label(char *data, int size){
    char * symbol;
    if(size > LABEL_MAX_SIZE){
        add_error(ERROR_LABEL_OVERSIZE,*RowNumber);
    }
    symbol = init_symbol_string(size);
    if(row_has_error()){ /* we have error don't continue */
        return;
    }

    /* TODO continue */
}
 /*
  * init char string to symbol
  */
char * init_symbol_string(int size){
    char * symbol;
    symbol = (char *)calloc(sizeof(char),size);
    if(symbol == NULL){
        add_error(ERROR_ALLOCATING_MEMORY,*RowNumber);
    }
    return symbol;
}

/*
 * init data node for linked list for symbol
 */
symbolNode * init_symbol_node(long data)
{
    symbolNode * pt;
    pt = (symbolNode *)calloc(sizeof(symbolNode),1);
    if(pt == NULL){
        /* TODO error allocation*/
    }

    pt->address = 0; /* TODO address counter*/
    return pt;
}

/*
 * adds the new node to linked list at the end
 */
symbolNode * add_symbol_node(symbolNode *newNode)
{
    symbolNode * cur_node;
    if(SymbolNodes == NULL){ /* this is the first node in the symbol nodes */
        SymbolNodes = newNode;
    }else{
        cur_node = SymbolNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of symbol nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = newNode;
    }
}