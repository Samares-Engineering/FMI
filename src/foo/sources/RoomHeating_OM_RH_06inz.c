/* Initialization */
#include "RoomHeating_OM_RH_model.h"
#include "RoomHeating_OM_RH_11mix.h"
#include "RoomHeating_OM_RH_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void RoomHeating_OM_RH_functionInitialEquations_0(DATA *data, threadData_t *threadData);


/*
 equation index: 1
 type: SIMPLE_ASSIGN
 room._energy = $_start(room.energy)
 */
void RoomHeating_OM_RH_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[1] /* room._energy STATE(1,room.Qin) */ = data->modelData->realVarsData[1].attribute /* room._energy */.start;
  TRACE_POP
}

/*
 equation index: 2
 type: SIMPLE_ASSIGN
 room._RAT = $_start(room.RAT)
 */
void RoomHeating_OM_RH_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[0] /* room._RAT STATE(1) */ = data->modelData->realVarsData[0].attribute /* room._RAT */.start;
  TRACE_POP
}

/*
 equation index: 3
 type: SIMPLE_ASSIGN
 wall._Tisurf = $_start(wall.Tisurf)
 */
void RoomHeating_OM_RH_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */ = data->modelData->realVarsData[2].attribute /* wall._Tisurf */.start;
  TRACE_POP
}

/*
 equation index: 4
 type: SIMPLE_ASSIGN
 wall._Tosurf = $_start(wall.Tosurf)
 */
void RoomHeating_OM_RH_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */ = data->modelData->realVarsData[3].attribute /* wall._Tosurf */.start;
  TRACE_POP
}

/*
 equation index: 5
 type: SIMPLE_ASSIGN
 wall._C = 0.5 * wall.rhoWall * wall.cWall * wall.lWall * wall.aWall
 */
void RoomHeating_OM_RH_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[21] /* wall._C variable */ = (0.5) * ((data->simulationInfo->realParameter[19] /* wall._rhoWall PARAM */) * ((data->simulationInfo->realParameter[14] /* wall._cWall PARAM */) * ((data->simulationInfo->realParameter[17] /* wall._lWall PARAM */) * (data->simulationInfo->realParameter[13] /* wall._aWall PARAM */))));
  TRACE_POP
}

/*
 equation index: 6
 type: SIMPLE_ASSIGN
 wall._R = DIVISION(wall.lWall, wall.aWall * wall.lambda_Wall)
 */
void RoomHeating_OM_RH_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->localData[0]->realVars[22] /* wall._R variable */ = DIVISION_SIM(data->simulationInfo->realParameter[17] /* wall._lWall PARAM */,(data->simulationInfo->realParameter[13] /* wall._aWall PARAM */) * (data->simulationInfo->realParameter[18] /* wall._lambda_Wall PARAM */),"wall.aWall * wall.lambda_Wall",equationIndexes);
  TRACE_POP
}

/*
 equation index: 7
 type: SIMPLE_ASSIGN
 room._Qout = room.hAir * room.Awall * (room.RAT - wall.Tisurf)
 */
void RoomHeating_OM_RH_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[14] /* room._Qout variable */ = (data->simulationInfo->realParameter[6] /* room._hAir PARAM */) * ((data->simulationInfo->realParameter[0] /* room._Awall PARAM */) * (data->localData[0]->realVars[0] /* room._RAT STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */));
  TRACE_POP
}

/*
 equation index: 8
 type: SIMPLE_ASSIGN
 room._fs = if fanspeed > 0.0 then fanspeed else 0.0001
 */
void RoomHeating_OM_RH_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  modelica_boolean tmp0;
  tmp0 = Greater(data->localData[0]->realVars[10] /* fanspeed variable */,0.0);
  data->localData[0]->realVars[16] /* room._fs variable */ = (tmp0?data->localData[0]->realVars[10] /* fanspeed variable */:0.0001);
  TRACE_POP
}

/*
 equation index: 9
 type: SIMPLE_ASSIGN
 room._Qin = room.eps * room.mdotat * room.fs * room.cAir * (room.LWT - room.RAT)
 */
