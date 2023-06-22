model Displacement
final constant Real g = Modelica.Constants.g_n;   //Acceleration of the gravity
  parameter Real m = 0.65;               // Mass
  parameter Real Ix = 7.5e-3;    //Quadrotor moment of inertia around X axis
  parameter Real Iy = 7.5e-3;    //Quadrotor moment of inertia around Y axis
  parameter Real Iz = 1.3e-3;    //Quadrotor moment of inertia around Z axis
  parameter Real Jr = 6.5e-5;    //Total rotational moment of inertia around the propeller axis
  parameter Real b = 3.13e-5;                       //Thrust factor
  parameter Real d = 7.5e-7;                    // Drag factor

 Modelica.Blocks.Interfaces.RealInput u1 annotation(
    Placement(visible = true, transformation(origin = {-120, 105}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 148}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Phi annotation(
    Placement(visible = true, transformation(origin = {-120, 71}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 99}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Theta annotation(
    Placement(visible = true, transformation(origin = {-120, 34}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 51}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psi annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -2}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput X_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Y_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Z_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput X_dot annotation(
    Placement(visible = true, transformation(origin = {-120, -40}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -54}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput Y_dot annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-122, -109}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Z_dot annotation(
    Placement(visible = true, transformation(origin = {-120, -120}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-122, -158}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
equation
X_dot_dot = (cos(Phi)*sin(Theta)*cos(Psi) + sin(Phi)*sin(Psi))*u1/m - X_dot*d/m;
Y_dot_dot = (cos(Phi)*sin(Theta)*sin(Psi) - sin(Phi)*cos(Psi))*u1/m - Y_dot*d/m;
Z_dot_dot = cos(Phi)*cos(Theta)*u1/m - Z_dot*d/m - g;	


annotation(
    Diagram(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}})),
    Icon(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}}), graphics = {Rectangle(origin = {0, 0}, extent = {{-100, 160}, {100, -180}})}),
    version = "",
    uses(Modelica(version = "3.2.2")),
    __OpenModelica_commandLineOptions = "");end Displacement;
