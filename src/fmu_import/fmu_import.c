#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmu_import.h"

void loadFMU(const char* fmuFileName) {
    printf("Loading FMU %s \n", fmuFileName);
    printf("FMU %s Loaded\n", fmuFileName);
}
