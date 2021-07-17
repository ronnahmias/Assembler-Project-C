#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

#include "constants.h"

typedef struct dataNode{
    int address;
    struct dataNode *next;
    union {
        char db;
        struct {
            long dw:32;
        };
        struct {
            int dh:16;
        };
    };
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


#endif //MAMAN14_SHARED_DATA_H
