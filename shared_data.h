#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

#include "constants.h"
#include "error_handler.h"
#include <limits.h>

/* for long variable TODO remove
#define TARGET_MAX 2147483647L
#if   SCHAR_MAX >= TARGET_MAX
typedef signed char int32;
#elif SHORT_MAX >= TARGET_MAX
typedef short int32;
#elif INT_MAX   >= TARGET_MAX
typedef int int32;
#else
typedef long int32;
#endif*/

#undef TARGET_MAX
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
