#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "sim_support.h"
#include "fmu_simulate.h"
#include "do_step.h"

int fmuSimulate(FMU* fmu, const char* fmuFileName, double tEnd, double h, fmi2Boolean loggingOn, char separator,
                    int nCategories, const fmi2String categories[]) {
    int i;
    double time;
    double tStart = 0;                      // start time
    const char *guid;                       // global unique id of the fmu
    const char *instanceName;               // instance name
    fmi2Component c;                        // instance of the fmu
    fmi2Status fmi2Flag;                    // return code of the fmu functions
    fmi2Status fmi2FlagTemp;
    char *fmuResourceLocation = getTempResourcesLocation(); // path to the fmu resources as URL, "file://C:\QTronic\sales"
    fmi2Boolean visible = fmi2False;        // no simulator user interface

    fmi2CallbackFunctions callbacks = {fmuLogger, calloc, free, NULL, fmu};  // called by the model during simulation
    ModelDescription* md;                      // handle to the parsed XML file
    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Real tolerance = 0;                    // used in setting up the experiment
    ValueStatus vs = 0;
    int nSteps = 0;
    Element *defaultExp;
    FILE* file;

    printf("FMU Simulator: run '%s' from t=0..%g with step size h=%g, loggingOn=%d, csv separator='%c' \n\n", fmuFileName, tEnd, h, loggingOn, separator);
    printf("log categories={ ");
    for (i = 0; i < nCategories; i++) printf("%s ", categories[i]);
    printf("}\n\n");
    
    // instantiate the fmu
    printf("Instantiate the FMU %s\n\n", fmuFileName);
    md = fmu->modelDescription;
    guid = getAttributeValue((Element *)md, att_guid);
    instanceName = getAttributeValue((Element *)getCoSimulation(md), att_modelIdentifier);
    c = fmu->instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceLocation,
                    &callbacks, visible, loggingOn);
    free(fmuResourceLocation);
    if (!c) return error("Could not instantiate model");

    if (nCategories > 0) {
        fmi2Flag = fmu->setDebugLogging(c, fmi2True, nCategories, categories);
        if (fmi2Flag > fmi2Warning) {
            return error("Could not initialize model; failed FMI set debug logging");
        }
    }

    // Setup experiment
    printf("Setup experiment\n\n");
    defaultExp = getDefaultExperiment(md);
    if (defaultExp) tolerance = getAttributeDouble(defaultExp, att_tolerance, &vs);
    if (vs == valueDefined) {
        toleranceDefined = fmi2True;
    }

    fmi2Flag = fmu->setupExperiment(c, toleranceDefined, tolerance, tStart, fmi2True, tEnd);
    if (fmi2Flag > fmi2Warning) {
        return error("could not initialize model; failed FMI setup experiment");
    }

    // Initialization of the FMU
    printf("Initialization of the FMU\n\n");
    fmi2Flag = fmu->enterInitializationMode(c);
    if (fmi2Flag > fmi2Warning) {
        return error("could not initialize model; failed FMI enter initialization mode");
    }
    fmi2Flag = fmu->exitInitializationMode(c);
    if (fmi2Flag > fmi2Warning) {
        return error("could not initialize model; failed FMI exit initialization mode");
    }

    // Open result file
    if (!(file = fopen(RESULT_FILE, "w"))) {
        printf("Could not write %s because:\n", RESULT_FILE);
        printf("    %s\n\n", strerror(errno));
        return 0; // failure
    }

    // Output solution for time t0
    outputRow(fmu, c, tStart, file, separator, fmi2True);  // output column names
    outputRow(fmu, c, tStart, file, separator, fmi2False); // output values

    // Enter the simulation loop
    printf("Entering the integration loop.\n\n");
    time = tStart;
    while (time < tEnd) {
        fmi2Flag = fmu->doStep(c, time, h, fmi2True);
        fmi2FlagTemp = doStep(c, time, h, fmi2True);
        if (fmi2Flag == fmi2Discard) {
            fmi2Boolean b;
            // check if model requests to end simulation
            if (fmi2OK != fmu->getBooleanStatus(c, fmi2Terminated, &b)) {
                return error("Could not complete simulation of the model. getBooleanStatus return other than fmi2OK.\n\n");
            }
            if (b == fmi2True) {
                return error("The model requested to end the simulation.\n\n");
            }
            return error("Could not complete simulation of the model.\n\n");
        }
        if (fmi2Flag != fmi2OK) return error("Could not complete simulation of the model.\n\n");
        time += h;
        outputRow(fmu, c, time, file, separator, fmi2False); // output values for this step
        nSteps++;
    }

    // End simulation
    printf("\nEnd of the simulation.\n\n");
    fmu->terminate(c);
    fmu->freeInstance(c);
    fclose(file);

    // print simulation summary
    printf("Simulation from %g to %g terminated successful\n", tStart, tEnd);
    printf("  steps ............ %d\n", nSteps);
    printf("  fixed step size .. %g\n", h);

    printf("CSV file '%s' written\n\n", RESULT_FILE);
    return 1; // success
}
