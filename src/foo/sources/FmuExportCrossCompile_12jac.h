/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define FmuExportCrossCompile_INDEX_JAC_D 3
  int FmuExportCrossCompile_functionJacD_column(void* data, threadData_t *threadData);
  int FmuExportCrossCompile_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */

#if defined(__cplusplus)
extern "C" {
#endif
  #define FmuExportCrossCompile_INDEX_JAC_C 2
  int FmuExportCrossCompile_functionJacC_column(void* data, threadData_t *threadData);
  int FmuExportCrossCompile_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */

#if defined(__cplusplus)
extern "C" {
#endif
  #define FmuExportCrossCompile_INDEX_JAC_B 1
  int FmuExportCrossCompile_functionJacB_column(void* data, threadData_t *threadData);
  int FmuExportCrossCompile_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */

#if defined(__cplusplus)
extern "C" {
#endif
  #define FmuExportCrossCompile_INDEX_JAC_A 0
  int FmuExportCrossCompile_functionJacA_column(void* data, threadData_t *threadData);
  int FmuExportCrossCompile_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */
#define $PhSeedA data->simulationInfo->analyticJacobians[0].seedVars[0]
#define $PvSeedA data->simulationInfo->analyticJacobians[0].seedVars[1]


