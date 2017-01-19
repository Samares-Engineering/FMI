typedef struct {
    fmi2Real output_altitute;
    fmi2Real output_velocity;
}MoonLandingOuputs;

fmi2Status doStep(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint);

MoonLandingOuputs doStepMoonLanding(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint, fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint, fmi2Real inputThrust);
