#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "sim_support.h"
#include "fmu_simulate.h"
#include "do_step.h"

/*static char *getResourcesLocationTemp(char* tempPath) {
    char *resourcesLocation = (char *)calloc(sizeof(char), 9 + strlen(RESOURCES_DIR) + strlen(tempPath));
    strcpy(resourcesLocation, "file:///");
    strcat(resourcesLocation, tempPath);
    strcat(resourcesLocation, RESOURCES_DIR);
    return resourcesLocation;
}*/

/*void stepfinished (fmi2ComponentEnvironment x, fmi2Status y) {
  printf ("Been there, done that\n");
}*/

char *dummyresource = "file:///home/jmgauthier/Work/git_samares/FMI/bin/foo/resources\\"; //Dummy

int initializeModel(FMU* fmu, fmi2Component c, const char* fmuFileName){
    fmi2Status fmi2Flag;

    printf("Initialization of the FMU %s.\n", fmuFileName);
    fmi2Flag = fmu->enterInitializationMode(c);
    if (fmi2Flag > fmi2Warning) {
        return error("Could not initialize model; failed FMI enter initialization mode");
    }
    fmi2Flag = fmu->exitInitializationMode(c);
    if (fmi2Flag > fmi2Warning) {
        return error("Could not initialize model; failed FMI exit initialization mode");
    }

    return 1; // Success
}

int fmuSimulate(FMU* fmu, const char* fmuFileName, double tEnd, double h, fmi2Boolean loggingOn, char separator,
                    int nCategories, const fmi2String categories[]) {
    int i;
    int nSteps = 0;
    double time;
    double tStart = 0; // start time

    const char *guid; // global unique id of the fmu
    const char *instanceName; // instance name
    char *fmuResourceLocation; //Dummy

    fmi2Status fmi2Flag; // return code of the fmu functions
    fmi2Component c; // instance of the fmu
    ModelDescription *md; // handle to the parsed XML file
    fmi2Real tolerance = 0; // used in setting up the experiment
    fmi2Boolean toleranceDefined = fmi2False;  // true if model description define tolerance
    fmi2Boolean visible = fmi2False; // no simulator user interface
    fmi2CallbackFunctions callbacks = {fmuLogger, calloc, free, NULL, fmu};  // called by the model during simulation

    ValueStatus vs = 0;
    Element *defaultExp;
    FILE *file;
    
    MoonLandingOuputs *moonLandingOuputs;
    moonLandingOuputs = (MoonLandingOuputs *) malloc(sizeof(MoonLandingOuputs)); //Specific to moonlanding

    if(moonLandingOuputs == NULL){
        fprintf(stderr, "Allocation failed.");
	exit(EXIT_FAILURE);
    }

    printf("FMU Simulator: run '%s' from t=0..%g with step size h=%g, loggingOn=%d, csv separator='%c' \n\n", fmuFileName, tEnd, h, loggingOn, separator);
    printf("log categories={ ");
    for (i = 0; i < nCategories; i++) printf("%s ", categories[i]);
    printf("}\n\n");

    //char *fmuResourceLocation = getResourcesLocationTemp(tmpPath); // Bug when using JModelica: path is absolute.
    fmuResourceLocation = malloc (strlen (dummyresource) + 2); //Dummy 
    strcpy (fmuResourceLocation, dummyresource); //Dummy

    printf("Instantiate the FMU %s. \n", fmuFileName);
    printf("----- Location %s.\n", fmuResourceLocation);
    md = fmu->modelDescription;
    guid = getAttributeValue((Element *)md, att_guid);
    instanceName = getAttributeValue((Element *)getCoSimulation(md), att_modelIdentifier);
    c = fmu->instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceLocation, &callbacks, visible, loggingOn);
    free(fmuResourceLocation);
    if (!c) return error("Could not instantiate model");

    printf("----- Set debug logging.\n");
    if (nCategories > 0) {
        fmi2Flag = fmu->setDebugLogging(c, fmi2True, nCategories, categories);
        if (fmi2Flag > fmi2Warning) return error("Could not finish instantiation; failed to set debug logging");
    }

    printf("----- Setup experiment\n");
    defaultExp = getDefaultExperiment(md);
    if (defaultExp) tolerance = getAttributeDouble(defaultExp, att_tolerance, &vs);
    if (vs == valueDefined) toleranceDefined = fmi2True;
    fmi2Flag = fmu->setupExperiment(c, toleranceDefined, tolerance, tStart, fmi2True, tEnd);
    if (fmi2Flag > fmi2Warning) return error("Could not finish instantiation; failed FMI setup experiment");

    initializeModel(fmu, c, fmuFileName);
    printf("\n\n");


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
        
        fmi2Real inputThrust = 10000.0; //Specific input for the MoonLanding
        
        doStepMoonLanding(fmu, c, time, h, fmi2True, inputThrust, moonLandingOuputs); //Specific to MoonLanding

    printf("OUPUT ALTITUDE === %f\n", moonLandingOuputs->output_altitute);
    printf("OUPUT VELOCITY === %f\n\n", moonLandingOuputs->output_velocity);

   	//fmi2Flag = doStep(fmu, c, time, h, fmi2True); //Activate to use other FMUs
        time += h;
        outputRow(fmu, c, time, file, separator, fmi2False); //Output values for this step
        nSteps++;
    }

    // End simulation
    printf("\nEnd of the simulation.\n\n");
    free(moonLandingOuputs);
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
