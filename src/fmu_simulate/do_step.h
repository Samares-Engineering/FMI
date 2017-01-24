#include "utils.h"

int doStep(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint);

int doStepMoonLanding(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint, fmi2Real inputThrust, MoonLandingOuputs* moonLandingOuputs);
