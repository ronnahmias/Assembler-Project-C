#include "symbol_functions.h"

 /* symbol variables */
symbolNode * SymbolNodes;

/*
 * finds the label in the list and return the address
 */
int find_label(char * label){
    symbolNode * curNode;
    curNode = SymbolNodes; /* init cur to linked list head */
    while(curNode != NULL){
        if(strcmp(curNode->symbol, label)){ /* we have label same */
            return curNode->address;
        }
        curNode = curNode->next;
    }
    return ERROR;
}

/*
 * checks if label has already in the linked list
 */
int check_label_exists(char * label){
    symbolNode * curNode;
    curNode = SymbolNodes; /* init cur to linked list head */
    while(curNode != NULL){
        if(!strcmp(curNode->symbol, label)){ /* we have label same -> error*/
            add_error(ERROR_LABEL_EXISTS,*RowNumber);
            return ERROR;
        }
        curNode = curNode->next;
    }
    return OK;
}

/*
 * init data node for linked list for symbol
 */
symbolNode * init_symbol_node(char* label,int label_type)
{
    symbolNode * pt;
    pt = (symbolNode *)calloc(sizeof(symbolNode),1);
    if(pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL_SIGN;
    }
    pt->symbol = label;
    pt->symbol_type = label_type;
    /* address is base on type */
    if(label_type == CODE){
        pt->address = *IC;
    }else{
        if(label_type == DATA){
            pt->address = *DC;
        }
    }
    return pt;
}

/*
 * save label to struct labels
 */
int save_label(char * label, int label_type){
    int status;
    symbolNode * symbol_pt;
    if(check_label_exists(label) == ERROR){ /* check duplicate label */
        return ERROR;
    }
    symbol_pt = init_symbol_node(label,label_type);
    if(symbol_pt == NULL_SIGN){ /* error allocating dont continue */
        return ERROR;
    }
    add_symbol_node(symbol_pt);
    return OK;
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