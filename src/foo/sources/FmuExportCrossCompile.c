/* Main Simulation File */
#include "FmuExportCrossCompile_model.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int FmuExportCrossCompile_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
 equation index: 8
 type: SIMPLE_ASSIGN
 $whenCondition1 = h <= 0.0
 */
void FmuExportCrossCompile_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  modelica_boolean tmp2;
  RELATIONHYSTERESIS(tmp2, data->localData[0]->realVars[0] /* h STATE(1,v) */, 0.0, 0, LessEq);
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = tmp2;
  TRACE_POP
}
/*
 equation index: 9
 type: WHEN
 
 when {$whenCondition1} then
   v_new = (-e) * pre(v);
 end when;
 */
void FmuExportCrossCompile_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[4] /* v_new DISCRETE */ = ((-data->simulationInfo->realParameter[0] /* e PARAM */)) * (data->simulationInfo->realVarsPre[1] /* v STATE(1) */);
  }
  TRACE_POP
}
/*
 equation index: 10
 type: SIMPLE_ASSIGN
 der(h) = v
 */
void FmuExportCrossCompile_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[2] /* der(h) STATE_DER */ = data->localData[0]->realVars[1] /* v STATE(1) */;
  TRACE_POP
}
/*
 equation index: 11
 type: SIMPLE_ASSIGN
 der(v) = -g
 */
void FmuExportCrossCompile_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[3] /* der(v) STATE_DER */ = (-data->simulationInfo->realParameter[1] /* g PARAM */);
  TRACE_POP
}
/*
 equation index: 12
 type: WHEN
 
 when {$whenCondition1} then
   reinit(v,  v_new);
 end when;
 */
void FmuExportCrossCompile_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[1] /* v STATE(1) */ = data->localData[0]->realVars[4] /* v_new DISCRETE */;
    infoStreamPrint(LOG_EVENTS, 0, "reinit v = %g", data->localData[0]->realVars[1] /* v STATE(1) */);
    data->simulationInfo->needToIterate = 1;
  }
  TRACE_POP
}


int FmuExportCrossCompile_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  FmuExportCrossCompile_functionLocalKnownVars(data, threadData);
  FmuExportCrossCompile_eqFunction_8(data, threadData);

  FmuExportCrossCompile_eqFunction_9(data, threadData);

  FmuExportCrossCompile_eqFunction_10(data, threadData);

  FmuExportCrossCompile_eqFunction_11(data, threadData);

  FmuExportCrossCompile_eqFunction_12(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int FmuExportCrossCompile_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_symEulerUpdate(DATA *data, modelica_real dt)
{
  return -1;
}



/* forwarded equations */
extern void FmuExportCrossCompile_eqFunction_10(DATA* data, threadData_t *threadData);
extern void FmuExportCrossCompile_eqFunction_11(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  FmuExportCrossCompile_eqFunction_10(data, threadData);

  FmuExportCrossCompile_eqFunction_11(data, threadData);
}

int FmuExportCrossCompile_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  FmuExportCrossCompile_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "FmuExportCrossCompile_12jac.h"
#include "FmuExportCrossCompile_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks FmuExportCrossCompile_callback = {
   NULL,
   NULL,
   NULL,
   FmuExportCrossCompile_callExternalObjectDestructors,
   NULL,
   NULL,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   FmuExportCrossCompile_initializeStateSets,
   #else
   NULL,
   #endif
   FmuExportCrossCompile_initializeDAEmodeData,
   FmuExportCrossCompile_functionODE,
   FmuExportCrossCompile_functionAlgebraics,
   FmuExportCrossCompile_functionDAE,
   FmuExportCrossCompile_functionLocalKnownVars,
   FmuExportCrossCompile_input_function,
   FmuExportCrossCompile_input_function_init,
   FmuExportCrossCompile_input_function_updateStartValues,
   FmuExportCrossCompile_output_function,
   FmuExportCrossCompile_function_storeDelayed,
   FmuExportCrossCompile_updateBoundVariableAttributes,
   0 /* useHomotopy */,
   FmuExportCrossCompile_functionInitialEquations,
   FmuExportCrossCompile_functionInitialEquations_lambda0,
   FmuExportCrossCompile_functionRemovedInitialEquations,
   FmuExportCrossCompile_updateBoundParameters,
   FmuExportCrossCompile_checkForAsserts,
   FmuExportCrossCompile_function_ZeroCrossingsEquations,
   FmuExportCrossCompile_function_ZeroCrossings,
   FmuExportCrossCompile_function_updateRelations,
   FmuExportCrossCompile_checkForDiscreteChanges,
   FmuExportCrossCompile_zeroCrossingDescription,
   FmuExportCrossCompile_relationDescription,
   FmuExportCrossCompile_function_initSample,
   FmuExportCrossCompile_INDEX_JAC_A,
   FmuExportCrossCompile_INDEX_JAC_B,
   FmuExportCrossCompile_INDEX_JAC_C,
   FmuExportCrossCompile_INDEX_JAC_D,
   FmuExportCrossCompile_initialAnalyticJacobianA,
   FmuExportCrossCompile_initialAnalyticJacobianB,
   FmuExportCrossCompile_initialAnalyticJacobianC,
   FmuExportCrossCompile_initialAnalyticJacobianD,
   FmuExportCrossCompile_functionJacA_column,
   FmuExportCrossCompile_functionJacB_column,
   FmuExportCrossCompile_functionJacC_column,
   FmuExportCrossCompile_functionJacD_column,
   FmuExportCrossCompile_linear_model_frame,
   FmuExportCrossCompile_linear_model_datarecovery_frame,
   FmuExportCrossCompile_mayer,
   FmuExportCrossCompile_lagrange,
   FmuExportCrossCompile_pickUpBoundsForInputsInOptimization,
   FmuExportCrossCompile_setInputData,
   FmuExportCrossCompile_getTimeGrid,
   FmuExportCrossCompile_symEulerUpdate,
   FmuExportCrossCompile_function_initSynchronous,
   FmuExportCrossCompile_function_updateSynchronous,
   FmuExportCrossCompile_function_equationsSynchronous,
   FmuExportCrossCompile_read_input_fmu
   #ifdef FMU_EXPERIMENTAL
   ,FmuExportCrossCompile_functionODE_Partial
   ,FmuExportCrossCompile_functionFMIJacobian
   #endif
   ,FmuExportCrossCompile_inputNames


};

void FmuExportCrossCompile_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &FmuExportCrossCompile_callback;
  data->modelData->modelName = "FmuExportCrossCompile";
  data->modelData->modelFilePrefix = "FmuExportCrossCompile";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "";
  data->modelData->modelGUID = "{5a4fa8dc-cd97-434c-ab30-e352e643f853}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData =
  #if defined(OMC_MINIMAL_METADATA)
    NULL;
  #else
  #include "FmuExportCrossCompile_info.c"
  #endif
  ;
  
  data->modelData->nStates = 2;
  data->modelData->nVariablesReal = 5;
  data->modelData->nDiscreteReal = 1;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 1;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 2;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 1;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.fileName = "FmuExportCrossCompile_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 13;
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