void RoomHeating_OM_RH_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[13] /* room._Qin variable */ = (data->simulationInfo->realParameter[5] /* room._eps PARAM */) * ((data->simulationInfo->realParameter[7] /* room._mdotat PARAM */) * ((data->localData[0]->realVars[16] /* room._fs variable */) * ((data->simulationInfo->realParameter[3] /* room._cAir PARAM */) * (data->simulationInfo->realParameter[1] /* room._LWT PARAM */ - data->localData[0]->realVars[0] /* room._RAT STATE(1) */))));
  TRACE_POP
}

/*
 equation index: 10
 type: SIMPLE_ASSIGN
 room._DT = room.Qin - room.Qout
 */
void RoomHeating_OM_RH_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[11] /* room._DT variable */ = data->localData[0]->realVars[13] /* room._Qin variable */ - data->localData[0]->realVars[14] /* room._Qout variable */;
  TRACE_POP
}

/*
 equation index: 11
 type: SIMPLE_ASSIGN
 der(room._RAT) = DIVISION(room.DT, room.vAir * room.cAir * room.rohAir)
 */
void RoomHeating_OM_RH_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[4] /* der(room._RAT) STATE_DER */ = DIVISION_SIM(data->localData[0]->realVars[11] /* room._DT variable */,((data->simulationInfo->realParameter[10] /* room._vAir PARAM */) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */)) * (data->simulationInfo->realParameter[9] /* room._rohAir PARAM */),"room.vAir * room.cAir * room.rohAir",equationIndexes);
  TRACE_POP
}

/*
 equation index: 12
 type: SIMPLE_ASSIGN
 der(room._energy) = room.Qin
 */
void RoomHeating_OM_RH_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  data->localData[0]->realVars[5] /* der(room._energy) STATE_DER */ = data->localData[0]->realVars[13] /* room._Qin variable */;
  TRACE_POP
}

/*
 equation index: 13
 type: SIMPLE_ASSIGN
 room._mdota = room.fs * room.mdotat
 */
void RoomHeating_OM_RH_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->localData[0]->realVars[17] /* room._mdota variable */ = (data->localData[0]->realVars[16] /* room._fs variable */) * (data->simulationInfo->realParameter[7] /* room._mdotat PARAM */);
  TRACE_POP
}

/*
 equation index: 14
 type: SIMPLE_ASSIGN
 room._SAT = DIVISION(room.Qin - (-room.RAT) * room.cAir * room.mdota, room.mdota * room.cAir)
 */
void RoomHeating_OM_RH_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[15] /* room._SAT variable */ = DIVISION_SIM(data->localData[0]->realVars[13] /* room._Qin variable */ - ((((-data->localData[0]->realVars[0] /* room._RAT STATE(1) */)) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */)) * (data->localData[0]->realVars[17] /* room._mdota variable */)),(data->localData[0]->realVars[17] /* room._mdota variable */) * (data->simulationInfo->realParameter[3] /* room._cAir PARAM */),"room.mdota * room.cAir",equationIndexes);
  TRACE_POP
}

/*
 equation index: 15
 type: SIMPLE_ASSIGN
 room._vo = if valveopen > 0.0 then valveopen else 0.0001
 */
void RoomHeating_OM_RH_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  modelica_boolean tmp1;
  tmp1 = Greater(data->localData[0]->realVars[20] /* valveopen variable */,0.0);
  data->localData[0]->realVars[19] /* room._vo variable */ = (tmp1?data->localData[0]->realVars[20] /* valveopen variable */:0.0001);
  TRACE_POP
}

/*
 equation index: 16
 type: SIMPLE_ASSIGN
 room._EWT = DIVISION(room.LWT * room.cWater * room.mdotwt * room.vo - room.Qin, room.vo * room.mdotwt * room.cWater)
 */
void RoomHeating_OM_RH_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[12] /* room._EWT variable */ = DIVISION_SIM((((data->simulationInfo->realParameter[1] /* room._LWT PARAM */) * (data->simulationInfo->realParameter[4] /* room._cWater PARAM */)) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */)) * (data->localData[0]->realVars[19] /* room._vo variable */) - data->localData[0]->realVars[13] /* room._Qin variable */,((data->localData[0]->realVars[19] /* room._vo variable */) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */)) * (data->simulationInfo->realParameter[4] /* room._cWater PARAM */),"room.vo * room.mdotwt * room.cWater",equationIndexes);
  TRACE_POP
}

