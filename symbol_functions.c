#include "symbol_functions.h"

 /* symbol variables */
symbolNode * SymbolNodes;

/*
 * save label to struct labels
 */
void save_label(char *data, int size){
    char * symbol;
    symbolNode * symbol_pt;
    symbol = init_symbol_string(size);
    if(row_has_error()){ /* we have error don't continue */
        return;
    }
    strncpy(symbol,data,size);
    symbol_pt = init_symbol_node(symbol);
    add_symbol_node(symbol_pt);
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
symbolNode * init_symbol_node(char* label)
{
    symbolNode * pt;
    pt = (symbolNode *)calloc(sizeof(symbolNode),1);
    if(pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    pt->symbol = label;
    pt->address = *DC++; /* TODO address counter*/
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