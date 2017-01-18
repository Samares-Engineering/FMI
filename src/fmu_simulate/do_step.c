#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmuTemplate.h"
#include "do_step.h"

fmi2Status doStep(fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
  
    printf("Do one step.\n");
   
    return fmi2OK;
}

