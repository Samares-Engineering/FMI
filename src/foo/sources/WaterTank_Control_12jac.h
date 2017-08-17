/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define WaterTank_Control_INDEX_JAC_LSJac1 0
  int WaterTank_Control_functionJacLSJac1_column(void* data, threadData_t *threadData);
  int WaterTank_Control_initialAnalyticJacobianLSJac1(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* LSJac1 */
#define $P$PRE_valveSeedLSJac1 data->simulationInfo->analyticJacobians[0].seedVars[0]
#define _$Pvalve$P$pDERLSJac1$PdummyVarLSJac1(i) data->simulationInfo->analyticJacobians[0].tmpVars[0]
#define $Pvalve$P$pDERLSJac1$PdummyVarLSJac1 _$Pvalve$P$pDERLSJac1$PdummyVarLSJac1(0)

#define _$P$res$P1$P$pDERLSJac1$PdummyVarLSJac1(i) data->simulationInfo->analyticJacobians[0].resultVars[0]
#define $P$res$P1$P$pDERLSJac1$PdummyVarLSJac1 _$P$res$P1$P$pDERLSJac1$PdummyVarLSJac1(0)

#if defined(__cplusplus)
extern "C" {
#endif
  #define WaterTank_Control_INDEX_JAC_D 4
  int WaterTank_Control_functionJacD_column(void* data, threadData_t *threadData);
  int WaterTank_Control_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */
#define $PlevelSeedD data->simulationInfo->analyticJacobians[4].seedVars[0]

#if defined(__cplusplus)
extern "C" {
#endif
  #define WaterTank_Control_INDEX_JAC_C 3
  int WaterTank_Control_functionJacC_column(void* data, threadData_t *threadData);
  int WaterTank_Control_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */

#if defined(__cplusplus)
extern "C" {
#endif
  #define WaterTank_Control_INDEX_JAC_B 2
  int WaterTank_Control_functionJacB_column(void* data, threadData_t *threadData);
  int WaterTank_Control_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */

#if defined(__cplusplus)
extern "C" {
#endif
  #define WaterTank_Control_INDEX_JAC_A 1
  int WaterTank_Control_functionJacA_column(void* data, threadData_t *threadData);
  int WaterTank_Control_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */


