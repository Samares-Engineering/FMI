model Angles

	import Modelica.SIunits;
  	parameter SIunits.Length l = 0.23;              // Length
  	parameter SIunits.MomentOfInertia Ix = 7.5e-3;  //Quadrotor moment of inertia around X axis
  	parameter SIunits.MomentOfInertia Iy = 7.5e-3;  //Quadrotor moment of inertia around Y axis
 	parameter SIunits.MomentOfInertia Iz = 1.3e-2;  //Quadrotor moment of inertia around Z axis
 	parameter SIunits.MomentOfInertia Jr = 6.5e-5;  //Total rotational moment of inertia around the propeller axis
	parameter Real b = 3.13e-5;                     //Thrust factor
  	parameter Real d = 7.5e-7;                      // Drag factor
	Real Phi_dot, Theta_dot, Psi_dot, Phi_dot_dot, Theta_dot_dot, Psi_dot_dot;
	
 Modelica.Blocks.Interfaces.RealInput u2 annotation(
    Placement(visible = true, transformation(origin = {-120, 78}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u3 annotation(
    Placement(visible = true, transformation(origin = {-120, 26}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u4 annotation(
    Placement(visible = true, transformation(origin = {-120, -32}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput omega annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Phi annotation(
    Placement(visible = true, transformation(origin = {110, 80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 88}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Theta annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Psi annotation(
    Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
	Phi_dot_dot = (Iy-Iz)/Ix*Theta_dot*Psi_dot + Jr/Ix*Theta_dot*omega + l/Ix*u2;
	Theta_dot_dot = (Iz-Ix)/Iy*Phi_dot*Psi_dot - Jr/Iy*Phi_dot*omega + l/Iy*u3;
	Psi_dot_dot = (Ix-Iy)/Iz*Phi_dot*Theta_dot + 1/Iz*u4;
	Phi_dot = der(Phi); 
	Phi_dot_dot = der(Phi_dot);
	Theta_dot = der(Theta); 
	Theta_dot_dot = der(Theta_dot);
	Psi_dot = der(Psi); 
	Psi_dot_dot = der(Psi_dot);
	
annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(coordinateSystem(extent = {{-100, -120}, {100, 120}}),graphics = {Rectangle(origin = {0, 0}, extent = {{-100, 120}, {100, -120}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 120}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Angles;
