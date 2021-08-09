#include "assembler.h"

/*
 * logic function for the first run over the current file
 */
int first_run(FILE *file)
{
    int status;
    status = init_every_file();
    if(status == ERROR){
        return ERROR;
    }
    status = read_by_line(file);
    if(status == ERROR){
        return ERROR;
    }
    update_symbol_data_addresses(); /* update symbol addresses */
    update_data_list_addresses();/* update data addresses */
    return OK;
}

/*
 * second run
 * do update of entry, and labels as args to complete the code
 */
int second_run(){
    int status;
    status = check_entry_labels();
    if(status == ERROR){
        return ERROR;
    }
    status = update_instructions_with_label();
    if(status == ERROR){
        return ERROR;
    }
    return OK;
}

/*
 * export file and free variables
 */
int export_free(){
    int status;
    status = export_files();
    if(status == ERROR){
        return ERROR;
    }

    return OK;
}

