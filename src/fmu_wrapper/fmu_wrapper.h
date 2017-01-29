#ifndef __FMU_WRAPPER__
#define __FMU_WRAPPER__

#include <stdio.h>
#include "fmi2.h"

typedef struct {
  FMU            *fmu;
  fmi2Component   component;
  fmi2Real        currentCommunicationPoint;
  fmi2Real        communicationStepSize;
  fmi2Boolean     noSetFMUStatePriorToCurrentPoint;
  FILE           *resultFile;
} FMUContext;


int
FMU_Activate_Entrypoint (const char *fmuFileName, double tEnd, double h, fmi2Boolean loggingOn, char separator,
                         int nCategories, const fmi2String categories[], FMUContext *ctx);

int
doStep (FMU * fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
        fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint);

#endif /* __FMU_WRAPPER__ */
