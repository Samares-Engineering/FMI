/* Jacobians */
static const REAL_ATTRIBUTE dummyREAL_ATTRIBUTE = omc_dummyRealAttribute;
/* Jacobian Variables */
#if defined(__cplusplus)
extern "C" {
#endif
  #define RoomHeating_OM_RH_INDEX_JAC_D 3
  int RoomHeating_OM_RH_functionJacD_column(void* data, threadData_t *threadData);
  int RoomHeating_OM_RH_initialAnalyticJacobianD(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* D */
#define $POATSeedD data->simulationInfo->analyticJacobians[3].seedVars[0]
#define $PfanspeedSeedD data->simulationInfo->analyticJacobians[3].seedVars[1]
#define $PvalveopenSeedD data->simulationInfo->analyticJacobians[3].seedVars[2]

#if defined(__cplusplus)
extern "C" {
#endif
  #define RoomHeating_OM_RH_INDEX_JAC_C 2
  int RoomHeating_OM_RH_functionJacC_column(void* data, threadData_t *threadData);
  int RoomHeating_OM_RH_initialAnalyticJacobianC(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* C */
#define $Proom_RATSeedC data->simulationInfo->analyticJacobians[2].seedVars[0]
#define $Proom_energySeedC data->simulationInfo->analyticJacobians[2].seedVars[1]
#define $Pwall_TisurfSeedC data->simulationInfo->analyticJacobians[2].seedVars[2]
#define $Pwall_TosurfSeedC data->simulationInfo->analyticJacobians[2].seedVars[3]

#if defined(__cplusplus)
extern "C" {
#endif
  #define RoomHeating_OM_RH_INDEX_JAC_B 1
  int RoomHeating_OM_RH_functionJacB_column(void* data, threadData_t *threadData);
  int RoomHeating_OM_RH_initialAnalyticJacobianB(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* B */
#define $POATSeedB data->simulationInfo->analyticJacobians[1].seedVars[0]
#define $PfanspeedSeedB data->simulationInfo->analyticJacobians[1].seedVars[1]
#define $PvalveopenSeedB data->simulationInfo->analyticJacobians[1].seedVars[2]

#if defined(__cplusplus)
extern "C" {
#endif
  #define RoomHeating_OM_RH_INDEX_JAC_A 0
  int RoomHeating_OM_RH_functionJacA_column(void* data, threadData_t *threadData);
  int RoomHeating_OM_RH_initialAnalyticJacobianA(void* data, threadData_t *threadData);
#if defined(__cplusplus)
}
#endif
/* A */
#define $Proom_RATSeedA data->simulationInfo->analyticJacobians[0].seedVars[0]
#define $Proom_energySeedA data->simulationInfo->analyticJacobians[0].seedVars[1]
#define $Pwall_TisurfSeedA data->simulationInfo->analyticJacobians[0].seedVars[2]
#define $Pwall_TosurfSeedA data->simulationInfo->analyticJacobians[0].seedVars[3]


