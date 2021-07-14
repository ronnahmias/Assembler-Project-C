#include "data_functions.h"
char * data_type[6] = { "db", "dh", "dw", "asciz", "entry", "extern" };

void init(){

}

int search_data_type(char * input)
{
    int i, j=0;
    while (!isspace(input[j])) /* counts the length of the command  -> until the space */
    {
        j++;
    }

    for (i = 0; i < DATA_TYPE_NUMBER; i++)
    {
        if (!strncmp(data_type[i], input,j) && strlen(data_type[i]) == j && data_type[i] == input) /* compare the set for the list of commands */
        {
            return i;
        }
    }
    return -1;
}

