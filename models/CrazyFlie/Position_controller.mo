model Position_controller
import Modelica.SIunits;
    final constant Real g = Modelica.Constants.g_n;   //Acceleration of the gravity
    parameter Real Kpx=6, Kdx=4, Kpy=6, Kdy=4, Kpz=6, Kdz=0.4;
 Modelica.Blocks.Interfaces.RealInput Xd annotation(
    Placement(visible = true, transformation(origin = {-120, 150}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 150}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput X annotation(
    Placement(visible = true, transformation(origin = {-120, 100}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 100}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Yd annotation(
    Placement(visible = true, transformation(origin = {-120, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Y annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Zd annotation(
    Placement(visible = true, transformation(origin = {-120, -50}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -50}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Z annotation(
    Placement(visible = true, transformation(origin = {-120, -100}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -100}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psid annotation(
    Placement(visible = true, transformation(origin = {-120, -150}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -150}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 
 Modelica.Blocks.Interfaces.RealOutput Phid annotation(
    Placement(visible = true, transformation(origin = {110, 75}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 75}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Thetad annotation(
    Placement(visible = true, transformation(origin = {110, -75}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -75}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

Real dx, dy, dz, Xd_dot_dot, Yd_dot_dot, Zd_dot_dot, Xd_dot, Yd_dot, Zd_dot, X_dot, Y_dot, Z_dot;

equation
   Xd_dot=der(Xd);Xd_dot_dot=der(Xd_dot);X_dot=der(X);
   Yd_dot=der(Yd);Yd_dot_dot=der(Yd_dot);Y_dot=der(Y);
   Zd_dot=der(Zd);Zd_dot_dot=der(Zd_dot);Z_dot=der(Z);
   dx=Xd_dot_dot+Kdx*(Xd_dot-X_dot)+Kpx*(Xd-X);
   dy=Yd_dot_dot+Kdy*(Yd_dot-Y_dot)+Kpy*(Yd-Y);
   dz=Zd_dot_dot+Kdz*(Zd_dot-Z_dot)+Kpz*(Zd-Z);
   Thetad=atan(dx*cos(Psid)+dy*sin(Psid))/(dz+g);
   Phid=atan(dx*sin(Psid)-dy*cos(Psid))/(sqrt(dx^2+dy^2+(dz+g)^2));

annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(coordinateSystem(extent = {{-100, -180}, {100, 180}}),graphics = {Rectangle(extent = {{-100, 180}, {100, -180}})}),
    Diagram(coordinateSystem(extent = {{-100, -180}, {100, 180}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Position_controller;