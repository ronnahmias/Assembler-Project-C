#ifndef MAMAN14_DATA_FUNCTIONS_H
#define MAMAN14_DATA_FUNCTIONS_H
#include <stdlib.h>
#include "Instructions_functions.h"
#include <ctype.h>

/* extern variables */
extern int *RowNumber;
extern int *row_data_type;
extern signed long *DC;

typedef struct dataNode{
    int address;
    struct dataNode *next;
    int datatype;
    char * db;
    int * dh;
    signed long *dw;
}dataNode;


typedef struct {
    int size;
    char * string;
}asciz_row;

typedef struct {
    int size;
    long * array;
    int input_num_size;
    char input_num[INPUT_NUM];
}data_row;

typedef enum{
    DB = 0,
    DH,
    DW,
    ASCIZ,
    ENTRY,
    EXTERN
}data_enum;

/*
 * init data counter
 */
int init_dc();

/*
 * free data counter
 */
void free_dc();

/*
 * init required variables
 */
int init_data();

/*
 * reset data variables
 */
void reset_data();

/*
 * free data variables
 */
void free_data();

/*
 * find the data type of the input row from array
 */
void search_data_type(char * input);

/* asciz data functions */

/*
 * init struct helper for string input row
 */
int init_asciz_row();

/*
 * free struct helper for string input
 */
void free_asciz_row();

/*
 * init char array in struct of string input row
 */
int init_asciz_string();

/*
 * add asciz array of chars to linked list data nodes
 */
int insert_asciz_row();

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
int insert_data_row();

/*
 * convert data row numbers (db,dw,dh) to long array before insert to linked list
 */
int convert_data_to_array(char * data);

/*
 * update addresses in data list add the current IC
 */
int update_data_list_addresses();

/*
 * get the data node of next node from head in linked list
 */
dataNode * get_next_node_data();

/*
 * checks if there is data nodes for export
 */
int data_exists();

/*
 * free data linked list
 */
void free_data_nodes();

#endif
