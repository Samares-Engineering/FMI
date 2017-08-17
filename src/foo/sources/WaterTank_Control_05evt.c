/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "WaterTank_Control_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void WaterTank_Control_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *WaterTank_Control_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"level >= maxlevel",
  "level < minlevel"};
  static const int occurEqs0[] = {1,5};
  static const int occurEqs1[] = {1,5};
  static const int *occurEqs[] = {occurEqs0,occurEqs1};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */

int WaterTank_Control_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  
  TRACE_POP
  return 0;
}

int WaterTank_Control_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp4;
  modelica_boolean tmp5;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp4 = GreaterEqZC(data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[0] /* maxlevel PARAM */, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp4) ? 1 : -1;
  tmp5 = LessZC(data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[1] /* minlevel PARAM */, data->simulationInfo->storedRelations[1]);
  gout[1] = (tmp5) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *WaterTank_Control_relationDescription(int i)
{
  const char *res[] = {"level >= maxlevel",
  "level < minlevel"};
  return res[i];
}

int WaterTank_Control_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  
  if(evalforZeroCross) {
    tmp6 = GreaterEqZC(data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[0] /* maxlevel PARAM */, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp6;
    tmp7 = LessZC(data->localData[0]->realVars[0] /* level variable */, data->simulationInfo->realParameter[1] /* minlevel PARAM */, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp7;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[0] /* level variable */ >= data->simulationInfo->realParameter[0] /* maxlevel PARAM */);
    data->simulationInfo->relations[1] = (data->localData[0]->realVars[0] /* level variable */ < data->simulationInfo->realParameter[1] /* minlevel PARAM */);
  }
  
  TRACE_POP
  return 0;
}

int WaterTank_Control_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
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

