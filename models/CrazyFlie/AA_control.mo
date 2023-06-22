model AA_control
import Modelica.SIunits;
    final constant Real g = Modelica.Constants.g_n;   //Acceleration of the gravity
  	parameter SIunits.Mass m = 0.65;   
  	parameter SIunits.Length l = 0.23;                // Length
  	parameter SIunits.MomentOfInertia Ix = 7.5e-3;    //Quadrotor moment of inertia around X axis
  	parameter SIunits.MomentOfInertia Iy = 7.5e-3;    //Quadrotor moment of inertia around Y axis
 	parameter SIunits.MomentOfInertia Iz = 1.3e-2;    //Quadrotor moment of inertia around Z axis
 	parameter SIunits.MomentOfInertia Jr = 6.5e-5;    //Total rotational moment of inertia around the propeller axis
  	parameter Real d = 7.5e-7;                        // Drag factor
  	parameter Real Kpz=90, Kdz=13.795, Kpp=50, Kdp=8, Kpt=50, Kdt=8.09, Kpps=50, Kdps=8.3996;
 Modelica.Blocks.Interfaces.RealInput Phi annotation(
    Placement(visible = true, transformation(origin = {-120, 240}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 240}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Theta annotation(
    Placement(visible = true, transformation(origin = {-120, 180}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 180}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psi annotation(
    Placement(visible = true, transformation(origin = {-120, 120}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 120}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Phid annotation(
    Placement(visible = true, transformation(origin = {-120, 60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 60}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Thetad annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psid annotation(
    Placement(visible = true, transformation(origin = {-120, -60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -60}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Z annotation(
    Placement(visible = true, transformation(origin = {-120, -120}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -120}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Zd annotation(
    Placement(visible = true, transformation(origin = {-120, -180}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -180}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Omega annotation(
    Placement(visible = true, transformation(origin = {-120, -240}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -240}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
    
 Modelica.Blocks.Interfaces.RealOutput T annotation(    
    Placement(visible = true, transformation(origin = {110, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 100}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput tau_phi annotation(
    Placement(visible = true, transformation(origin = {110, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput tau_theta annotation(
    Placement(visible = true, transformation(origin = {110, -50}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput tau_psi annotation(
    Placement(visible = true, transformation(origin = {110, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -100}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
Real Z_dot, Phi_dot, Theta_dot, Psi_dot;

equation
Z_dot=der(Z);Phi_dot=der(Phi);Theta_dot=der(Theta);Psi_dot=der(Psi);
T=(Kpz*(Zd-Z)-Kdz*Z_dot+g)*m/(cos(Phi)*cos(Theta))+d*Z_dot;
tau_phi=Kpp*(Phid-Phi)-Kdp*Phi_dot-(Iy-Iz)/l*Theta_dot*Psi_dot-Jr/l*Theta_dot*Omega;
tau_theta=Kpt*(Thetad-Theta)-Kdt*Theta_dot-(Iz-Ix)/l*Phi_dot*Psi_dot+Jr/l*Phi_dot*Omega;
tau_psi=Kpps*(Psid-Psi)-Kdps*Psi_dot-(Ix-Iy)/l*Phi_dot*Theta_dot;

annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(coordinateSystem(extent = {{-100, -280}, {100, 280}}),graphics = {Rectangle(extent = {{-100, 280}, {100, -280}})}),
    Diagram(coordinateSystem(extent = {{-100, -280}, {100, 280}})),
    version = "",
    __OpenModelica_commandLineOptions = "");

end AA_control;