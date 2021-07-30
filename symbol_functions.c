#include "symbol_functions.h"

 /* symbol variables */
symbolNode * SymbolNodes;
entryNode * EntryNodes;

/*
 * add entry label to entry list for future use
 */
int add_entry_node(char * label){
    entryNode * ent_pt,*temp_pt;
    ent_pt = (entryNode *)calloc(1,sizeof(entryNode));
    if(ent_pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    strncpy(ent_pt->symbol,label,sizeof(ent_pt->symbol)-1);
    if(EntryNodes == NULL){ /* this is the first node in the entry nodes */
        EntryNodes = ent_pt;
    }else{
        temp_pt = EntryNodes;
        while(temp_pt->next){ /* insert to tail of the linked list of entry nodes */
            temp_pt = temp_pt->next;
        }
        temp_pt->next = ent_pt;
    }
    return OK;
}

/*
 * finds the label in the list and return the address
 */
signed long find_label(char * label){
    symbolNode * node;
    node = SymbolNodes; /* init cur to linked list head */
    while(node)
    {
        if(!strcmp(node->symbol, label)) {/* we have label same*/
            return node->address;
        }
        node = node->next;
    }
    return NOT_FOUND;
}

/*
 * checks if label has already in the linked list
 */
int check_label_exists(char * label){
    symbolNode * node;
    node = SymbolNodes; /* init cur to linked list head */
    while (node) {
        if (!strcmp(node->symbol, label)) { /* we have label same -> error*/
            add_error(ERROR_LABEL_EXISTS, *RowNumber);
            return ERROR;
        }
        node = node->next;
    }
    return OK;

}

/*
 * init data node for linked list for symbol
 */
symbolNode * init_symbol_node(char *label,int label_type)
{
    symbolNode * pt;
    pt = (symbolNode *)calloc(1,sizeof(symbolNode));
    if(pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL_SIGN;
    }
    strncpy(pt->symbol,label,sizeof(pt->symbol)-1);
    pt->symbol_type = label_type;
    /* address is base on type */
    switch (label_type) {
        case CODE:
            pt->address = *IC;
            break;
        case DATA:
            pt->address = *DC;
            break;
        case EXTERNAL:
            pt->address = FALSE;
            break;
    }
    return pt;
}

/*
 * save label to struct labels
 */
int save_label(char label[LABEL_MAX_SIZE], int label_type){
    int status;
    symbolNode * symbol_pt;
    if(check_label_exists(label) == ERROR){ /* TODO check duplicate label*/
        return ERROR;
    }
    symbol_pt = init_symbol_node(label,label_type);
    if(symbol_pt == NULL_SIGN){ /* error allocating dont continue */
        return ERROR;
    }
    add_symbol_node(&symbol_pt);
    return OK;
}

/*
 * adds the new node to linked list at the end
 */
symbolNode * add_symbol_node(symbolNode **newNode){
    symbolNode * cur_node;
    if(SymbolNodes == NULL){ /* this is the first node in the symbol nodes */
        SymbolNodes = *newNode;
    }else{
        cur_node = SymbolNodes;
        while(cur_node->next != NULL){ /* insert to tail of the linked list of symbol nodes */
            cur_node = cur_node->next;
        }
        cur_node->next = *newNode;
    }
}

/*
 * after first run over the rows file
 * update the data address after the IC
 */
int update_symbol_data_addresses(){
    symbolNode * temp_node;
    temp_node = SymbolNodes; /* init temp node to linked list head */
    while (temp_node) {
        if (temp_node->symbol_type == DATA) { /* symbol type data -> update the address */
            temp_node->address += *IC; /* add the IC to address */
        }
        temp_node = temp_node->next;
    }
    return OK;

}