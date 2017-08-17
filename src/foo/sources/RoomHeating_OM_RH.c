/* Main Simulation File */
#include "RoomHeating_OM_RH_model.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int RoomHeating_OM_RH_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->localData[0]->realVars[8] /* OAT variable */ = data->simulationInfo->inputVars[0];
  data->localData[0]->realVars[10] /* fanspeed variable */ = data->simulationInfo->inputVars[1];
  data->localData[0]->realVars[20] /* valveopen variable */ = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[8].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[10].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[20].attribute.start;
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[8].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[10].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[20].attribute.start = data->simulationInfo->inputVars[2];
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[8].info.name;
  names[1] = (char *) data->modelData->realVarsData[10].info.name;
  names[2] = (char *) data->modelData->realVarsData[20].info.name;
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = data->localData[0]->realVars[9] /* RAT variable */;
  
  TRACE_POP
  return 0;
}


/*
 equation index: 21
 type: SIMPLE_ASSIGN
 room._Qout = room.hAir * room.Awall * (room.RAT - wall.Tisurf)
 */
void RoomHeating_OM_RH_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->realVars[14] /* room._Qout variable */ = (data->simulationInfo->realParameter[6] /* room._hAir PARAM */) * ((data->simulationInfo->realParameter[0] /* room._Awall PARAM */) * (data->localData[0]->realVars[0] /* room._RAT STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */));
  TRACE_POP
}
/*
 equation index: 22
 type: SIMPLE_ASSIGN
 room._fs = if fanspeed > 0.0 then fanspeed else 0.0001
 */
void RoomHeating_OM_RH_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  modelica_boolean tmp14;
  RELATIONHYSTERESIS(tmp14, data->localData[0]->realVars[10] /* fanspeed variable */, 0.0, 1, Greater);
  data->localData[0]->realVars[16] /* room._fs variable */ = (tmp14?data->localData[0]->realVars[10] /* fanspeed variable */:0.0001);
  TRACE_POP
}
/*
 equation index: 23
 type: SIMPLE_ASSIGN
 room._Qin = room.eps * room.mdotat * room.fs * room.cAir * (room.LWT - room.RAT)
 */
void RoomHeating_OM_RH_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->realVars[13] /* room._Qin variable */ = (data->simulationInfo->realParameter[5] /* room._eps PARAM */) * ((data->simulationInfo->realParameter[7] /* room._mdotat PARAM */) * ((data->localData[0]->realVars[16] /* room._fs variable */) * ((data->simulationInfo->realParameter[3] /* room._cAir PARAM */) * (data->simulationInfo->realParameter[1] /* room._LWT PARAM */ - data->localData[0]->realVars[0] /* room._RAT STATE(1) */))));
  TRACE_POP
}
/*
 equation index: 24
 type: SIMPLE_ASSIGN
 room._DT = room.Qin - room.Qout
 */
void RoomHeating_OM_RH_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->localData[0]->realVars[11] /* room._DT variable */ = data->localData[0]->realVars[13] /* room._Qin variable */ - data->localData[0]->realVars[14] /* room._Qout variable */;
  TRACE_POP
}
/*
 equation index: 25
 type: SIMPLE_ASSIGN
 der(room._RAT) = DIVISION(room.DT, room.vAir * room.cAir * room.rohAir)
 */
void RoomHeating_OM_RH_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->localData[0]->realVars[4] /* der(room._RAT) STATE_DER */ = DIVISION_SIM(data->localData[0]->realVars[11] /* room._DT variable */,((data->simulationInfo->realParameter[10] /* room._vAir PARAM */) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */)) * (data->simulationInfo->realParameter[9] /* room._rohAir PARAM */),"room.vAir * room.cAir * room.rohAir",equationIndexes);
  TRACE_POP
}
/*
 equation index: 26
 type: SIMPLE_ASSIGN
 der(room._energy) = room.Qin
 */
void RoomHeating_OM_RH_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->realVars[5] /* der(room._energy) STATE_DER */ = data->localData[0]->realVars[13] /* room._Qin variable */;
  TRACE_POP
}
/*
 equation index: 27
 type: SIMPLE_ASSIGN
 room._mdota = room.fs * room.mdotat
 */
void RoomHeating_OM_RH_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[17] /* room._mdota variable */ = (data->localData[0]->realVars[16] /* room._fs variable */) * (data->simulationInfo->realParameter[7] /* room._mdotat PARAM */);
  TRACE_POP
}
/*
 equation index: 28
 type: SIMPLE_ASSIGN
 room._SAT = DIVISION(room.Qin - (-room.RAT) * room.cAir * room.mdota, room.mdota * room.cAir)
 */
