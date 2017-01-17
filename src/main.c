#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmu_import.h"

void printHelp(const char *fmusim) {
    printf("command syntax: %s <model.fmu>\n", fmusim);
    printf("   <model.fmu> .... path to FMU, relative to current dir or absolute, required\n");
}


int main(int argc, char *argv[]) {
    const char* fmuFileName;
    
    if (argc > 1) {
        fmuFileName = argv[1];
    } else {
        printf("error: no fmu file\n");
        printHelp(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    loadFMU(fmuFileName);

    return EXIT_SUCCESS;
}
