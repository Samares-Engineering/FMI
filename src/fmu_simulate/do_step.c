#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fmi2.h"
#include "do_step.h"

void doStep(FMU* fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
  
    fmi2Status fmi2Flag;
    /*fmi2ValueReference vr;
    fmi2Real r;

    ScalarVariable *input_thrust_sv = getScalarVariable(fmu->modelDescription, 56);//Dummy
    ScalarVariable *output_altitute_sv = getScalarVariable(fmu->modelDescription, 40);//Dummy
    ScalarVariable *output_velocity_sv = getScalarVariable(fmu->modelDescription, 57);//Dummy

    vr = getValueReference(input_thrust_sv);
    fmi2Real input_thrust = fmu->getReal(c, &vr, 1, &r);

    vr = getValueReference(output_altitute_sv);
    fmi2Real output_altitute = fmu->getReal(c, &vr, 1, &r);

    vr = getValueReference(output_velocity_sv);
    fmi2Real output_velocity = fmu->getReal(c, &vr, 1, &r);

    printf("INPUT THRUST === %d\n", input_thrust);
    printf("OUPUT ALTITUDE === %d\n", output_altitute);
    printf("OUPUT VELOCITY === %d\n\n", output_altitute);*/

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
  
    //return fmi2OK;
}

