/* Algebraic */
#include "FmuExportCrossCompile_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void FmuExportCrossCompile_eqFunction_8(DATA* data, threadData_t *threadData);
extern void FmuExportCrossCompile_eqFunction_12(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  FmuExportCrossCompile_eqFunction_8(data, threadData);

  FmuExportCrossCompile_eqFunction_12(data, threadData);
}
/* for continuous time variables */
int FmuExportCrossCompile_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  FmuExportCrossCompile_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
