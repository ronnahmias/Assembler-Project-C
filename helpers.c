#include "helpers.h"

void read_by_line(FILE *cur_file, int iteration_num)
{
    char charr =0;
    char data[ROW_LINE];
    //fscanf(cur_file, "%c", &data);
    while(fgets(data, sizeof(data),cur_file))
    {
        process_input(data);
    }
}

void process_input(char *input_row)
{
    printf("%s", input_row);
    input_row = delete_spaces(input_row); /* delete white spaces if have */
    //if(has_label(input_row)){ /* check if it has label first */
        //TODO save label
        // strtok to label and remove spaces
    //}
    if(is_dot(*input_row)){ /* check if is data row */
        input_row = input_row + 1; /* skip the dot */
        input_row = split_word(input_row);
        search_data_type(input_row);
        return;
    }


}

int is_dot(char ch){
    int res;
    return (ch==46) ?  1 : 0;
}

char * split_word(char* input) /* get the next word */
{
    char * comma=" ",*word;
    word = strtok(input,comma);
    return word;
}

char * delete_spaces(char* input) /* delete space */
{
    int i = 0;
    while (input[i] != 0 && isspace(input[i]))
    {
        i++;
    }
    return input + i;
}