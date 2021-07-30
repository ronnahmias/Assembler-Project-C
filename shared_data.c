#include "shared_data.h"

/* current file name */
char * FileName;

/* data type definition */
int * row_data_type;

/* row number */
int * RowNumber;

/* instruction variables */
int * Inst_Type;
int * Inst_Action;
unsigned int * help_argument_array;
signed int * immed;

/* instruction, data counters */
signed long * IC;
signed long * DC;