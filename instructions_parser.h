#ifndef MAMAN14_INSTRUCTIONS_PARSER_H
#define MAMAN14_INSTRUCTIONS_PARSER_H

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

#endif
