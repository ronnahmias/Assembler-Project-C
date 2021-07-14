#ifndef MAMAN14_DATA_FUNCTIONS_H
#define MAMAN14_DATA_FUNCTIONS_H
#include "stdio.h"
#include "ctype.h"
#include "constants.h"
#include "string.h"

enum data_t
{
    DB = 0,
    DH,
    DW,
    ASCIZ,
    ENTRY,
    EXTERN
};

struct dataNode {
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
};

int search_data_type(char * input);

#endif //MAMAN14_DATA_FUNCTIONS_H
