/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "FmuExportCrossCompile_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void FmuExportCrossCompile_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
}

const char *FmuExportCrossCompile_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"h <= 0.0"};
  static const int occurEqs0[] = {1,8};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void FmuExportCrossCompile_eqFunction_10(DATA* data, threadData_t *threadData);
extern void FmuExportCrossCompile_eqFunction_11(DATA* data, threadData_t *threadData);

int FmuExportCrossCompile_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  FmuExportCrossCompile_eqFunction_10(data, threadData);

  FmuExportCrossCompile_eqFunction_11(data, threadData);
  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp0;
  
  data->simulationInfo->callStatistics.functionZeroCrossings++;
  
  tmp0 = LessEqZC(data->localData[0]->realVars[0] /* h STATE(1,v) */, 0.0, data->simulationInfo->storedRelations[0]);
  gout[0] = (tmp0) ? 1 : -1;
  
  TRACE_POP
  return 0;
}

const char *FmuExportCrossCompile_relationDescription(int i)
{
  const char *res[] = {"h <= 0.0"};
  return res[i];
}

int FmuExportCrossCompile_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp1;
  
  if(evalforZeroCross) {
    tmp1 = LessEqZC(data->localData[0]->realVars[0] /* h STATE(1,v) */, 0.0, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp1;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[0] /* h STATE(1,v) */ <= 0.0);
  }
  
  TRACE_POP
  return 0;
}

int FmuExportCrossCompile_checkForDiscreteChanges(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int needToIterate = 0;

  infoStreamPrint(LOG_EVENTS_V, 1, "check for discrete changes at time=%.12g", data->localData[0]->timeValue);
  if(data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ != data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: $whenCondition1 from %d to %d", data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */, data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */);
    needToIterate = 1;
  }
  if(data->localData[0]->realVars[4] /* v_new DISCRETE */ != data->simulationInfo->realVarsPre[4] /* v_new DISCRETE */)
  {
    infoStreamPrint(LOG_EVENTS_V, 0, "discrete var changed: v_new from %g to %g", data->simulationInfo->realVarsPre[4] /* v_new DISCRETE */, data->localData[0]->realVars[4] /* v_new DISCRETE */);
    needToIterate = 1;
  }
  if (ACTIVE_STREAM(LOG_EVENTS_V)) messageClose(LOG_EVENTS_V);
  
  TRACE_POP
  return needToIterate;
}

#if defined(__cplusplus)
}
#endif

