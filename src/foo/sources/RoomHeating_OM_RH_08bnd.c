/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "RoomHeating_OM_RH_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
 equation index: 37
 type: SIMPLE_ASSIGN
 room._RAT = room.RATinit
 */
void RoomHeating_OM_RH_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[0] /* room._RAT STATE(1) */ = data->simulationInfo->realParameter[2] /* room._RATinit PARAM */;
  TRACE_POP
}

/*
 equation index: 38
 type: SIMPLE_ASSIGN
 wall._Tisurf = wall.TisurfInit
 */
void RoomHeating_OM_RH_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */ = data->simulationInfo->realParameter[11] /* wall._TisurfInit PARAM */;
  TRACE_POP
}

/*
 equation index: 39
 type: SIMPLE_ASSIGN
 wall._Tosurf = wall.TosurfInit
 */
void RoomHeating_OM_RH_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */ = data->simulationInfo->realParameter[12] /* wall._TosurfInit PARAM */;
  TRACE_POP
}
int RoomHeating_OM_RH_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  RoomHeating_OM_RH_eqFunction_37(data, threadData);

  RoomHeating_OM_RH_eqFunction_38(data, threadData);

  RoomHeating_OM_RH_eqFunction_39(data, threadData);
  
  infoStreamPrint(LOG_INIT, 1, "updating start-values");
  data->modelData->realVarsData[0].attribute /* room._RAT */.start = data->localData[0]->realVars[0] /* room._RAT STATE(1) */;
    infoStreamPrint(LOG_INIT, 0, "%s(start=%g)", data->modelData->realVarsData[0].info /* room._RAT */.name, (modelica_real)  data->modelData->realVarsData[0].attribute /* room._RAT */.start);
  data->modelData->realVarsData[2].attribute /* wall._Tisurf */.start = data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */;
    infoStreamPrint(LOG_INIT, 0, "%s(start=%g)", data->modelData->realVarsData[2].info /* wall._Tisurf */.name, (modelica_real)  data->modelData->realVarsData[2].attribute /* wall._Tisurf */.start);
  data->modelData->realVarsData[3].attribute /* wall._Tosurf */.start = data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */;
    infoStreamPrint(LOG_INIT, 0, "%s(start=%g)", data->modelData->realVarsData[3].info /* wall._Tosurf */.name, (modelica_real)  data->modelData->realVarsData[3].attribute /* wall._Tosurf */.start);
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