void RoomHeating_OM_RH_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->realVars[15] /* room._SAT variable */ = DIVISION_SIM(data->localData[0]->realVars[13] /* room._Qin variable */ - ((((-data->localData[0]->realVars[0] /* room._RAT STATE(1) */)) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */)) * (data->localData[0]->realVars[17] /* room._mdota variable */)),(data->localData[0]->realVars[17] /* room._mdota variable */) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */),"room.mdota * room.cAir",equationIndexes);
  TRACE_POP
}
/*
 equation index: 29
 type: SIMPLE_ASSIGN
 room._vo = if valveopen > 0.0 then valveopen else 0.0001
 */
void RoomHeating_OM_RH_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  modelica_boolean tmp15;
  RELATIONHYSTERESIS(tmp15, data->localData[0]->realVars[20] /* valveopen variable */, 0.0, 0, Greater);
  data->localData[0]->realVars[19] /* room._vo variable */ = (tmp15?data->localData[0]->realVars[20] /* valveopen variable */:0.0001);
  TRACE_POP
}
/*
 equation index: 30
 type: SIMPLE_ASSIGN
 room._EWT = DIVISION(room.LWT * room.cWater * room.mdotwt * room.vo - room.Qin, room.vo * room.mdotwt * room.cWater)
 */
void RoomHeating_OM_RH_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->localData[0]->realVars[12] /* room._EWT variable */ = DIVISION_SIM((((data->simulationInfo->realParameter[1] /* room._LWT PARAM */) * (data->simulationInfo->realParameter[4] /* room._cWater PARAM */)) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */)) * (data->localData[0]->realVars[19] /* room._vo variable */) - data->localData[0]->realVars[13] /* room._Qin variable */,((data->localData[0]->realVars[19] /* room._vo variable */) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */)) * (data->simulationInfo->realParameter[4] /* room._cWater PARAM */),"room.vo * room.mdotwt * room.cWater",equationIndexes);
  TRACE_POP
}
/*
 equation index: 31
 type: SIMPLE_ASSIGN
 room._mdotw = room.vo * room.mdotwt
 */
void RoomHeating_OM_RH_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  data->localData[0]->realVars[18] /* room._mdotw variable */ = (data->localData[0]->realVars[19] /* room._vo variable */) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */);
  TRACE_POP
}
/*
 equation index: 32
 type: SIMPLE_ASSIGN
 der(wall._Tosurf) = DIVISION(wall.ho * wall.aWall * (OAT - wall.Tosurf) + DIVISION(wall.Tisurf - wall.Tosurf, wall.R), wall.C)
 */
void RoomHeating_OM_RH_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  data->localData[0]->realVars[7] /* der(wall._Tosurf) STATE_DER */ = DIVISION_SIM((data->simulationInfo->realParameter[16] /* wall._ho PARAM */) * ((data->simulationInfo->realParameter[13] /* wall._aWall PARAM */) * (data->localData[0]->realVars[8] /* OAT variable */ - data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */)) + DIVISION_SIM(data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */ - data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */,data->localData[0]->realVars[22] /* wall._R variable */,"wall.R",equationIndexes),data->localData[0]->realVars[21] /* wall._C variable */,"wall.C",equationIndexes);
  TRACE_POP
}
/*
 equation index: 33
 type: SIMPLE_ASSIGN
 der(wall._Tisurf) = DIVISION(wall.hi * wall.aWall * (room.RAT - wall.Tisurf) + DIVISION(wall.Tosurf - wall.Tisurf, wall.R), wall.C)
 */
void RoomHeating_OM_RH_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  data->localData[0]->realVars[6] /* der(wall._Tisurf) STATE_DER */ = DIVISION_SIM((data->simulationInfo->realParameter[15] /* wall._hi PARAM */) * ((data->simulationInfo->realParameter[13] /* wall._aWall PARAM */) * (data->localData[0]->realVars[0] /* room._RAT STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */)) + DIVISION_SIM(data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */,data->localData[0]->realVars[22] /* wall._R variable */,"wall.R",equationIndexes),data->localData[0]->realVars[21] /* wall._C variable */,"wall.C",equationIndexes);
  TRACE_POP
}
/*
 equation index: 34
 type: SIMPLE_ASSIGN
 RAT = room.RAT
 */
