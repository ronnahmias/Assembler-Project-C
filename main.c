#include <stdio.h>
#include "assembler.h"

int main(int argc, char** argv) {

    int i;
    FILE *file;
    /* error not enough files */
    if(argc<2){
        // TODO ERROR
        fprintf(stderr, "missing files");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        /* checks if the file was open correctrly */
        if((file = fopen(argv[i], "r")) != NULL){
            first_run(file);
            //second_run(file);
            // TODO check file ok
            //export_files();
            fclose(file); /* close current file */
        }
    }

    return 0;
}
