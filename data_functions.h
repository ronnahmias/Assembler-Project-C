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
extern data_row * DataRow;

enum data_enum
{
    DB = 0,
    DH,
    DW,
    ASCIZ,
    ENTRY,
    EXTERN
};

/*
 * init required variables
 */
void init_data();


void search_data_type(char * input);
dataNode * init_data_node(long data);
dataNode * add_data_node(dataNode *newNode);

/* asciz data functions */
/*
 * init struct helper for string input row
 */
void init_asciz_row();
void free_asciz_row();
void init_asciz_string();
void insert_asciz_row();

void insert_data_row();
void realloc_data_row();
void init_data_row();
void zero_input_num();

/*
 * parser (db,dh,dw) function
 */
void convert_data_to_array(char * data);


#endif //MAMAN14_DATA_FUNCTIONS_H
