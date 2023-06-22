model Angles

  	parameter Real l = 0.23;              // Length
  	parameter Real Ix = 0.0075;  //Quadrotor moment of inertia around X axis
  	parameter Real Iy = 0.0075;  //Quadrotor moment of inertia around Y axis
 	parameter Real Iz = 0.013;  //Quadrotor moment of inertia around Z axis
 	parameter Real Jr = 6.5e-5;  //Total rotational moment of inertia around the propeller axis
	parameter Real b = 3.13e-5;                     //Thrust factor
  	parameter Real d = 7.5e-7;                      // Drag factor
	
 Modelica.Blocks.Interfaces.RealInput u2 annotation(
    Placement(visible = true, transformation(origin = {-120, 20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 22}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u3 annotation(
    Placement(visible = true, transformation(origin = {-120, -20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -22}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u4 annotation(
    Placement(visible = true, transformation(origin = {-120, -60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -66}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput omega annotation(
    Placement(visible = true, transformation(origin = {-120, -100}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -110}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Phi_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, 120}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 110}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Theta_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 20}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Psi_dot_dot annotation(
    Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -70}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Phi_dot annotation(
    Placement(visible = true, transformation(origin = {-120, 140}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 150}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psi_dot annotation(
    Placement(visible = true, transformation(origin = {-120, 60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 66}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Theta_dot annotation(
    Placement(visible = true, transformation(origin = {-120, 100}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 108}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
equation
	Phi_dot_dot = ((Iy - Iz)/Ix)*Theta_dot*Psi_dot + (Jr/Ix)*Theta_dot*omega + (l/Ix)*u2;
	Theta_dot_dot = ((Iz - Ix)/Iy)*Phi_dot*Psi_dot - (Jr/Iy)*Phi_dot*omega + (l/Iy)*u3;
	Psi_dot_dot = ((Ix - Iy)/Iz)*Phi_dot*Theta_dot + (1/Iz)*u4;
annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(coordinateSystem(extent = {{-100, -120}, {100, 160}}),graphics = {Rectangle(origin = {0, 40}, extent = {{-100, 120}, {100, -160}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 160}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Angles;
