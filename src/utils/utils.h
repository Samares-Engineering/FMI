#include "fmi2.h"

typedef struct {
    fmi2Real output_altitute;
    fmi2Real output_velocity;
}MoonLandingOuputs;

typedef struct {
     FMU* fmu;
     fmi2Component component; 
     fmi2Real currentCommunicationPoint;
     fmi2Real communicationStepSize; 
     fmi2Boolean noSetFMUStatePriorToCurrentPoint;
} FMUtoSimulate;
