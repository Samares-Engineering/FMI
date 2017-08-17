/* Main Simulation File */
#include "WaterTank_Control_model.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;
#if defined(__cplusplus)
extern "C" {
#endif

int WaterTank_Control_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->localData[0]->realVars[0] /* level variable */ = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int WaterTank_Control_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[0].attribute.start;
  
  TRACE_POP
  return 0;
}

int WaterTank_Control_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[0].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int WaterTank_Control_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[0].info.name;
  
  TRACE_POP
  return 0;
}

int WaterTank_Control_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = data->localData[0]->realVars[1] /* valve variable */;
  
  TRACE_POP
  return 0;
}


/*
 equation index: 5
 type: SIMPLE_ASSIGN
 valve = if level >= maxlevel then 1.0 else if level < minlevel then 0.0 else pre(valve)
 */
void WaterTank_Control_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  modelica_boolean tmp8;
  modelica_real tmp9;
  RELATIONHYSTERESIS(tmp6, data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[0] /* maxlevel PARAM */, 0, GreaterEq);
  tmp8 = (modelica_boolean)tmp6;
  if(tmp8)
  {
    tmp9 = 1.0;
  }
  else
  {
    RELATIONHYSTERESIS(tmp7, data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[1] /* minlevel PARAM */, 1, Less);
    tmp9 = (tmp7?0.0:data->simulationInfo->realVarsPre[1] /* valve variable */);
  }
  data->localData[0]->realVars[1] /* valve variable */ = tmp9;
  TRACE_POP
}


int WaterTank_Control_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  WaterTank_Control_functionLocalKnownVars(data, threadData);
  WaterTank_Control_eqFunction_5(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int WaterTank_Control_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int WaterTank_Control_symEulerUpdate(DATA *data, modelica_real dt)
{
  return -1;
}



int WaterTank_Control_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  WaterTank_Control_functionLocalKnownVars(data, threadData);
  /* no ODE systems */

  
  TRACE_POP
  return 0;
}

#ifdef FMU_EXPERIMENTAL
#endif
/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "WaterTank_Control_12jac.h"
#include "WaterTank_Control_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks WaterTank_Control_callback = {
   NULL,
   NULL,
   NULL,
   WaterTank_Control_callExternalObjectDestructors,
   NULL,
   WaterTank_Control_initialLinearSystem,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   WaterTank_Control_initializeStateSets,
   #else
   NULL,
   #endif
   WaterTank_Control_initializeDAEmodeData,
   WaterTank_Control_functionODE,
   WaterTank_Control_functionAlgebraics,
   WaterTank_Control_functionDAE,
   WaterTank_Control_functionLocalKnownVars,
   WaterTank_Control_input_function,
   WaterTank_Control_input_function_init,
   WaterTank_Control_input_function_updateStartValues,
   WaterTank_Control_output_function,
   WaterTank_Control_function_storeDelayed,
   WaterTank_Control_updateBoundVariableAttributes,
   0 /* useHomotopy */,
   WaterTank_Control_functionInitialEquations,
   WaterTank_Control_functionInitialEquations_lambda0,
   WaterTank_Control_functionRemovedInitialEquations,
   WaterTank_Control_updateBoundParameters,
   WaterTank_Control_checkForAsserts,
   WaterTank_Control_function_ZeroCrossingsEquations,
   WaterTank_Control_function_ZeroCrossings,
   WaterTank_Control_function_updateRelations,
   WaterTank_Control_checkForDiscreteChanges,
   WaterTank_Control_zeroCrossingDescription,
   WaterTank_Control_relationDescription,
   WaterTank_Control_function_initSample,
   WaterTank_Control_INDEX_JAC_A,
   WaterTank_Control_INDEX_JAC_B,
   WaterTank_Control_INDEX_JAC_C,
   WaterTank_Control_INDEX_JAC_D,
   WaterTank_Control_initialAnalyticJacobianA,
   WaterTank_Control_initialAnalyticJacobianB,
   WaterTank_Control_initialAnalyticJacobianC,
   WaterTank_Control_initialAnalyticJacobianD,
   WaterTank_Control_functionJacA_column,
   WaterTank_Control_functionJacB_column,
   WaterTank_Control_functionJacC_column,
   WaterTank_Control_functionJacD_column,
   WaterTank_Control_linear_model_frame,
   WaterTank_Control_linear_model_datarecovery_frame,
   WaterTank_Control_mayer,
   WaterTank_Control_lagrange,
   WaterTank_Control_pickUpBoundsForInputsInOptimization,
   WaterTank_Control_setInputData,
   WaterTank_Control_getTimeGrid,
   WaterTank_Control_symEulerUpdate,
   WaterTank_Control_function_initSynchronous,
   WaterTank_Control_function_updateSynchronous,
   WaterTank_Control_function_equationsSynchronous,
   WaterTank_Control_read_input_fmu
   #ifdef FMU_EXPERIMENTAL
   ,WaterTank_Control_functionODE_Partial
   ,WaterTank_Control_functionFMIJacobian
   #endif
   ,WaterTank_Control_inputNames


};

void WaterTank_Control_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  data->callback = &WaterTank_Control_callback;
  data->modelData->modelName = "WaterTank.Control";
  data->modelData->modelFilePrefix = "WaterTank_Control";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/var/lib/hudson/jobs/OpenModelica_BUILD/workspace/OpenModelica/testsuite/special/FmuExportCrossCompile";
  data->modelData->modelGUID = "{ad6d7bad-97d1-4fb9-ab3e-00a0d051e42c}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData =
  #if defined(OMC_MINIMAL_METADATA)
    NULL;
  #else
  #include "WaterTank_Control_info.c"
  #endif
  ;
  
  data->modelData->nStates = 0;
  data->modelData->nVariablesReal = 2;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 2;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 1;
  
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 2;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 2;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.fileName = "WaterTank_Control_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 6;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 1;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 5;
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

