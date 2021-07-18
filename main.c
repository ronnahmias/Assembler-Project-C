#include <stdio.h>
#include "assembler.h"

int main(int argc, char** argv) {

    int i;
    FILE *file;
    /* error not enough files */
    if(argc<2){
        program_error(ERROR_MISSING_FILES);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        update_current_file_name(argv[i]);
        /* checks if the file was open correctrly */
        if((file = fopen(argv[i], "r")) != NULL){
            first_run(file);
            if(get_errors_count() == FALSE){
                //second_run(file);
                /* TODO check file ok*/
                //export_files();
            }else{

            }

            fclose(file); /* close current file */
        }
    }

    return 0;
}
