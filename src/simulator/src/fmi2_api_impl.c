#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2Functions.h"
#include "fmi2TypesPlatform.h"
#include "simulator/um_threads.h"
#include "simulator/workload.h"
#include "simulator/user_code.h"
#include "simulator/rr.h"

#include "AADL_fmi2CS.h"

int doOneStep(fmi2Real time, fmi2Real ccp){

	float t = time;
	float h = ccp;

	initialize_period();
	configure_rr_scheduler_2(h);

	start_scheduler();

	printf("doStep finished");

	return 1;
}

int createSimulatorInstance(void){

	return 1;
}

fmi2Status allocateSlave(fmi2Component c){
  	
	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci;

	ci = (AADL_fmi2CSComponent*)calloc(1, sizeof(AADL_fmi2CSComponent));
	
	if(createSimulatorInstance() == 1){
		
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

int InitializeSlave(fmi2Component c){

	int i;

	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci = (AADL_fmi2CSComponent*)cc->c;

	for (i = 0 ; i < 10 ; ++i){

	  	ci->tid = um_thread_create(user_thread, STACKSIZE, 0);
	}

	return 1;
}

fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type iType, fmi2String fmuGUID, fmi2String fmuResourceLocation, const fmi2CallbackFunctions*functions, fmi2Boolean visible, fmi2Boolean loggingOn)
{
	fmi2Component c;
	AADL_fmi2Component* cc;

	c = (fmi2Component)calloc(1, sizeof(AADL_fmi2Component));
	cc = (AADL_fmi2Component*)c;
	
	cc->instanceName = (char*)calloc(strlen(instanceName) + 1, sizeof(char));
	strcpy(cc->instanceName, instanceName);

	if(allocateSlave(c) == fmi2OK){
		((AADL_fmi2CSComponent*)cc->c)->mode = AADL_fmiCSInstantiated;
		printf("The slave is instantiated. \n");
		return c;
	}
	else{
		free(cc->instanceName);
		free(cc);
	}	
	return 0;
}

fmi2Status fmi2SetupExperiment(fmi2Component c, fmi2Boolean toleranceDefined, fmi2Real tolerance, fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime)
{
	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci = (AADL_fmi2CSComponent*)cc->c;

	if(ci->mode == AADL_fmiCSError){
		return fmi2Error;
	}

	if(ci->mode == AADL_fmiCSInstantiated){
		cc->startTime = startTime;

		cc->stopTimeDefined = stopTimeDefined;
		if(cc->stopTimeDefined){
			cc->stopTime = stopTime;

			if(cc->startTime > cc->stopTime){
				ci->mode = AADL_fmiCSError;
				return fmi2Error;
			}
		}
		if(cc->stopTimeDefined){
			ci->aadlSettings.stopTime = cc->stopTime;
		}
		else{
			ci->aadlSettings.stopTime = startTime-1.0;
		}

		ci->aadlSettings.startTime = cc->startTime;
	}
	else{
		printf("The function fmi2SetupExperiment was called after initialization. This is not conform to the fmi2 specification.\nThe function call is ignored.\n");
		return fmi2Warning;
	}

	return fmi2OK;
}

fmi2Status fmi2EnterInitializationMode(fmi2Component c){

	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci = (AADL_fmi2CSComponent*)cc->c;

	if(ci->mode != AADL_fmiCSInstantiated){
		return fmi2Error;
	}

	if(!InitializeSlave(c)){
		ci->mode = AADL_fmiCSError;
	}

	ci->mode = AADL_fmiCSInitializationMode;

	printf("The slave enter initialization mode. \n");

	return fmi2OK;
}

fmi2Status fmi2ExitInitializationMode(fmi2Component c){

	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
	AADL_fmi2CSComponent* ci = (AADL_fmi2CSComponent*)cc->c;

	if(ci->mode != AADL_fmiCSInitializationMode){
		ci->mode = AADL_fmiCSError;
		return fmi2Error;
	}

	ci->mode = AADL_fmiCSInitialized;
	ci->t0=ci->aadlSettings.startTime;

	printf("The slave exit initialization mode. \n");

	return fmi2OK;
}



fmi2Status fmi2DoStep(fmi2Component c, fmi2Real time, fmi2Real h, fmi2Boolean noSetFMUStatePriorToCurrentPoint)
{
   	AADL_fmi2Component* cc = (AADL_fmi2Component*)c;
   	AADL_fmi2CSComponent* ci = (AADL_fmi2CSComponent*)cc->c;

   	if(ci->mode==AADL_fmiCSError)
   	{
   		printf("fmi2DoStep: An error occurred in a previous call. Unable to proceed.\n");
   		return fmi2Error;
   	}
   	if(ci->mode==AADL_fmiCSInitialized)
   	{
   			/* Check Timing */
   			if(ci->t0!=time)
   			{
   				printf("fmi2DoStep: First communication time != startTime. \n");
   				ci->mode = AADL_fmiCSError;
   				return fmi2Error;
   			}
   	}

   	ci->t0=time;
   	ci->t1=time+h;
   	ci->h=h;

   	if((ci->mode==AADL_fmiCSInitialized)||(ci->mode==AADL_fmiCSStepping)){
   		if(ci->mode==AADL_fmiCSInitialized){
   				ci->mode = AADL_fmiCSStepping;
   		}

   		if(doOneStep(time, h)<0)
   		{
   			ci->mode = AADL_fmiCSError;
   			return fmi2Error;
   		}
   	}
   	else
   	{
   		printf("fmi2DoStep: fmi2DoStep is called without initialization sequence before.\n");
   		ci->mode = AADL_fmiCSError;
   		return fmi2Error;
   	}

   	return fmi2OK;
}