void RoomHeating_OM_RH_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  data->localData[0]->realVars[9] /* RAT variable */ = data->localData[0]->realVars[0] /* room._RAT STATE(1) */;
  TRACE_POP
}
/*
 equation index: 36
 type: ALGORITHM
 
   assert(room.EWT - room.LWT <= 5.0, "UTRC-FCU-001: Difference between EWT and LWT for HP should be less than 5 C");
 */
void RoomHeating_OM_RH_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  modelica_boolean tmp16;
  static const MMC_DEFSTRINGLIT(tmp17,75,"UTRC-FCU-001: Difference between EWT and LWT for HP should be less than 5 C");
  static int tmp18 = 0;
  if(!tmp18)
  {
    tmp16 = LessEq(data->localData[0]->realVars[12] /* room._EWT variable */ - data->simulationInfo->realParameter[1] /* room._LWT PARAM */,5.0);
    if(!tmp16)
    {
      {
        FILE_INFO info = {"/var/lib/hudson/jobs/OpenModelica_BUILD/workspace/OpenModelica/testsuite/special/FmuExportCrossCompile/RoomHeating_OM.mo",70,5,70,130,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nroom.EWT - room.LWT <= 5.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp17)));
      }
      tmp18 = 1;
    }
  }
  TRACE_POP
}
/*
 equation index: 35
 type: ALGORITHM
 
   assert(fanspeed >= 0.01, "UTRC-FCU-002: FCU air damper should be opened at least 0.10.");
 */
void RoomHeating_OM_RH_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  modelica_boolean tmp19;
  static const MMC_DEFSTRINGLIT(tmp20,60,"UTRC-FCU-002: FCU air damper should be opened at least 0.10.");
  static int tmp21 = 0;
  if(!tmp21)
  {
    tmp19 = GreaterEq(data->localData[0]->realVars[10] /* fanspeed variable */,0.01);
    if(!tmp19)
    {
      {
        FILE_INFO info = {"/var/lib/hudson/jobs/OpenModelica_BUILD/workspace/OpenModelica/testsuite/special/FmuExportCrossCompile/RoomHeating_OM.mo",69,5,69,117,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nfanspeed >= 0.01", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp20)));
      }
      tmp21 = 1;
    }
  }
  TRACE_POP
}


