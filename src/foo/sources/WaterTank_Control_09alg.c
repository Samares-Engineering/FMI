/* Algebraic */
#include "WaterTank_Control_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void WaterTank_Control_eqFunction_5(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  WaterTank_Control_eqFunction_5(data, threadData);
}
/* for continuous time variables */
int WaterTank_Control_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  WaterTank_Control_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
