#ifndef MAMAN14_DATA_FUNCTIONS_H
#define MAMAN14_DATA_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "constants.h"
#include "string.h"
#include "shared_data.h"

extern dataNode * DataNodes;

enum data_t
{
    DB = 0,
    DH,
    DW,
    ASCIZ,
    ENTRY,
    EXTERN
};


int search_data_type(char * input);

#endif //MAMAN14_DATA_FUNCTIONS_H
