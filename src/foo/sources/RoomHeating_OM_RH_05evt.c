/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "RoomHeating_OM_RH_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void RoomHeating_OM_RH_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *RoomHeating_OM_RH_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"valveopen > 0.0",
  "fanspeed > 0.0"};
  static const int occurEqs0[] = {1,29};
  static const int occurEqs1[] = {1,22};
  static const int *occurEqs[] = {occurEqs0,occurEqs1};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int RoomHeating_OM_RH_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp0 = GreaterZC(data->localData[0]->realVars[20] /* valveopen variable */, 0.0, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp0) ? 1 : -1;
  tmp1 = GreaterZC(data->localData[0]->realVars[10] /* fanspeed variable */, 0.0, data->simulationInfo->storedRelations[1]);
  gout[1] = (tmp1) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *RoomHeating_OM_RH_relationDescription(int i)
{
  const char *res[] = {"valveopen > 0.0",
  "fanspeed > 0.0"};
  return res[i];
}

int RoomHeating_OM_RH_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  
  if(evalforZeroCross) {
    tmp2 = GreaterZC(data->localData[0]->realVars[20] /* valveopen variable */, 0.0, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp2;
    tmp3 = GreaterZC(data->localData[0]->realVars[10] /* fanspeed variable */, 0.0, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp3;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[20] /* valveopen variable */ > 0.0);
    data->simulationInfo->relations[1] = (data->localData[0]->realVars[10] /* fanspeed variable */ > 0.0);
  }
  
  TRACE_POP
  return 0;
}

int RoomHeating_OM_RH_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int needToIterate = 0;

  infoStreamPrint(LOG_EVENTS_V, 1, "check for discrete changes at time=%.12g", data->localData[0]->timeValue);
  if (ACTIVE_STREAM(LOG_EVENTS_V)) messageClose(LOG_EVENTS_V);
  
  TRACE_POP
  return needToIterate;
}

#if defined(__cplusplus)
}
#endif

