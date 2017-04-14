#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2Functions.h"
#include "fmi2TypesPlatform.h"
#include "um_threads.h"
#include "workload.h"
#include "AADL_fmi2CS.h"

fmi2Status allocateSlave(fmi2Component c);
fmi2Status freeSlave(fmi2Component c);

int CreateSimulatorInstance(void){
	int i;
  	um_thread_id tid;
	initialize_period();
	
	return 1;
}

fmi2Status allocateSlave(fmi2Component c){
	//TODO: Allocate the component and instantiate the simulator
  	
	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci;

	ci = (AADL_fmi2CSComponent*)calloc(1, sizeof(AADL_fmi2CSComponent));
	
	if(CreateSimulatorInstance() == 1){
		
		printf("Simulator created.\n");

		ci->c = cc;
		cc->c = ci;

		return fmi2OK;
	}
	else{
		free(ci);
	}

	return fmi2Error;
}

fmi2Status freeSlave(fmi2Component c){
	//TODO: free the model and free the simulateur
	return fmi2OK;
}

fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type iType, fmi2String fmuGUID, fmi2String fmuResourceLocation, const fmi2CallbackFunctions*functions, fmi2Boolean visible, fmi2Boolean loggingOn)
{
	size_t i;
	fmi2Component c;
	AADL_fmi2Component* cc;

	c = (fmi2Component)calloc(1, sizeof(AADL_fmi2Component));
	cc = (AADL_fmi2Component*)c;
	
	cc->instanceName = (char*)calloc(strlen(instanceName) + 1, sizeof(char));
	strcpy(cc->instanceName, instanceName);

	if(allocateSlave(c) == fmi2OK){
		printf("AADL FMU allocated\n");
	}
	else{
		free(cc->instanceName);
		free(cc);
	}	
	return 0;
}

fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint, fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint)
{
   	printf("The simulator perform one step \n");
   	return fmi2OK;
}

