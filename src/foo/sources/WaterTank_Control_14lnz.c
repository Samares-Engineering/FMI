/* Linearization */
#include "WaterTank_Control_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *WaterTank_Control_linear_model_frame()
{
  return "model linear_WaterTank_Control\n  parameter Integer n = 0; // states\n  parameter Integer k = 1; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n"
  "  parameter Real x0[0] = {%s};\n"
  "  parameter Real u0[1] = {%s};\n"
  "  parameter Real A[0,0] = zeros(0,0);%s\n"
  "  parameter Real B[0,1] = zeros(0,1);%s\n"
  "  parameter Real C[1,0] = zeros(1,0);%s\n"
  "  parameter Real D[1,1] = [%s];\n"
  "  Real x[0];\n"
  "  input Real u[1](start= u0);\n"
  "  output Real y[1];\n"
  "\n    Real 'u_level' = u[1];\n  Real 'y_valve' = y[1];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_WaterTank_Control;\n";
}
const char *WaterTank_Control_linear_model_datarecovery_frame()
{
  return "model linear_WaterTank_Control\n  parameter Integer n = 0; // states\n  parameter Integer k = 1; // top-level inputs\n  parameter Integer l = 1; // top-level outputs\n  parameter Integer nz = 2; // data recovery variables\n"
  "  parameter Real x0[0] = {%s};\n"
  "  parameter Real u0[1] = {%s};\n"
  "  parameter Real z0[2] = {%s};\n"
  "  parameter Real A[0,0] = zeros(0,0);%s\n"
  "  parameter Real B[0,1] = zeros(0,1);%s\n"
  "  parameter Real C[1,0] = zeros(1,0);%s\n"
  "  parameter Real D[1,1] = [%s];\n"
  "  parameter Real Cz[2,0] = zeros(2,0);%s\n"
  "  parameter Real Dz[2,1] = [%s];\n"
  "  Real x[0];\n"
  "  input Real u[1](start= u0);\n"
  "  output Real y[1];\n"
  "  output Real z[2];\n"
  "\n  Real 'u_level' = u[1];\n  Real 'y_valve' = y[1];\n  Real 'z_level' = z[1];\n  Real 'z_valve' = z[2];\n\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_WaterTank_Control;\n";
}
#if defined(__cplusplus)
}
#endif

