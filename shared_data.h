#ifndef MAMAN14_SHARED_DATA_H
#define MAMAN14_SHARED_DATA_H

#include "constants.h"
#include "error_handler.h"

typedef struct dataNode{
    int address;
    struct dataNode *next;
    union {
        char db;
        struct {
            long dw:32;
        }data_dw;
        struct {
            int dh:16;
        }data_dh;
    }data_u;
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

typedef union NAME{
    unsigned int bits32:32;
    struct{
        unsigned int bitsNum:32;
    }bits31;
    struct{
        unsigned int funct:5;
        unsigned int rt:2;
        unsigned int rs:3;
        unsigned int reg:2;
        unsigned int opcode:6;
    }bitsDetailsTypeX;
    struct{
        unsigned int funct:5;
        unsigned int rt:2;
        unsigned int rs:3;
        unsigned int reg:2;
        unsigned int opcode:6;
    }bitsDetailsTypeR;
    struct{
        unsigned int funct:5;
        unsigned int rt:2;
        unsigned int rs:3;
        unsigned int reg:2;
        unsigned int opcode:6;
    }bitsDetailsTypeE;

}binaryCode;


#endif
