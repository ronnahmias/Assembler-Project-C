#include <stdio.h>
#include "assembler.h"

int main(int argc, char** argv) {

    int i;
    FILE *file;
    /* error not enough files */
    if(argc<2){
        fprintf(stderr, "missing files");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if((file = fopen(argv[i], "r")) != NULL){
            first_run(file);
            fclose(file); /* close current file */
        }
    }

    return 0;
}
