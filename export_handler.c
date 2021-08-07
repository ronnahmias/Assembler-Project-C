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
 * export entry file
 */
int export_ent_file();

/*
 * export entry file
 */
int export_ext_file();

/*
 * print number of the instructions and data code lines
 */
int print_num_rows(FILE **File);

/*
 * print data image to file ob
 */
int print_data_image(FILE ** File);

/* end - prototypes functions */


/*
 * function that handler all export files
 */
int export_files(){
    export_ob_file();
    export_ent_file();
    export_ext_file();
    return OK;
}

/*
 * export entry file
 */
int export_ext_file(){
    char file_name[FILE_NAME_LEN] = {FALSE};
    char formatted_data[ROW_LINE] ={FALSE};
    FILE * File_Handler;
    externNode * node;

    /* no extern values for export -> no file generate */
    if(!extern_nodes_exists()){
        return OK;
    }

    /* generate .ent file name */
    sprintf(file_name, "%s.ext", strtok(FileName,DOT));
    File_Handler = fopen(file_name, "w");

    if(File_Handler == NULL){
        program_error(ERROR_OPEN_FILE_EXPORT);
        return ERROR;
    }
    while((node = get_next_extern_node()) != NULL){
        sprintf(formatted_data, "%s %04ld\n", node->symbol,node->address);
        fprintf(File_Handler, "%s", formatted_data);
        free(node);
    }
    fclose(File_Handler);
    return OK;
}

/*
 * export entry file
 */
int export_ent_file(){
    char file_name[FILE_NAME_LEN] = {FALSE};
    char formatted_data[ROW_LINE] ={FALSE};
    FILE * File_Handler;
    entryNode * node;

    /* no entry values for export -> no file generate */
    if(!entry_nodes_exists()){
        return OK;
    }

    /* generate .ent file name */
    sprintf(file_name, "%s.ent", strtok(FileName,DOT));
    File_Handler = fopen(file_name, "w");

    if(File_Handler == NULL){
        program_error(ERROR_OPEN_FILE_EXPORT);
        return ERROR;
    }
    while((node = get_next_entry_node()) != NULL){
        sprintf(formatted_data, "%s %04ld\n", node->symbol,node->address);
        fprintf(File_Handler, "%s", formatted_data);
        free(node);
    }

    fclose(File_Handler);
    return OK;
}

/*
 * export ob file with
 * instructions code and
 * data image code
 */
int export_ob_file(){
    char file_name[FILE_NAME_LEN] = {FALSE};
    FILE * File_Handler;

    /* generate ob file name */
    sprintf(file_name, "%s.ob", strtok(FileName,DOT));
    File_Handler = fopen(file_name, "w");

    if(File_Handler == NULL){
        program_error(ERROR_OPEN_FILE_EXPORT);
        return ERROR;
    }

    print_num_rows(&File_Handler); /* print ob caption row */
    print_code(&File_Handler); /* print instructions code to ob file */
    print_data_image(&File_Handler); /* print data image to ob file */
    fclose(File_Handler);
    return OK;
}

/*
 * print number of the instructions and data code lines
 */
int print_num_rows(FILE **File){
    char formatted_data[CODE_PRINT_LEN];
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
    char formatted_data[CODE_PRINT_LEN];
    for (i = ADDRESS_INIT; i < *IC ; i=i+BYTE_SIZE) {
        node = get_next_node_code();
        if(node == NULL){
            break;
        }
        sprintf(formatted_data, "%04d %02X %02X %02X %02X\n", node->address,
                (unsigned char)(node->code & TWO_BYTES), (unsigned char)((node->code >> SHIFT_ONE) & TWO_BYTES),
                (unsigned char)((node->code >> SHIFT_TWO) & TWO_BYTES), (unsigned char)((node->code >> SHIFT_THREE) & TWO_BYTES));
        fprintf(*File, "%s", formatted_data);
        free(node);
    }
    return OK;
}

/*
 * insert data to array for export to file
 */
unsigned char* prepare_data_export(){
    unsigned char * data_code;
    int data_index,i;
    dataNode * node;
    data_code = (unsigned char*)calloc(*DC, sizeof(unsigned char));
    if(data_code == NULL){
        program_error(ERROR_ALLOCATING_MEMORY);
        return NULL;
    }
    data_index = 0;
    /* loop on all nodes in data image list */
    while((node = get_next_node_data())!= NULL) {
        i = 0;
        switch (node->datatype) {
            case DB:
            case ASCIZ:
                memcpy((data_code + data_index),(unsigned char *)node->db,1);
                data_index++;
                free(node->db);
                break;
            case DH:
                while(i !=2){
                    data_code[data_index++] = ((*(node->dh) >> (i * SHIFT_ONE)) & TWO_BYTES);
                    i++;
                }
                free(node->dh);
                break;
            case DW:
                while(i !=4){
                    data_code[data_index++] = ((*(node->dw) >> (i * SHIFT_ONE)) & TWO_BYTES);
                    i++;
                }
                free(node->dw);
                break;
        }
        free(node);
    }
    return data_code;
}

/*
 * print data image to file ob
 */
int print_data_image(FILE ** File){
    unsigned char * data_code;
    int i,j;
    long address;
    char formatted_date[20] = { 0 };
    data_code = prepare_data_export();
    /* print full row with 4 bytes as hex format */
    for(j=0,i=0, address = *IC;j<*DC/BYTE_SIZE;i+=BYTE_SIZE, address+=BYTE_SIZE,j++){
        sprintf(formatted_date, "%04ld %02X %02X %02X %02X\n",address,data_code[i], data_code[i+1],data_code[i+2],data_code[i+3]);
        fprintf(*File, "%s", formatted_date);
    }
    /* we have more bits to print but not 4 bytes */
    j = (int)*DC%BYTE_SIZE;
    if(j != 0){
        switch (j) {
            case 1:
                sprintf(formatted_date, "%04ld %02X\n",address, data_code[i]);
                break;
            case 2:
                sprintf(formatted_date, "%04ld %02X %02X\n",address, data_code[i], data_code[i+1]);
                break;
            case 3:
                sprintf(formatted_date, "%04ld %02X %02X %02X\n",address, data_code[i], data_code[i+1],data_code[i+2]);
                break;
            default:
                break;
        }
        fprintf(*File, "%s", formatted_date);
    }
    free(data_code);
    return OK;
}
