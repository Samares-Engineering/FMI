#if !defined(_AADL_fmi2CS)
#define _AADL_fmi2CS

#include "fmi2FunctionTypes.h"
#include "simulator/um_threads.h"

typedef enum {
	AADL_fmiCSInstantiated=0,
	AADL_fmiCSInitializationMode=1,
	AADL_fmiCSInitialized=2,
	AADL_fmiCSStepping=3,
	AADL_fmiCSTerminated=4,
	AADL_fmiCSError=5,
	AADL_fmiCSTerminationRequired=6,
} AADL_fmiCSMode;

typedef struct AADL_SimulatorSettings {
	//TODO: Identify here some settings, e.g round-robin, prempt, no-prempt, etc...
	fmi2Real startTime;
	fmi2Real stopTime;
	fmi2Real dt;
}AADL_SimulatorSettings;

typedef struct {
	fmi2CallbackFunctions functions;
	fmi2Boolean logCategories[4];
	char* instanceName;
	fmi2Type type;
	void* c;
	fmi2Boolean bSetupExperimentCalled;
	fmi2Real startTime;
	fmi2Boolean stopTimeDefined;
	fmi2Real stopTime;
}AADL_fmi2Component;

typedef struct {
	AADL_fmi2Component* c;
	AADL_fmiCSMode mode;
	AADL_SimulatorSettings aadlSettings;
	fmi2Real t0;
	fmi2Real t1;
	fmi2Real h;
	um_thread_id tid;
} AADL_fmi2CSComponent;

#endif
