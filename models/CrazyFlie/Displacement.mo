model Displacement
import Modelica.SIunits;
final constant Real g = Modelica.Constants.g_n; //Acceleration of the gravity	
parameter SIunits.Mass m = 0.65;             // Mass 	
parameter SIunits.MomentOfInertia Ix = 7.5e-3;  //Quadrotor moment of inertia around X axis 	
parameter SIunits.MomentOfInertia Iy = 7.5e-3;  //Quadrotor moment of inertia around Y axis 	
parameter SIunits.MomentOfInertia Iz = 1.3e-3;  //Quadrotor moment of inertia around Z axis	
parameter SIunits.MomentOfInertia Jr = 6.5e-5;  //Total rotational moment of inertia around the propeller axis	
parameter Real b = 3.13e-5;                     //Thrust factor 	
parameter Real d = 7.5e-7;                    // Drag factor
Real X_dot, Y_dot, Z_dot, X_dot_dot, Y_dot_dot, Z_dot_dot;
 Modelica.Blocks.Interfaces.RealInput u1 annotation(
    Placement(visible = true, transformation(origin = {-120, 110}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 110}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Phi annotation(
    Placement(visible = true, transformation(origin = {-120, 40}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 40}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Theta annotation(
    Placement(visible = true, transformation(origin = {-120, -40}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -40}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psi annotation(
    Placement(visible = true, transformation(origin = {-120, -110}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -110}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput X annotation(
    Placement(visible = true, transformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Z annotation(
    Placement(visible = true, transformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

equation
X_dot_dot = (cos(Phi)*sin(Theta)*cos(Psi) + sin(Phi)*sin(Psi))*u1/m - X_dot*d/m;
Y_dot_dot = (cos(Phi)*sin(Theta)*sin(Psi) + sin(Phi)*cos(Psi))*u1/m - Y_dot*d/m;
Z_dot_dot = cos(Phi)*cos(Theta)*u1/m - Z_dot*d/m - g;	
X_dot = der(X); 
X_dot_dot = der(X_dot);	
Y_dot = der(Y); 
Y_dot_dot = der(Y_dot);	
Z_dot = der(Z); 
Z_dot_dot = der(Z_dot);

annotation(
    Diagram(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}})),
    Icon(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}}),graphics = {Rectangle(origin = {0, 0}, extent = {{-100, 160}, {100, -180}})}),
    version = "",
    uses,
    __OpenModelica_commandLineOptions = "");end Displacement;
