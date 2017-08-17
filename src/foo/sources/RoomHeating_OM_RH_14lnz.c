/* Linearization */
#include "RoomHeating_OM_RH_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *RoomHeating_OM_RH_linear_model_frame()
{
  return "model linear_RoomHeating__OM_RH\n  parameter Integer n = 4; // states\n  parameter Integer k = 3; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n"
  "  parameter Real x0[4] = {%s};\n"
  "  parameter Real u0[3] = {%s};\n"
  "  parameter Real A[4,4] = [%s];\n"
  "  parameter Real B[4,3] = [%s];\n"
  "  parameter Real C[1,4] = [%s];\n"
  "  parameter Real D[1,3] = [%s];\n"
  "  Real x[4](start=x0);\n"
  "  input Real u[3](start= u0);\n"
  "  output Real y[1];\n"
  "\n    Real 'x_room.RAT' = x[1];\n  Real 'x_room.energy' = x[2];\n  Real 'x_wall.Tisurf' = x[3];\n  Real 'x_wall.Tosurf' = x[4];\n  Real 'u_OAT' = u[1];\n  Real 'u_fanspeed' = u[2];\n  Real 'u_valveopen' = u[3];\n  Real 'y_RAT' = y[1];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_RoomHeating__OM_RH;\n";
}
const char *RoomHeating_OM_RH_linear_model_datarecovery_frame()
{
  return "model linear_RoomHeating__OM_RH\n  parameter Integer n = 4; // states\n  parameter Integer k = 3; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n  parameter Integer nz = 15; // data recovery variables\n"
  "  parameter Real x0[4] = {%s};\n"
  "  parameter Real u0[3] = {%s};\n"
  "  parameter Real z0[15] = {%s};\n"
  "  parameter Real A[4,4] = [%s];\n"
  "  parameter Real B[4,3] = [%s];\n"
  "  parameter Real C[1,4] = [%s];\n"
  "  parameter Real D[1,3] = [%s];\n"
  "  parameter Real Cz[15,4] = [%s];\n"
  "  parameter Real Dz[15,3] = [%s];\n"
  "  Real x[4](start=x0);\n"
  "  input Real u[3](start= u0);\n"
  "  output Real y[1];\n"
  "  output Real z[15];\n"
  "\n  Real 'x_room.RAT' = x[1];\n  Real 'x_room.energy' = x[2];\n  Real 'x_wall.Tisurf' = x[3];\n  Real 'x_wall.Tosurf' = x[4];\n  Real 'u_OAT' = u[1];\n  Real 'u_fanspeed' = u[2];\n  Real 'u_valveopen' = u[3];\n  Real 'y_RAT' = y[1];\n  Real 'z_OAT' = z[1];\n  Real 'z_RAT' = z[2];\n  Real 'z_fanspeed' = z[3];\n  Real 'z_room.DT' = z[4];\n  Real 'z_room.EWT' = z[5];\n  Real 'z_room.Qin' = z[6];\n  Real 'z_room.Qout' = z[7];\n  Real 'z_room.SAT' = z[8];\n  Real 'z_room.fs' = z[9];\n  Real 'z_room.mdota' = z[10];\n  Real 'z_room.mdotw' = z[11];\n  Real 'z_room.vo' = z[12];\n  Real 'z_valveopen' = z[13];\n  Real 'z_wall.C' = z[14];\n  Real 'z_wall.R' = z[15];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_RoomHeating__OM_RH;\n";
}
#if defined(__cplusplus)
}
#endif

