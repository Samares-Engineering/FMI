#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2.h"
#include "sim_support.h"
#include "fmu_import.h"
#include "fmu_simulate.h"

FMU fmu; // the fmu to simulate

/*static void deleteTempFiles(char* fmuTempPath) {
    char *cmd = (char *)calloc(15 + strlen(fmuTempPath), sizeof(char));
#if WINDOWS
    sprintf(cmd, "rmdir /S /Q %s", fmuTempPath);
#else
    sprintf(cmd, "rm -rf %s", fmuTempPath);
#endif
    system(cmd);
    free(cmd);
}*/

int main(int argc, char *argv[]) {
    const char* fmuFileName;
    double tEnd = 1.0;
    double h=0.1;
    int loggingOn = 0;
    char csv_separator = ',';
    fmi2String *categories = NULL;
    int nCategories = 0;
 
    parseArguments(argc, argv, &fmuFileName, &tEnd, &h, &loggingOn, &csv_separator, &nCategories, &categories);

    fmuImport(fmuFileName);
   
    fmuSimulate(&fmu, fmuFileName, tEnd, h, loggingOn, csv_separator, nCategories, categories);

    printf("Release FMU\n\n");
    dlclose(fmu.dllHandle);
    freeModelDescription(fmu.modelDescription);
    //deleteTempFiles(tmpPath);	
    //free(tmpPath);
    return EXIT_SUCCESS;
}
