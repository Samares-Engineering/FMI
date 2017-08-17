/* Linear Systems */
#include "WaterTank_Control_model.h"
#include "WaterTank_Control_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* initial linear systems */

/*
 equation index: 1
 type: SIMPLE_ASSIGN
 valve = $PRE.valve
 */
void WaterTank_Control_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[1] /* valve variable */ = data->simulationInfo->realVarsPre[1] /* valve variable */;
  TRACE_POP
}

void residualFunc4(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,4};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_boolean tmp2;
  modelica_real tmp3;
  data->simulationInfo->realVarsPre[1] /* valve variable */ = xloc[0];
  /* local constraints */
  WaterTank_Control_eqFunction_1(data, threadData);
  tmp0 = GreaterEq(data->localData[0]->realVars[0] /* level variable */,data->simulationInfo->realParameter[0] /* maxlevel PARAM */);
  tmp2 = (modelica_boolean)tmp0;
  if(tmp2)
  {
    tmp3 = 1.0;
  }
  else
  {
    tmp1 = Less(data->localData[0]->realVars[0] /* level variable */,data->simulationInfo->realParameter[1] /* minlevel PARAM */);
    tmp3 = (tmp1?0.0:data->simulationInfo->realVarsPre[1] /* valve variable */);
  }
  res[0] = tmp3 - data->localData[0]->realVars[1] /* valve variable */;
  TRACE_POP
}
void initializeStaticLSData4(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for $PRE.valve */
  linearSystemData->nominal[i] = data->modelData->realVarsData[-2].attribute /* ERROR_cref2simvar_failed $PRE.valve */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[-2].attribute /* ERROR_cref2simvar_failed $PRE.valve */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[-2].attribute /* ERROR_cref2simvar_failed $PRE.valve */.max;
}
/* initial_lambda0 linear systems */
/* parameter linear systems */
/* model linear systems */
/* jacobians linear systems */

/* Prototypes for the strict sets (Dynamic Tearing) */

/* Global constraints for the casual sets */
/* function initialize linear systems */
void WaterTank_Control_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* initial linear systems */
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 4;
  linearSystemData[0].size = 1;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;
  linearSystemData[0].residualFunc = residualFunc4;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = WaterTank_Control_functionJacLSJac1_column;
  linearSystemData[0].initialAnalyticalJacobian = WaterTank_Control_initialAnalyticJacobianLSJac1;
  linearSystemData[0].jacobianIndex = 0;
  linearSystemData[0].setA = NULL;//setLinearMatrixA4;
  linearSystemData[0].setb = NULL; //setLinearVectorb4;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData4;
  /* initial_lambda0 linear systems */
  /* parameter linear systems */
  /* model linear systems */
  /* jacobians linear systems */
}

#if defined(__cplusplus)
}
#endif