/*
 equation index: 17
 type: SIMPLE_ASSIGN
 room._mdotw = room.vo * room.mdotwt
 */
void RoomHeating_OM_RH_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[18] /* room._mdotw variable */ = (data->localData[0]->realVars[19] /* room._vo variable */) * (data->simulationInfo->realParameter[8] /* room._mdotwt PARAM */);
  TRACE_POP
}

/*
 equation index: 18
 type: SIMPLE_ASSIGN
 der(wall._Tosurf) = DIVISION(wall.ho * wall.aWall * (OAT - wall.Tosurf) + DIVISION(wall.Tisurf - wall.Tosurf, wall.R), wall.C)
 */
void RoomHeating_OM_RH_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->localData[0]->realVars[7] /* der(wall._Tosurf) STATE_DER */ = DIVISION_SIM((data->simulationInfo->realParameter[16] /* wall._ho PARAM */) * ((data->simulationInfo->realParameter[13] /* wall._aWall PARAM */) * (data->localData[0]->realVars[8] /* OAT variable */ - data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */)) + DIVISION_SIM(data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */ - data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */,data->localData[0]->realVars[22] /* wall._R variable */,"wall.R",equationIndexes),data->localData[0]->realVars[21] /* wall._C variable */,"wall.C",equationIndexes);
  TRACE_POP
}

/*
 equation index: 19
 type: SIMPLE_ASSIGN
 der(wall._Tisurf) = DIVISION(wall.hi * wall.aWall * (room.RAT - wall.Tisurf) + DIVISION(wall.Tosurf - wall.Tisurf, wall.R), wall.C)
 */
void RoomHeating_OM_RH_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[6] /* der(wall._Tisurf) STATE_DER */ = DIVISION_SIM((data->simulationInfo->realParameter[15] /* wall._hi PARAM */) * ((data->simulationInfo->realParameter[13] /* wall._aWall PARAM */) * (data->localData[0]->realVars[0] /* room._RAT STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */)) + DIVISION_SIM(data->localData[0]->realVars[3] /* wall._Tosurf STATE(1) */ - data->localData[0]->realVars[2] /* wall._Tisurf STATE(1) */,data->localData[0]->realVars[22] /* wall._R variable */,"wall.R",equationIndexes),data->localData[0]->realVars[21] /* wall._C variable */,"wall.C",equationIndexes);
  TRACE_POP
}

/*
 equation index: 20
 type: SIMPLE_ASSIGN
 RAT = room.RAT
 */
void RoomHeating_OM_RH_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->realVars[9] /* RAT variable */ = data->localData[0]->realVars[0] /* room._RAT STATE(1) */;
  TRACE_POP
}
void RoomHeating_OM_RH_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  RoomHeating_OM_RH_eqFunction_1(data, threadData);
  RoomHeating_OM_RH_eqFunction_2(data, threadData);
  RoomHeating_OM_RH_eqFunction_3(data, threadData);
  RoomHeating_OM_RH_eqFunction_4(data, threadData);
  RoomHeating_OM_RH_eqFunction_5(data, threadData);
  RoomHeating_OM_RH_eqFunction_6(data, threadData);
  RoomHeating_OM_RH_eqFunction_7(data, threadData);
  RoomHeating_OM_RH_eqFunction_8(data, threadData);
  RoomHeating_OM_RH_eqFunction_9(data, threadData);
  RoomHeating_OM_RH_eqFunction_10(data, threadData);
  RoomHeating_OM_RH_eqFunction_11(data, threadData);
  RoomHeating_OM_RH_eqFunction_12(data, threadData);
  RoomHeating_OM_RH_eqFunction_13(data, threadData);
  RoomHeating_OM_RH_eqFunction_14(data, threadData);
  RoomHeating_OM_RH_eqFunction_15(data, threadData);
  RoomHeating_OM_RH_eqFunction_16(data, threadData);
  RoomHeating_OM_RH_eqFunction_17(data, threadData);
  RoomHeating_OM_RH_eqFunction_18(data, threadData);
  RoomHeating_OM_RH_eqFunction_19(data, threadData);
  RoomHeating_OM_RH_eqFunction_20(data, threadData);
  TRACE_POP
}


int RoomHeating_OM_RH_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  RoomHeating_OM_RH_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int RoomHeating_OM_RH_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int RoomHeating_OM_RH_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