int RoomHeating_OM_RH_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  RoomHeating_OM_RH_functionLocalKnownVars(data, threadData);
  RoomHeating_OM_RH_eqFunction_21(data, threadData);

  RoomHeating_OM_RH_eqFunction_22(data, threadData);

  RoomHeating_OM_RH_eqFunction_23(data, threadData);

  RoomHeating_OM_RH_eqFunction_24(data, threadData);

  RoomHeating_OM_RH_eqFunction_25(data, threadData);

  RoomHeating_OM_RH_eqFunction_26(data, threadData);

  RoomHeating_OM_RH_eqFunction_27(data, threadData);

  RoomHeating_OM_RH_eqFunction_28(data, threadData);

  RoomHeating_OM_RH_eqFunction_29(data, threadData);

  RoomHeating_OM_RH_eqFunction_30(data, threadData);

  RoomHeating_OM_RH_eqFunction_31(data, threadData);

  RoomHeating_OM_RH_eqFunction_32(data, threadData);

  RoomHeating_OM_RH_eqFunction_33(data, threadData);

  RoomHeating_OM_RH_eqFunction_34(data, threadData);

  RoomHeating_OM_RH_eqFunction_36(data, threadData);

  RoomHeating_OM_RH_eqFunction_35(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int RoomHeating_OM_RH_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_symEulerUpdate(DATA *data, modelica_real dt)
{
  return -1;
}



/* forwarded equations */
extern void RoomHeating_OM_RH_eqFunction_21(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_22(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_23(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_24(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_25(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_26(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_32(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_33(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  RoomHeating_OM_RH_eqFunction_21(data, threadData);

  RoomHeating_OM_RH_eqFunction_22(data, threadData);

  RoomHeating_OM_RH_eqFunction_23(data, threadData);

  RoomHeating_OM_RH_eqFunction_24(data, threadData);

  RoomHeating_OM_RH_eqFunction_25(data, threadData);

  RoomHeating_OM_RH_eqFunction_26(data, threadData);

  RoomHeating_OM_RH_eqFunction_32(data, threadData);

  RoomHeating_OM_RH_eqFunction_33(data, threadData);
}

int RoomHeating_OM_RH_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  RoomHeating_OM_RH_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "RoomHeating_OM_RH_12jac.h"
#include "RoomHeating_OM_RH_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks RoomHeating_OM_RH_callback = {
   NULL,
   NULL,
   NULL,
   RoomHeating_OM_RH_callExternalObjectDestructors,
   NULL,
   NULL,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   RoomHeating_OM_RH_initializeStateSets,
   #else
   NULL,
   #endif
   RoomHeating_OM_RH_initializeDAEmodeData,
   RoomHeating_OM_RH_functionODE,
   RoomHeating_OM_RH_functionAlgebraics,
   RoomHeating_OM_RH_functionDAE,
   RoomHeating_OM_RH_functionLocalKnownVars,
   RoomHeating_OM_RH_input_function,
   RoomHeating_OM_RH_input_function_init,
   RoomHeating_OM_RH_input_function_updateStartValues,
   RoomHeating_OM_RH_output_function,
   RoomHeating_OM_RH_function_storeDelayed,
   RoomHeating_OM_RH_updateBoundVariableAttributes,
   0 /* useHomotopy */,
   RoomHeating_OM_RH_functionInitialEquations,
   RoomHeating_OM_RH_functionInitialEquations_lambda0,
   RoomHeating_OM_RH_functionRemovedInitialEquations,
   RoomHeating_OM_RH_updateBoundParameters,
   RoomHeating_OM_RH_checkForAsserts,
   RoomHeating_OM_RH_function_ZeroCrossingsEquations,
   RoomHeating_OM_RH_function_ZeroCrossings,
   RoomHeating_OM_RH_function_updateRelations,
   RoomHeating_OM_RH_checkForDiscreteChanges,
   RoomHeating_OM_RH_zeroCrossingDescription,
   RoomHeating_OM_RH_relationDescription,
   RoomHeating_OM_RH_function_initSample,
   RoomHeating_OM_RH_INDEX_JAC_A,
   RoomHeating_OM_RH_INDEX_JAC_B,
   RoomHeating_OM_RH_INDEX_JAC_C,
   RoomHeating_OM_RH_INDEX_JAC_D,
   RoomHeating_OM_RH_initialAnalyticJacobianA,
   RoomHeating_OM_RH_initialAnalyticJacobianB,
   RoomHeating_OM_RH_initialAnalyticJacobianC,
   RoomHeating_OM_RH_initialAnalyticJacobianD,
   RoomHeating_OM_RH_functionJacA_column,
   RoomHeating_OM_RH_functionJacB_column,
   RoomHeating_OM_RH_functionJacC_column,
   RoomHeating_OM_RH_functionJacD_column,
   RoomHeating_OM_RH_linear_model_frame,
   RoomHeating_OM_RH_linear_model_datarecovery_frame,
   RoomHeating_OM_RH_mayer,
   RoomHeating_OM_RH_lagrange,
   RoomHeating_OM_RH_pickUpBoundsForInputsInOptimization,
   RoomHeating_OM_RH_setInputData,
   RoomHeating_OM_RH_getTimeGrid,
   RoomHeating_OM_RH_symEulerUpdate,
   RoomHeating_OM_RH_function_initSynchronous,
   RoomHeating_OM_RH_function_updateSynchronous,
   RoomHeating_OM_RH_function_equationsSynchronous,
   RoomHeating_OM_RH_read_input_fmu
   #ifdef FMU_EXPERIMENTAL
   ,RoomHeating_OM_RH_functionODE_Partial
   ,RoomHeating_OM_RH_functionFMIJacobian
   #endif
   ,RoomHeating_OM_RH_inputNames


};

void RoomHeating_OM_RH_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &RoomHeating_OM_RH_callback;
  data->modelData->modelName = "RoomHeating_OM.RH";
  data->modelData->modelFilePrefix = "RoomHeating_OM_RH";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/var/lib/hudson/jobs/OpenModelica_BUILD/workspace/OpenModelica/testsuite/special/FmuExportCrossCompile";
  data->modelData->modelGUID = "{e0da2bdb-ec76-42d1-bd09-a8db9cb3c63a}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData =
  #if defined(OMC_MINIMAL_METADATA)
    NULL;
  #else
  #include "RoomHeating_OM_RH_info.c"
  #endif
  ;
  
  data->modelData->nStates = 4;
  data->modelData->nVariablesReal = 23;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 20;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 3;
  data->modelData->nOutputVars = 1;
  
  data->modelData->nAliasReal = 6;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 2;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 2;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.fileName = "RoomHeating_OM_RH_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 40;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 4;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
}

#ifdef __cplusplus
}
#endif

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

