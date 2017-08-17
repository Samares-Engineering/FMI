#ifndef __FMU_WRAPPER__
#define __FMU_WRAPPER__

#include <stdio.h>
#include "fmi2.h"

typedef struct {
  FMU            *fmus;
  fmi2Component  *component;
  fmi2Real        currentCommunicationPoint;
  fmi2Real        communicationStepSize;
  fmi2Boolean     noSetFMUStatePriorToCurrentPoint;
  FILE           *resultFile;
} FMUContext;

void freeContext (FMUContext ctx, int numberOfFMUs);

int
FMU_Activate_Entrypoint (int numberOfFMUs,
						 const char* fmuFileName[],
                         double tEnd,
                         double h,
                         fmi2Boolean loggingOn,
                         char separator,
                         int nCategories,
                         const fmi2String categories[],
                         FMUContext *ctx);

int
doStep (FMU * fmu,
        fmi2Component c,
        fmi2Real currentCommunicationPoint,
        fmi2Real communicationStepSize,
        fmi2Boolean noSetFMUStatePriorToCurrentPoint);

void outputRow_local(int numberOfFMUs, const char* NAMES_OF_FMUS[], FMU *fmus, fmi2Component * component, double time, FILE* file, char separator, fmi2Boolean header);

#endif /* __FMU_WRAPPER__ */
