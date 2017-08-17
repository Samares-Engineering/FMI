
// define class name and unique id
#define MODEL_IDENTIFIER FmuExportCrossCompile
#define MODEL_GUID "{5a4fa8dc-cd97-434c-ab30-e352e643f853}"

// include fmu header files, typedefs and macros
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "util/omc_error.h"
#include "FmuExportCrossCompile_functions.h"
#include "simulation/solver/initialization/initialization.h"
#include "simulation/solver/events.h"
#include "fmu2_model_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

void setStartValues(ModelInstance *comp);
void setDefaultStartValues(ModelInstance *comp);
void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo);
fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value);
fmi2Integer getInteger(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Integer value);
fmi2Boolean getBoolean(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value);
fmi2String getString(ModelInstance* comp, const fmi2ValueReference vr);
fmi2Status setString(ModelInstance* comp, const fmi2ValueReference vr, fmi2String value);
fmi2Status setExternalFunction(ModelInstance* c, const fmi2ValueReference vr, const void* value);

// define model size
#define NUMBER_OF_STATES 2
#define NUMBER_OF_EVENT_INDICATORS 1
#define NUMBER_OF_REALS 7
#define NUMBER_OF_INTEGERS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 1
#define NUMBER_OF_EXTERNALFUNCTIONS 0

// define variable data for model
#define $Ph_vr 0 
#define $Pv_vr 1 
#define $P$DER$Ph_vr 2 
#define $P$DER$Pv_vr 3 
#define $Pv_new_vr 4 
#define $Pe_vr 5 
#define $Pg_vr 6 
#define $P$whenCondition1_vr 0 


// define initial state vector as vector of value references
#define STATES { $Ph_vr, $Pv_vr }
#define STATESDERIVATIVES { $P$DER$Ph_vr, $P$DER$Pv_vr }


// implementation of the Model Exchange functions
  extern void FmuExportCrossCompile_setupDataStruc(DATA *data);
  #define fmu2_model_interface_setupDataStruc FmuExportCrossCompile_setupDataStruc
  #include "fmu2_model_interface.c"

// Set values for all variables that define a start value
void setDefaultStartValues(ModelInstance *comp) {

comp->fmuData->modelData->realVarsData[0].attribute.start = 1.0;
comp->fmuData->modelData->realVarsData[1].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[2].attribute.start = 0;
comp->fmuData->modelData->realVarsData[3].attribute.start = 0;
comp->fmuData->modelData->realVarsData[4].attribute.start = 0.0;
comp->fmuData->modelData->booleanVarsData[0].attribute.start = 0;
comp->fmuData->modelData->realParameterData[0].attribute.start = 0.7;
comp->fmuData->modelData->realParameterData[1].attribute.start = 9.81;
}
// Set values for all variables that define a start value
void setStartValues(ModelInstance *comp) {

  comp->fmuData->modelData->realVarsData[0].attribute.start =  comp->fmuData->localData[0]->realVars[0];
  comp->fmuData->modelData->realVarsData[1].attribute.start =  comp->fmuData->localData[0]->realVars[1];
  comp->fmuData->modelData->realVarsData[2].attribute.start =  comp->fmuData->localData[0]->realVars[2];
  comp->fmuData->modelData->realVarsData[3].attribute.start =  comp->fmuData->localData[0]->realVars[3];
  comp->fmuData->modelData->realVarsData[4].attribute.start =  comp->fmuData->localData[0]->realVars[4];
  comp->fmuData->modelData->booleanVarsData[0].attribute.start =  comp->fmuData->localData[0]->booleanVars[0];
comp->fmuData->modelData->realParameterData[0].attribute.start = comp->fmuData->simulationInfo->realParameter[0];
comp->fmuData->modelData->realParameterData[1].attribute.start = comp->fmuData->simulationInfo->realParameter[1];
}
  // Used to set the next time event, if any.
  void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo) {
  }
  
  fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $Ph_vr : return comp->fmuData->localData[0]->realVars[0]; break;
        case $Pv_vr : return comp->fmuData->localData[0]->realVars[1]; break;
        case $P$DER$Ph_vr : return comp->fmuData->localData[0]->realVars[2]; break;
        case $P$DER$Pv_vr : return comp->fmuData->localData[0]->realVars[3]; break;
        case $Pv_new_vr : return comp->fmuData->localData[0]->realVars[4]; break;
        case $Pe_vr : return comp->fmuData->simulationInfo->realParameter[0]; break;
        case $Pg_vr : return comp->fmuData->simulationInfo->realParameter[1]; break;
        default:
            return 0;
    }
  }
  
  fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value) {
    switch (vr) {
        case $Ph_vr : comp->fmuData->localData[0]->realVars[0] = value; break;
        case $Pv_vr : comp->fmuData->localData[0]->realVars[1] = value; break;
        case $P$DER$Ph_vr : comp->fmuData->localData[0]->realVars[2] = value; break;
        case $P$DER$Pv_vr : comp->fmuData->localData[0]->realVars[3] = value; break;
        case $Pv_new_vr : comp->fmuData->localData[0]->realVars[4] = value; break;
        case $Pe_vr : comp->fmuData->simulationInfo->realParameter[0] = value; break;
        case $Pg_vr : comp->fmuData->simulationInfo->realParameter[1] = value; break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2Integer getInteger(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        default:
            return 0;
    }
  }
  fmi2Status setInteger(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Integer value) {
    switch (vr) {
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  fmi2Boolean getBoolean(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $P$whenCondition1_vr : return comp->fmuData->localData[0]->booleanVars[0]; break;
        default:
            return fmi2False;
    }
  }
  
  fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value) {
    switch (vr) {
        case $P$whenCondition1_vr : comp->fmuData->localData[0]->booleanVars[0] = value; break;
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2String getString(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        default:
            return "";
    }
  }
  
  fmi2Status setString(ModelInstance* comp, const fmi2ValueReference vr, fmi2String value) {
    switch (vr) {
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  
  fmi2Status setExternalFunction(ModelInstance* c, const fmi2ValueReference vr, const void* value){
    switch (vr) {
        default:
            return fmi2Error;
    }
    return fmi2OK;
  }
  

#ifdef __cplusplus
}
#endif

