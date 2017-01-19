#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "do_step.h"

fmi2Status doStep(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
   
   fmi2Status fmi2Flag;
   
   fmi2Flag = fmu->doStep(c, currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint);
    if (fmi2Flag == fmi2Discard) {
    	fmi2Boolean b;
        // Check if model requests to end simulation
        if (fmi2OK != fmu->getBooleanStatus(c, fmi2Terminated, &b)) {
        	return error("Could not complete simulation of the model. getBooleanStatus return other than fmi2OK.\n\n");
        }
        if (b == fmi2True) {
                return error("The model requested to end the simulation.\n\n");
        }
            return error("Could not complete simulation of the model.\n\n");
    }

    //if (fmi2Flag != fmi2OK) return error("Could not complete simulation of the model.\n\n");
   
    printf("Do one step. %d\n\n", fmi2Flag);
}

MoonLandingOuputs doStepMoonLanding(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint, fmi2Real inputThrust) {
  
    
    MoonLandingOuputs moonLandingOuputs;

    fmi2ValueReference vr;
    fmi2Real r;
    fmi2Status fmi2Flag;

    // Get the scalar variables
    ScalarVariable *input_thrust_sv = getVariable(fmu->modelDescription, "thrust");
    ScalarVariable *output_altitute_sv = getVariable(fmu->modelDescription, "a");
    ScalarVariable *output_velocity_sv = getVariable(fmu->modelDescription, "v");

    // Set the input
    vr = getValueReference(input_thrust_sv);
    fmi2Flag = fmu->setReal(c, &vr, 1, &inputThrust); 

    // Calculate the Step
    fmi2Flag = doStep(fmu, c, currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint);

    // Get the outputs
    vr = getValueReference(output_altitute_sv);
    fmi2Flag = fmu->getReal(c, &vr, 1, &r); //get the altitude output
    moonLandingOuputs.output_altitute = r;

    vr = getValueReference(output_velocity_sv);
    fmi2Flag = fmu->getReal(c, &vr, 1, &r); //get the velocity output
    moonLandingOuputs.output_velocity = r;

    //printf("INPUT THRUST === %d\n", inputThrust);
    printf("OUPUT ALTITUDE === %f\n", moonLandingOuputs.output_altitute);
    printf("OUPUT VELOCITY === %f\n\n", moonLandingOuputs.output_velocity);
  
    return moonLandingOuputs;
}

