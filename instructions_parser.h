#ifndef MAMAN14_INSTRUCTIONS_PARSER_H
#define MAMAN14_INSTRUCTIONS_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Instructions_functions.h"
#include "shared_data.h"
#include "helpers.h"

/*
 * process the data of the instruction row and check how many arguments
 * that match to instruction Action with the type
 */
int process_instruction(char * data);

/*
 * extract label from line input
 */
int get_label(char * data, char *label_dest);

/*
 * turn on bits according to range (index of start)
 */
signed long add_bits(signed long before, unsigned char num, unsigned char range);



#endif
