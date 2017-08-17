/* Initialization */
#include "FmuExportCrossCompile_model.h"
#include "FmuExportCrossCompile_11mix.h"
#include "FmuExportCrossCompile_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void FmuExportCrossCompile_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 der(v) = -g
 */
void FmuExportCrossCompile_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[3] /* der(v) STATE_DER */ = (-data->simulationInfo->realParameter[1] /* g PARAM */);
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 v = $_start(v)
 */
void FmuExportCrossCompile_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[1] /* v STATE(1) */ = data->modelData->realVarsData[1].attribute /* v */.start;
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 der(h) = v
 */
void FmuExportCrossCompile_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[2] /* der(h) STATE_DER */ = data->localData[0]->realVars[1] /* v STATE(1) */;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 h = $_start(h)
 */
void FmuExportCrossCompile_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->realVars[0] /* h STATE(1,v) */ = data->modelData->realVarsData[0].attribute /* h */.start;
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 $whenCondition1 = h <= 0.0
 */
void FmuExportCrossCompile_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  modelica_boolean tmp0;
  tmp0 = LessEq(data->localData[0]->realVars[0] /* h STATE(1,v) */,0.0);
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = tmp0;
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 $PRE._v_new = 0.0
 */
void FmuExportCrossCompile_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->simulationInfo->realVarsPre[4] /* v_new DISCRETE */ = 0.0;
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 v_new = $PRE.v_new
 */
void FmuExportCrossCompile_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[4] /* v_new DISCRETE */ = data->simulationInfo->realVarsPre[4] /* v_new DISCRETE */;
  TRACE_POP
}
void FmuExportCrossCompile_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  FmuExportCrossCompile_eqFunction_1(data, threadData);
  FmuExportCrossCompile_eqFunction_2(data, threadData);
  FmuExportCrossCompile_eqFunction_3(data, threadData);
  FmuExportCrossCompile_eqFunction_4(data, threadData);
  FmuExportCrossCompile_eqFunction_5(data, threadData);
  FmuExportCrossCompile_eqFunction_6(data, threadData);
  FmuExportCrossCompile_eqFunction_7(data, threadData);
  TRACE_POP
}


int FmuExportCrossCompile_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  FmuExportCrossCompile_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int FmuExportCrossCompile_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int FmuExportCrossCompile_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

