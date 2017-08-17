
// define class name and unique id
#define MODEL_IDENTIFIER RoomHeating_OM_RH
#define MODEL_GUID "{e0da2bdb-ec76-42d1-bd09-a8db9cb3c63a}"

// include fmu header files, typedefs and macros
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "openmodelica.h"
#include "openmodelica_func.h"
#include "simulation_data.h"
#include "util/omc_error.h"
#include "RoomHeating_OM_RH_functions.h"
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
#define NUMBER_OF_STATES 4
#define NUMBER_OF_EVENT_INDICATORS 2
#define NUMBER_OF_REALS 49
#define NUMBER_OF_INTEGERS 0
#define NUMBER_OF_STRINGS 0
#define NUMBER_OF_BOOLEANS 0
#define NUMBER_OF_EXTERNALFUNCTIONS 0

// define variable data for model
#define $Proom$PRAT_vr 0 
#define $Proom$Penergy_vr 1 
#define $Pwall$PTisurf_vr 2 // "internal surface temperature of the wall"
#define $Pwall$PTosurf_vr 3 // "external surface temperature of the wall"
#define $P$DER$Proom$PRAT_vr 4 
#define $P$DER$Proom$Penergy_vr 5 
#define $P$DER$Pwall$PTisurf_vr 6 // "internal surface temperature of the wall"
#define $P$DER$Pwall$PTosurf_vr 7 // "external surface temperature of the wall"
#define $POAT_vr 8 
#define $PRAT_vr 9 
#define $Pfanspeed_vr 10 
#define $Proom$PDT_vr 11 
#define $Proom$PEWT_vr 12 // "entering water temperature"
#define $Proom$PQin_vr 13 // "heat transferred to the air in the coil"
#define $Proom$PQout_vr 14 // "heat lost through room walls"
#define $Proom$PSAT_vr 15 // "supply air temperature"
#define $Proom$Pfs_vr 16 
#define $Proom$Pmdota_vr 17 // "air flow rate leaving the fan"
#define $Proom$Pmdotw_vr 18 // "water flow rate leaving the valve"
#define $Proom$Pvo_vr 19 
#define $Pvalveopen_vr 20 
#define $Pwall$PC_vr 21 // "thermal capacity of the wall"
#define $Pwall$PR_vr 22 // "wall resistance"
#define $Proom$PAwall_vr 23 // "wall surface area"
#define $Proom$PLWT_vr 24 // "leaving water temperature"
#define $Proom$PRATinit_vr 25 // "initial room air temperature"
#define $Proom$PcAir_vr 26 // "specific heat of air"
#define $Proom$PcWater_vr 27 // "specific heat of water"
#define $Proom$Peps_vr 28 // "coil effectiveness"
#define $Proom$PhAir_vr 29 // "heat transfer coefficient"
#define $Proom$Pmdotat_vr 30 // "total air flow rate availbale from the fan"
#define $Proom$Pmdotwt_vr 31 // "total water flow rate availbale from the heat pump"
#define $Proom$ProhAir_vr 32 // "density of air"
#define $Proom$PvAir_vr 33 // "room air volume"
#define $Pwall$PTisurfInit_vr 34 // "initial internal surface temperature of the wall"
#define $Pwall$PTosurfInit_vr 35 // "initial external surface temperature of the wall"
#define $Pwall$PaWall_vr 36 // "wall area"
#define $Pwall$PcWall_vr 37 
#define $Pwall$Phi_vr 38 // "indoor heat transfer coefficient"
#define $Pwall$Pho_vr 39 // "outdoor heat transfer coefficient"
#define $Pwall$PlWall_vr 40 // "wall thickness"
#define $Pwall$Plambda_Wall_vr 41 
#define $Pwall$PrhoWall_vr 42 
#define $Proom$PTisurf_vr 43 // "wall internal surface temperature"
#define $Proom$Pfanspeed_vr 44 
#define $Proom$Pvalveopen_vr 45 
#define $Pwall$POAT_vr 46 
#define $Pwall$PRAT_vr 47 
#define $Pwall$PlambdaOut_vr 48 


