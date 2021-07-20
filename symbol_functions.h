#ifndef MAMAN14_SYMBOL_FUNCTIONS_H
#define MAMAN14_SYMBOL_FUNCTIONS_H
#include "stdio.h"
#include "stdlib.h"
#include "constants.h"
#include "error_handler.h"

extern int * RowNumber;

enum symbol_type_enum
{
    CODE = 0,
    DATA,
    EXTERNAL
};

enum symbol_entry_enum
{
    YES = 0,
    NO
};

typedef struct symbolNode{
    int address;
    char * symbol;
    int symbol_type;
    int symbol_entry;
    struct symbolNode *next;

}symbolNode;

#endif
