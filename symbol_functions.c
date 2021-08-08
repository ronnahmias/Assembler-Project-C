#include "symbol_functions.h"

 /* symbol variables */
symbolNode * SymbolNodes;
entryNode * EntryNodes;
externNode * ExternNodes;

/* private functions */
/*
 * adds the new node to linked list at the end
 */
symbolNode * add_symbol_node(symbolNode **newNode);
/* end - private functions */

/*
 * add extern label to extern list for future use
 */
int add_extern_node(char * label, signed long address){
    externNode * ext_pt,*temp_pt;
    ext_pt = (externNode *)calloc(1, sizeof(externNode));
    if(ext_pt == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return ERROR;
    }
    strncpy(ext_pt->symbol, label, sizeof(ext_pt->symbol) - 1);
    ext_pt->address = address;
    if(ExternNodes == NULL){ /* this is the first node in the extern nodes */
        ExternNodes = ext_pt;
    }else{
        temp_pt = ExternNodes;
        while(temp_pt->next){ /* insert to tail of the linked list of extern nodes */
            temp_pt = temp_pt->next;
        }
        temp_pt->next = ext_pt;
    }
    return OK;
}

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
 * update entry labels addresses for ent export files
 */
int check_entry_labels(){
    entryNode * cur_entry;
    symbolNode * cur_symbol;
    int flag = 0;
    cur_entry = EntryNodes;
    while(cur_entry){ /* loop on entry list */
        cur_symbol = SymbolNodes;
        while(cur_symbol){ /* loop on symbol list */
            if(!strcmp(cur_entry->symbol,cur_symbol->symbol)){ /* found symbol in the symbol list */
                cur_entry->address = cur_symbol->address; /* update address of entry symbol */
                cur_symbol->symbol_entry = YES; /* update in symbol list that is entry also */
                flag = 1;
                break;
            }
            cur_symbol = cur_symbol->next;
        }
        if(!flag){
            program_error(ERROR_ENTRY_ERROR);
            return ERROR;
        }
        flag = 0;
        cur_entry = cur_entry->next;
    }
    return OK;
}

/*
 * finds the label in the list and return the address
 */
signed long find_label(char * label, int* external){
    symbolNode * node;
    node = SymbolNodes; /* init cur to linked list head */
    while(node)
    {
        if(!strcmp(node->symbol, label)) {/* we have label same*/
            if(node->symbol_type == EXTERNAL){
                *external = TRUE;
            }
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
    if(check_label_exists(label) == ERROR){
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

/*
 * return the next head node for export file entry
 */
entryNode * get_next_entry_node(){
    entryNode * node;
    if(EntryNodes == NULL){
        return NULL;
    }
    node = EntryNodes;
    EntryNodes = EntryNodes->next;
    return node;
}

/*
 * checks if there is entry nodes for export ent file
 */
int entry_nodes_exists(){
    if(EntryNodes == NULL){
        return FALSE;
    }
    return TRUE;
}

/*
 * return the next head node for export file extern
 */
externNode * get_next_extern_node(){
    externNode * node;
    if(ExternNodes == NULL){
        return NULL;
    }
    node = ExternNodes;
    ExternNodes = ExternNodes->next;
    return node;
}

/*
 * checks if there is extern node for export ext file
 */
int extern_nodes_exists(){
    if(ExternNodes == NULL){
        return FALSE;
    }
    return TRUE;
}

/*
 * free symbol linked list
 */
void free_symbol_node(){
    symbolNode * node;
    if(SymbolNodes == NULL){
        return;
    }

    while(SymbolNodes){
        node = SymbolNodes;
        SymbolNodes = SymbolNodes->next;
        free(node);
    }
}