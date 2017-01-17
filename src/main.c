/* ------------------------------------------------------------------------- 
 * sim_support.c
 * Functions used by both FMU simulators fmu20sim_me and fmu20sim_cs
 * to parse command-line arguments, to unzip and load an fmu,
 * to write CSV file, and more.
 *
 * Revision history
 *  07.03.2014 initial version released in FMU SDK 2.0.0
 *  10.04.2014 use FMI 2.0 headers that prefix function and type names with 'fmi2'.
 *             When 'fmi2' functions are not found in loaded DLL, look also for
 *             FMI 2.0 RC1 function names.
 *
 * Author: Adrian Tirea
 * Copyright QTronic GmbH. All rights reserved.
 * -------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2.h"
#include "fmu_import.h"

FMU fmu;

int main(int argc, char *argv[]) {
    const char* fmuFileName;
    int i;

    // parse command line arguments and load the FMU
    // default arguments value
    double tEnd = 1.0;
    double h=0.1;
    int loggingOn = 0;
    char csv_separator = ',';
    fmi2String *categories = NULL;
    int nCategories = 0;

    parseArguments(argc, argv, &fmuFileName, &tEnd, &h, &loggingOn, &csv_separator, &nCategories, &categories);
    loadFMU(fmuFileName);

  // run the simulation
    printf("FMU Simulator: run '%s' from t=0..%g with step size h=%g, loggingOn=%d, csv separator='%c' ",
            fmuFileName, tEnd, h, loggingOn, csv_separator);
    printf("log categories={ ");
    for (i = 0; i < nCategories; i++) printf("%s ", categories[i]);
    printf("}\n");

    simulate(&fmu, tEnd, h, loggingOn, csv_separator, nCategories, categories);
    printf("CSV file '%s' written\n", RESULT_FILE);

    // release FMU
    dlclose(fmu.dllHandle);
    freeModelDescription(fmu.modelDescription);

    // delete temp files obtained by unzipping the FMU
    deleteUnzippedFiles();

    return EXIT_SUCCESS;
}
