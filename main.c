#include "assembler.h"

int main(int argc, char** argv) {
    int i,error_flag;
    FILE *file;

    /* error not enough files */
    if(argc<2){
        program_error(ERROR_MISSING_FILES);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        update_current_file_name(argv[i]);
        if(!check_file_extension()){
            program_error(ERROR_EXT_ERROR);
            continue; /* continue to next index to check more files */
        }
        /* checks if the file was open correctly */
        if((file = fopen(argv[i], "r")) != NULL){
            error_flag = first_run(file);
            if(get_errors_count() == FALSE && error_flag){
                error_flag = second_run();
                if(error_flag == ERROR){ /* found error in second run-> continue to next file*/
                    continue;
                }
                error_flag = export_free();
                if(error_flag == ERROR){ /* for error allocating*/
                    continue;
                }
            }
            else{ /* error in the file was found don't continue */
                /* print errors */
                print_errors();
            }
            fclose(file); /* close current file */
            free_every_file();
        }else{ /* failed open file continue to next file */
            program_error(ERROR_OPEN_FILE);
            continue; /* continue to next index to check more files */
        }
    }

    return 0;
}
