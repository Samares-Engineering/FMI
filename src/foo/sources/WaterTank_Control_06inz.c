/* Initialization */
#include "WaterTank_Control_model.h"
#include "WaterTank_Control_11mix.h"
#include "WaterTank_Control_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void WaterTank_Control_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 4
 type: LINEAR
 
 <var>$PRE._valve</var>
 <row>

 </row>
 <matrix>
 </matrix>
 */
void WaterTank_Control_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  /* Linear equation system */
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 4 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  data->simulationInfo->linearSystemData[0].x[0] = data->simulationInfo->realVarsPre[1] /* valve variable */;
  retValue = solve_linear_system(data, threadData, 0);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,4};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 4 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->simulationInfo->realVarsPre[1] /* valve variable */ = data->simulationInfo->linearSystemData[0].x[0];
  TRACE_POP
}
void WaterTank_Control_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  WaterTank_Control_eqFunction_4(data, threadData);
  TRACE_POP
}


int WaterTank_Control_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  WaterTank_Control_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int WaterTank_Control_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int WaterTank_Control_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
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

