#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

#include "constants.h"
#include "error_handler.h"

/* TODO remove */
/*typedef struct dataNode{
    int address;
    struct dataNode *next;
    union {
        char db;
        struct {
            int32 dw:32;
        }data_dw;
        struct {
            int dh:16;
        }data_dh;
    }data_u;
}dataNode;*/

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


#endif