// define initial state vector as vector of value references
#define STATES { $Proom$PRAT_vr, $Proom$Penergy_vr, $Pwall$PTisurf_vr, $Pwall$PTosurf_vr }
#define STATESDERIVATIVES { $P$DER$Proom$PRAT_vr, $P$DER$Proom$Penergy_vr, $P$DER$Pwall$PTisurf_vr, $P$DER$Pwall$PTosurf_vr }


// implementation of the Model Exchange functions
  extern void RoomHeating_OM_RH_setupDataStruc(DATA *data);
  #define fmu2_model_interface_setupDataStruc RoomHeating_OM_RH_setupDataStruc
  #include "fmu2_model_interface.c"

// Set values for all variables that define a start value
void setDefaultStartValues(ModelInstance *comp) {

comp->fmuData->modelData->realVarsData[0].attribute.start = 0;
comp->fmuData->modelData->realVarsData[1].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[2].attribute.start = 0;
comp->fmuData->modelData->realVarsData[3].attribute.start = 0;
comp->fmuData->modelData->realVarsData[4].attribute.start = 0;
comp->fmuData->modelData->realVarsData[5].attribute.start = 0;
comp->fmuData->modelData->realVarsData[6].attribute.start = 0;
comp->fmuData->modelData->realVarsData[7].attribute.start = 0;
comp->fmuData->modelData->realVarsData[8].attribute.start = 0;
comp->fmuData->modelData->realVarsData[9].attribute.start = 0;
comp->fmuData->modelData->realVarsData[10].attribute.start = 0;
comp->fmuData->modelData->realVarsData[11].attribute.start = 0.0;
comp->fmuData->modelData->realVarsData[12].attribute.start = 0;
comp->fmuData->modelData->realVarsData[13].attribute.start = 0;
comp->fmuData->modelData->realVarsData[14].attribute.start = 0;
comp->fmuData->modelData->realVarsData[15].attribute.start = 0;
comp->fmuData->modelData->realVarsData[16].attribute.start = 0.0001;
comp->fmuData->modelData->realVarsData[17].attribute.start = 5e-05;
comp->fmuData->modelData->realVarsData[18].attribute.start = 1e-05;
comp->fmuData->modelData->realVarsData[19].attribute.start = 0.0001;
comp->fmuData->modelData->realVarsData[20].attribute.start = 0;
comp->fmuData->modelData->realVarsData[21].attribute.start = 0;
comp->fmuData->modelData->realVarsData[22].attribute.start = 0;
comp->fmuData->modelData->realParameterData[0].attribute.start = 60.0;
comp->fmuData->modelData->realParameterData[1].attribute.start = 40.0;
comp->fmuData->modelData->realParameterData[2].attribute.start = 16.0;
comp->fmuData->modelData->realParameterData[3].attribute.start = 1012.0;
comp->fmuData->modelData->realParameterData[4].attribute.start = 4181.0;
comp->fmuData->modelData->realParameterData[5].attribute.start = 0.4;
comp->fmuData->modelData->realParameterData[6].attribute.start = 4.0;
comp->fmuData->modelData->realParameterData[7].attribute.start = 0.5;
comp->fmuData->modelData->realParameterData[8].attribute.start = 0.1;
comp->fmuData->modelData->realParameterData[9].attribute.start = 1.204;
comp->fmuData->modelData->realParameterData[10].attribute.start = 300.0;
comp->fmuData->modelData->realParameterData[11].attribute.start = 16.0;
comp->fmuData->modelData->realParameterData[12].attribute.start = 10.0;
comp->fmuData->modelData->realParameterData[13].attribute.start = 60.0;
comp->fmuData->modelData->realParameterData[14].attribute.start = 1360.71;
comp->fmuData->modelData->realParameterData[15].attribute.start = 8.33;
comp->fmuData->modelData->realParameterData[16].attribute.start = 33.33;
comp->fmuData->modelData->realParameterData[17].attribute.start = 0.03;
comp->fmuData->modelData->realParameterData[18].attribute.start = 0.1192;
comp->fmuData->modelData->realParameterData[19].attribute.start = 1312.0;
}
// Set values for all variables that define a start value
void setStartValues(ModelInstance *comp) {

  comp->fmuData->modelData->realVarsData[0].attribute.start =  comp->fmuData->localData[0]->realVars[0];
  comp->fmuData->modelData->realVarsData[1].attribute.start =  comp->fmuData->localData[0]->realVars[1];
  comp->fmuData->modelData->realVarsData[2].attribute.start =  comp->fmuData->localData[0]->realVars[2];
  comp->fmuData->modelData->realVarsData[3].attribute.start =  comp->fmuData->localData[0]->realVars[3];
  comp->fmuData->modelData->realVarsData[4].attribute.start =  comp->fmuData->localData[0]->realVars[4];
  comp->fmuData->modelData->realVarsData[5].attribute.start =  comp->fmuData->localData[0]->realVars[5];
  comp->fmuData->modelData->realVarsData[6].attribute.start =  comp->fmuData->localData[0]->realVars[6];
  comp->fmuData->modelData->realVarsData[7].attribute.start =  comp->fmuData->localData[0]->realVars[7];
  comp->fmuData->modelData->realVarsData[8].attribute.start =  comp->fmuData->localData[0]->realVars[8];
  comp->fmuData->modelData->realVarsData[9].attribute.start =  comp->fmuData->localData[0]->realVars[9];
  comp->fmuData->modelData->realVarsData[10].attribute.start =  comp->fmuData->localData[0]->realVars[10];
  comp->fmuData->modelData->realVarsData[11].attribute.start =  comp->fmuData->localData[0]->realVars[11];
  comp->fmuData->modelData->realVarsData[12].attribute.start =  comp->fmuData->localData[0]->realVars[12];
  comp->fmuData->modelData->realVarsData[13].attribute.start =  comp->fmuData->localData[0]->realVars[13];
  comp->fmuData->modelData->realVarsData[14].attribute.start =  comp->fmuData->localData[0]->realVars[14];
  comp->fmuData->modelData->realVarsData[15].attribute.start =  comp->fmuData->localData[0]->realVars[15];
  comp->fmuData->modelData->realVarsData[16].attribute.start =  comp->fmuData->localData[0]->realVars[16];
  comp->fmuData->modelData->realVarsData[17].attribute.start =  comp->fmuData->localData[0]->realVars[17];
  comp->fmuData->modelData->realVarsData[18].attribute.start =  comp->fmuData->localData[0]->realVars[18];
  comp->fmuData->modelData->realVarsData[19].attribute.start =  comp->fmuData->localData[0]->realVars[19];
  comp->fmuData->modelData->realVarsData[20].attribute.start =  comp->fmuData->localData[0]->realVars[20];
  comp->fmuData->modelData->realVarsData[21].attribute.start =  comp->fmuData->localData[0]->realVars[21];
  comp->fmuData->modelData->realVarsData[22].attribute.start =  comp->fmuData->localData[0]->realVars[22];
comp->fmuData->modelData->realParameterData[0].attribute.start = comp->fmuData->simulationInfo->realParameter[0];
comp->fmuData->modelData->realParameterData[1].attribute.start = comp->fmuData->simulationInfo->realParameter[1];
comp->fmuData->modelData->realParameterData[2].attribute.start = comp->fmuData->simulationInfo->realParameter[2];
comp->fmuData->modelData->realParameterData[3].attribute.start = comp->fmuData->simulationInfo->realParameter[3];
comp->fmuData->modelData->realParameterData[4].attribute.start = comp->fmuData->simulationInfo->realParameter[4];
comp->fmuData->modelData->realParameterData[5].attribute.start = comp->fmuData->simulationInfo->realParameter[5];
comp->fmuData->modelData->realParameterData[6].attribute.start = comp->fmuData->simulationInfo->realParameter[6];
comp->fmuData->modelData->realParameterData[7].attribute.start = comp->fmuData->simulationInfo->realParameter[7];
comp->fmuData->modelData->realParameterData[8].attribute.start = comp->fmuData->simulationInfo->realParameter[8];
comp->fmuData->modelData->realParameterData[9].attribute.start = comp->fmuData->simulationInfo->realParameter[9];
comp->fmuData->modelData->realParameterData[10].attribute.start = comp->fmuData->simulationInfo->realParameter[10];
comp->fmuData->modelData->realParameterData[11].attribute.start = comp->fmuData->simulationInfo->realParameter[11];
comp->fmuData->modelData->realParameterData[12].attribute.start = comp->fmuData->simulationInfo->realParameter[12];
comp->fmuData->modelData->realParameterData[13].attribute.start = comp->fmuData->simulationInfo->realParameter[13];
comp->fmuData->modelData->realParameterData[14].attribute.start = comp->fmuData->simulationInfo->realParameter[14];
comp->fmuData->modelData->realParameterData[15].attribute.start = comp->fmuData->simulationInfo->realParameter[15];
comp->fmuData->modelData->realParameterData[16].attribute.start = comp->fmuData->simulationInfo->realParameter[16];
comp->fmuData->modelData->realParameterData[17].attribute.start = comp->fmuData->simulationInfo->realParameter[17];
comp->fmuData->modelData->realParameterData[18].attribute.start = comp->fmuData->simulationInfo->realParameter[18];
comp->fmuData->modelData->realParameterData[19].attribute.start = comp->fmuData->simulationInfo->realParameter[19];
}
  // Used to set the next time event, if any.
  void eventUpdate(ModelInstance* comp, fmi2EventInfo* eventInfo) {
  }
  
  fmi2Real getReal(ModelInstance* comp, const fmi2ValueReference vr) {
    switch (vr) {
        case $Proom$PRAT_vr : return comp->fmuData->localData[0]->realVars[0]; break;
        case $Proom$Penergy_vr : return comp->fmuData->localData[0]->realVars[1]; break;
        case $Pwall$PTisurf_vr : return comp->fmuData->localData[0]->realVars[2]; break;
        case $Pwall$PTosurf_vr : return comp->fmuData->localData[0]->realVars[3]; break;
        case $P$DER$Proom$PRAT_vr : return comp->fmuData->localData[0]->realVars[4]; break;
        case $P$DER$Proom$Penergy_vr : return comp->fmuData->localData[0]->realVars[5]; break;
        case $P$DER$Pwall$PTisurf_vr : return comp->fmuData->localData[0]->realVars[6]; break;
        case $P$DER$Pwall$PTosurf_vr : return comp->fmuData->localData[0]->realVars[7]; break;
        case $POAT_vr : return comp->fmuData->localData[0]->realVars[8]; break;
        case $PRAT_vr : return comp->fmuData->localData[0]->realVars[9]; break;
        case $Pfanspeed_vr : return comp->fmuData->localData[0]->realVars[10]; break;
        case $Proom$PDT_vr : return comp->fmuData->localData[0]->realVars[11]; break;
        case $Proom$PEWT_vr : return comp->fmuData->localData[0]->realVars[12]; break;
        case $Proom$PQin_vr : return comp->fmuData->localData[0]->realVars[13]; break;
        case $Proom$PQout_vr : return comp->fmuData->localData[0]->realVars[14]; break;
        case $Proom$PSAT_vr : return comp->fmuData->localData[0]->realVars[15]; break;
        case $Proom$Pfs_vr : return comp->fmuData->localData[0]->realVars[16]; break;
        case $Proom$Pmdota_vr : return comp->fmuData->localData[0]->realVars[17]; break;
        case $Proom$Pmdotw_vr : return comp->fmuData->localData[0]->realVars[18]; break;
        case $Proom$Pvo_vr : return comp->fmuData->localData[0]->realVars[19]; break;
        case $Pvalveopen_vr : return comp->fmuData->localData[0]->realVars[20]; break;
        case $Pwall$PC_vr : return comp->fmuData->localData[0]->realVars[21]; break;
        case $Pwall$PR_vr : return comp->fmuData->localData[0]->realVars[22]; break;
        case $Proom$PAwall_vr : return comp->fmuData->simulationInfo->realParameter[0]; break;
        case $Proom$PLWT_vr : return comp->fmuData->simulationInfo->realParameter[1]; break;
        case $Proom$PRATinit_vr : return comp->fmuData->simulationInfo->realParameter[2]; break;
        case $Proom$PcAir_vr : return comp->fmuData->simulationInfo->realParameter[3]; break;
        case $Proom$PcWater_vr : return comp->fmuData->simulationInfo->realParameter[4]; break;
        case $Proom$Peps_vr : return comp->fmuData->simulationInfo->realParameter[5]; break;
        case $Proom$PhAir_vr : return comp->fmuData->simulationInfo->realParameter[6]; break;
        case $Proom$Pmdotat_vr : return comp->fmuData->simulationInfo->realParameter[7]; break;
        case $Proom$Pmdotwt_vr : return comp->fmuData->simulationInfo->realParameter[8]; break;
        case $Proom$ProhAir_vr : return comp->fmuData->simulationInfo->realParameter[9]; break;
        case $Proom$PvAir_vr : return comp->fmuData->simulationInfo->realParameter[10]; break;
        case $Pwall$PTisurfInit_vr : return comp->fmuData->simulationInfo->realParameter[11]; break;
        case $Pwall$PTosurfInit_vr : return comp->fmuData->simulationInfo->realParameter[12]; break;
        case $Pwall$PaWall_vr : return comp->fmuData->simulationInfo->realParameter[13]; break;
        case $Pwall$PcWall_vr : return comp->fmuData->simulationInfo->realParameter[14]; break;
        case $Pwall$Phi_vr : return comp->fmuData->simulationInfo->realParameter[15]; break;
        case $Pwall$Pho_vr : return comp->fmuData->simulationInfo->realParameter[16]; break;
        case $Pwall$PlWall_vr : return comp->fmuData->simulationInfo->realParameter[17]; break;
        case $Pwall$Plambda_Wall_vr : return comp->fmuData->simulationInfo->realParameter[18]; break;
        case $Pwall$PrhoWall_vr : return comp->fmuData->simulationInfo->realParameter[19]; break;
        case $Proom$PTisurf_vr : return getReal(comp, $Pwall$PTisurf_vr); break;
        case $Proom$Pfanspeed_vr : return getReal(comp, $Pfanspeed_vr); break;
        case $Proom$Pvalveopen_vr : return getReal(comp, $Pvalveopen_vr); break;
        case $Pwall$POAT_vr : return getReal(comp, $POAT_vr); break;
        case $Pwall$PRAT_vr : return getReal(comp, $Proom$PRAT_vr); break;
        case $Pwall$PlambdaOut_vr : return getReal(comp, $Pwall$Plambda_Wall_vr); break;
        default:
            return 0;
    }
  }
  
  fmi2Status setReal(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Real value) {
    switch (vr) {
        case $Proom$PRAT_vr : comp->fmuData->localData[0]->realVars[0] = value; break;
        case $Proom$Penergy_vr : comp->fmuData->localData[0]->realVars[1] = value; break;
        case $Pwall$PTisurf_vr : comp->fmuData->localData[0]->realVars[2] = value; break;
        case $Pwall$PTosurf_vr : comp->fmuData->localData[0]->realVars[3] = value; break;
        case $P$DER$Proom$PRAT_vr : comp->fmuData->localData[0]->realVars[4] = value; break;
        case $P$DER$Proom$Penergy_vr : comp->fmuData->localData[0]->realVars[5] = value; break;
        case $P$DER$Pwall$PTisurf_vr : comp->fmuData->localData[0]->realVars[6] = value; break;
        case $P$DER$Pwall$PTosurf_vr : comp->fmuData->localData[0]->realVars[7] = value; break;
        case $POAT_vr : comp->fmuData->localData[0]->realVars[8] = value; break;
        case $PRAT_vr : comp->fmuData->localData[0]->realVars[9] = value; break;
        case $Pfanspeed_vr : comp->fmuData->localData[0]->realVars[10] = value; break;
        case $Proom$PDT_vr : comp->fmuData->localData[0]->realVars[11] = value; break;
        case $Proom$PEWT_vr : comp->fmuData->localData[0]->realVars[12] = value; break;
        case $Proom$PQin_vr : comp->fmuData->localData[0]->realVars[13] = value; break;
        case $Proom$PQout_vr : comp->fmuData->localData[0]->realVars[14] = value; break;
        case $Proom$PSAT_vr : comp->fmuData->localData[0]->realVars[15] = value; break;
        case $Proom$Pfs_vr : comp->fmuData->localData[0]->realVars[16] = value; break;
        case $Proom$Pmdota_vr : comp->fmuData->localData[0]->realVars[17] = value; break;
        case $Proom$Pmdotw_vr : comp->fmuData->localData[0]->realVars[18] = value; break;
        case $Proom$Pvo_vr : comp->fmuData->localData[0]->realVars[19] = value; break;
        case $Pvalveopen_vr : comp->fmuData->localData[0]->realVars[20] = value; break;
        case $Pwall$PC_vr : comp->fmuData->localData[0]->realVars[21] = value; break;
        case $Pwall$PR_vr : comp->fmuData->localData[0]->realVars[22] = value; break;
        case $Proom$PAwall_vr : comp->fmuData->simulationInfo->realParameter[0] = value; break;
        case $Proom$PLWT_vr : comp->fmuData->simulationInfo->realParameter[1] = value; break;
        case $Proom$PRATinit_vr : comp->fmuData->simulationInfo->realParameter[2] = value; break;
        case $Proom$PcAir_vr : comp->fmuData->simulationInfo->realParameter[3] = value; break;
        case $Proom$PcWater_vr : comp->fmuData->simulationInfo->realParameter[4] = value; break;
        case $Proom$Peps_vr : comp->fmuData->simulationInfo->realParameter[5] = value; break;
        case $Proom$PhAir_vr : comp->fmuData->simulationInfo->realParameter[6] = value; break;
        case $Proom$Pmdotat_vr : comp->fmuData->simulationInfo->realParameter[7] = value; break;
        case $Proom$Pmdotwt_vr : comp->fmuData->simulationInfo->realParameter[8] = value; break;
        case $Proom$ProhAir_vr : comp->fmuData->simulationInfo->realParameter[9] = value; break;
        case $Proom$PvAir_vr : comp->fmuData->simulationInfo->realParameter[10] = value; break;
        case $Pwall$PTisurfInit_vr : comp->fmuData->simulationInfo->realParameter[11] = value; break;
        case $Pwall$PTosurfInit_vr : comp->fmuData->simulationInfo->realParameter[12] = value; break;
        case $Pwall$PaWall_vr : comp->fmuData->simulationInfo->realParameter[13] = value; break;
        case $Pwall$PcWall_vr : comp->fmuData->simulationInfo->realParameter[14] = value; break;
        case $Pwall$Phi_vr : comp->fmuData->simulationInfo->realParameter[15] = value; break;
        case $Pwall$Pho_vr : comp->fmuData->simulationInfo->realParameter[16] = value; break;
        case $Pwall$PlWall_vr : comp->fmuData->simulationInfo->realParameter[17] = value; break;
        case $Pwall$Plambda_Wall_vr : comp->fmuData->simulationInfo->realParameter[18] = value; break;
        case $Pwall$PrhoWall_vr : comp->fmuData->simulationInfo->realParameter[19] = value; break;
        case $Proom$PTisurf_vr : return setReal(comp, $Pwall$PTisurf_vr, value); break;
        case $Proom$Pfanspeed_vr : return setReal(comp, $Pfanspeed_vr, value); break;
        case $Proom$Pvalveopen_vr : return setReal(comp, $Pvalveopen_vr, value); break;
        case $Pwall$POAT_vr : return setReal(comp, $POAT_vr, value); break;
        case $Pwall$PRAT_vr : return setReal(comp, $Proom$PRAT_vr, value); break;
        case $Pwall$PlambdaOut_vr : return setReal(comp, $Pwall$Plambda_Wall_vr, value); break;
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
        default:
            return fmi2False;
    }
  }
  
  fmi2Status setBoolean(ModelInstance* comp, const fmi2ValueReference vr, const fmi2Boolean value) {
    switch (vr) {
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

