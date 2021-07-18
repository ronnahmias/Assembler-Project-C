#ifndef MAMAN14_DATA_FUNCTIONS_H
#define MAMAN14_DATA_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "constants.h"
#include "string.h"
#include "shared_data.h"

extern int *row_data_type;

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

/*
 * find the data type of the input row from array
 */
void search_data_type(char * input);

/*
 * init data node for linked list for data input
 */
dataNode * init_data_node(long data);

/*
 * adds the new node to linked list at the end
 */
dataNode * add_data_node(dataNode *newNode);

/* asciz data functions */

/*
 * init struct helper for string input row
 */
void init_asciz_row();

/*
 * free struct helper for string input
 */
void free_asciz_row();

/*
 * init char array in struct of string input row
 */
void init_asciz_string();

/*
 * add asciz array of chars to linked list data nodes
 */
void insert_asciz_row();

/*
 * copy the input data of string to AscizRow structure
 */
void copy_asciz_string(char * data);

/*
 * update string input size to struct
 */
void update_asciz_row_size(int size);

/*
 * insert from long array of numbers to data nodes
 * after -> connect to linked data list
 */
void insert_data_row();

/*
 * realloc array long of the row input data
*/
void realloc_data_row();

/*
 * init data row struct for data input row
*/
void init_data_row();

/*
 * zero all input num for the next number in the input
 */
void zero_input_num();

/*
 * convert data row numbers (db,dw,dh) to long array before insert to linked list
 */
void convert_data_to_array(char * data);


#endif
