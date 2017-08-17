/* Algebraic */
#include "RoomHeating_OM_RH_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void RoomHeating_OM_RH_eqFunction_27(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_28(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_29(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_30(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_31(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_34(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_36(DATA* data, threadData_t *threadData);
extern void RoomHeating_OM_RH_eqFunction_35(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
  RoomHeating_OM_RH_eqFunction_27(data, threadData);

  RoomHeating_OM_RH_eqFunction_28(data, threadData);

  RoomHeating_OM_RH_eqFunction_29(data, threadData);

  RoomHeating_OM_RH_eqFunction_30(data, threadData);

  RoomHeating_OM_RH_eqFunction_31(data, threadData);

  RoomHeating_OM_RH_eqFunction_34(data, threadData);

  RoomHeating_OM_RH_eqFunction_36(data, threadData);

  RoomHeating_OM_RH_eqFunction_35(data, threadData);
}
/* for continuous time variables */
int RoomHeating_OM_RH_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  RoomHeating_OM_RH_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
