#ifndef MAMAN14_INSTRUCTIONS_PARSER_H
#define MAMAN14_INSTRUCTIONS_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Instructions_functions.h"
#include "shared_data.h"

/*
 * process the data of the instruction row and check how many arguments
 * that match to instruction Action with the type
 */
int process_instruction(char * data,int iteration);



#endif
