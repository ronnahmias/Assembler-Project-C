#include "export_handler.h"
/* prototypes functions */
/*
 * print instructions code to ob file
 */
int print_code(FILE ** File);

/*
 * export ob file with
 * instructions code and
 * data image code
 */
int export_ob_file();

/*
 * print number of the instructions and data code lines
 */
int print_num_rows(FILE **File);

/* end - prototypes functions */


/*
 * function that handler all export files
 */
int export_files(){
    export_ob_file();
    /* TODO ent ext files*/
}

/*
 * export ob file with
 * instructions code and
 * data image code
 */
int export_ob_file(){
    char file_name[20] = {0};
    FILE * File_Handler;

    /* generate ob file name */
    sprintf(file_name, "%s.ob", strtok(FileName,DOT));
    File_Handler = fopen(file_name, "w");

    if(File_Handler == NULL){
        program_error(ERROR_OPEN_FILE_EXPORT);
        return ERROR;
    }

    print_num_rows(&File_Handler);
    print_code(&File_Handler);
}

/*
 * print number of the instructions and data code lines
 */
int print_num_rows(FILE **File){
    char formatted_data[18];
    sprintf(formatted_data, "     %02ld %02ld\n", *IC - ADDRESS_INIT, *DC);
    fprintf(*File, "%s", formatted_data);
    return OK;
}

/*
 * print instructions code to ob file
 */
int print_code(FILE ** File){
    int i;
    instructionNode * node;
    char formatted_data[18];
    for (i = ADDRESS_INIT; i < *IC ; i=i+BYTE_SIZE) {
        node = get_next_node_code();
        if(node == NULL){
            break;
        }
        sprintf(formatted_data, "%04d %02X %02X %02X %02X\n", node->address,
                (unsigned char)(node->code & TWO_BYTES), (unsigned char)((node->code >> SHIFT_ONE) & TWO_BYTES),
                (unsigned char)((node->code >> SHIFT_TWO) & TWO_BYTES), (unsigned char)((node->code >> SHIFT_THREE) & TWO_BYTES));
        fprintf(*File, "%s", formatted_data);
    }
    return OK;
}

/*
 * print data image to file ob
 */
int print_data_image(FILE ** File){
    int i;
    dataNode * node;
    char formatted_data[18];
    /*for (i = 0; i < *DC ; i=i+BYTE_SIZE) {
        node = get_next_node_code();
        if(node == NULL){
            break;
        }
        sprintf(formatted_data, "%04d %02X %02X %02X %02X\n", node->address,
                (unsigned char)(node->code & TWO_BYTES), (unsigned char)((node->code >> SHIFT_ONE) & TWO_BYTES),
                (unsigned char)((node->code >> SHIFT_TWO) & TWO_BYTES), (unsigned char)((node->code >> SHIFT_THREE) & TWO_BYTES));
        fprintf(*File, "%s", formatted_data);
    }*/
    return OK;
}


