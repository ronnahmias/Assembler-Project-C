#ifndef MAMAN14_CONSTANTS_H
#define MAMAN14_CONSTANTS_H

/* max extension len */
#define EXT_LEN 4
#define EXT_INPUT_FILES ".as"

#define TRUE 1
#define FALSE 0
#define OK 1

/* max row input row */
#define ROW_LINE 81

/* iteration defines */
#define FIRST_ITER 1
#define SECOND_ITER 2

/*
 * data image constants
 */

 /* number of data types option (db,dw,dw,asciz,entry,extern)*/
#define DATA_TYPE_NUMBER 6
#define INST_R_NUMBER 6
#define INST_J_NUMBER 4
#define INST_I_NUMBER 15

#define NO_INSTRUCTION_FOUND -1
#define ERROR -1
#define NO_DATA_TYPE -1
#define NO_LINE_NUMBER -1

#define INPUT_NUM 10

#define DOT "."

#define LABEL_MAX_SIZE 31
#define INSTRUCTION_MAX_SIZE 4 /* the longest instruction word */
#define FIRST_INDEX 0
#define THREE_ARGS 3
#define TWO_ARGS 2
#define NULL_SIGN '\0'

#endif
