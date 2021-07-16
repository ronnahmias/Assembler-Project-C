#ifndef MAMAN14_DATA_FUNCTIONS_H
#define MAMAN14_DATA_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "constants.h"
#include "string.h"
#include "shared_data.h"

extern dataNode * DataNodes;
extern int * row_data_type;
extern asciz_row * AscizRow;

enum data_enum
{
    DB = 0,
    DH,
    DW,
    ASCIZ,
    ENTRY,
    EXTERN
};

void init_data();
void search_data_type(char * input);
dataNode * init_data_node(int data);
dataNode * add_data_node(dataNode *newNode);
void init_asciz_row();
void free_asciz_row();
void init_asciz_string();
void insert_asciz_row();


#endif //MAMAN14_DATA_FUNCTIONS_H
