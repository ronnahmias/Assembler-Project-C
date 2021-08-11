#ifndef MAMAN14_CONSTANTS_H
#define MAMAN14_CONSTANTS_H

/* max extension len */
#define EXT_LEN 4
#define EXT_INPUT_FILES ".as"
#define FILE_NAME_LEN 20

#define TRUE 1
#define FALSE 0
#define OK 1

/* max row input row */
#define ROW_LINE 81


/*
 * data image constants
 */

 /* number of data types option (db,dw,dw,asciz,entry,extern)*/
#define DATA_TYPE_NUMBER 6
#define INST_R_NUMBER 6
#define INST_J_NUMBER 4
#define INST_I_NUMBER 15

#define BYTE_SIZE 4
#define ADDRESS_INIT 100

#define NO_INSTRUCTION_FOUND -1
#define ERROR -1
#define NO_DATA_TYPE -1
#define COMMENT_ROW -5
#define NOT_FOUND -2

#define INPUT_NUM 10

#define DOT "."

#define LABEL_MAX_SIZE 31
#define INSTRUCTION_MAX_SIZE 4 /* the longest instruction word */
#define FIRST_INDEX 0
#define THREE_ARGS 3
#define TWO_ARGS 2
#define NULL_SIGN '\0'
#define NEW_LINE '\n'
#define BACK_R '\r'
#define UNUSED 0

 /* const sizes */
#define MAX_REGISTER 31
#define MIN_REGISTER 0
#define MAX_IMMED 32767
#define MIN_IMMED -32768
#define IMMED_DIGITS 6

 /* instructions bits range */
#define OPCODE 26
#define RS 21
#define RT 16
#define RD_R 11
#define FUNCT_R 6

 /* exporting consts*/
#define TWO_BYTES 0xFF
#define SHIFT_ONE 8
#define SHIFT_TWO 16
#define SHIFT_THREE 24
#define CODE_PRINT_LEN 18

 /* bits data size */
#define ONE_BYTE_SIZE 8
#define HALF_WORD_SIZE 16
#define WHOLE_WORD_SIZE 32

#endif
