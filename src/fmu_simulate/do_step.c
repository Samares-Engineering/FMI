#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "fmuTemplate.h"
#include "do_step.h"

fmi2Status doStep(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
  
    fmi2Status fmi2Flag;

    fmi2Flag = fmu->doStep(c, currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint);
    
    printf("Do one step. %d\n", fmi2Flag);
   
    return fmi2OK;
}

