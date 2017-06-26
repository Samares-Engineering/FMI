model Speed_calculator
	import Modelica.SIunits;
  	parameter SIunits.Length l = 0.23;           // Length
	parameter Real b = 3.13e-5;                  //Thrust factor
  	parameter Real d = 7.5e-7;                   // Drag factor
	Real o1, o2, o3, o4;
 Modelica.Blocks.Interfaces.RealInput U1 annotation(
    Placement(visible = true, transformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U2 annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U3 annotation(
    Placement(visible = true, transformation(origin = {-120, -28}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -24}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U4 annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u1 annotation(
    Placement(visible = true, transformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u2 annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u3 annotation(
    Placement(visible = true, transformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u4 annotation(
    Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput omega annotation(
    Placement(visible = true, transformation(origin = {110, 80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 80}, 
extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    
equation
    o1 = 1/(4*b)*U1 + 1/(2*b*l)*U3 - 1/(4*d)*U4;
    o2 = 1/(4*b)*U1 - 1/(2*b*l)*U2 + 1/(4*d)*U4;
    o3 = 1/(4*b)*U1 - 1/(2*b*l)*U3 - 1/(4*d)*U4;
    o4 = 1/(4*b)*U1 + 1/(2*b*l)*U2 + 1/(4*d)*U4;
	omega = (-sqrt(abs(o1)) + sqrt(abs(o2)) - sqrt(abs(o3)) + sqrt(abs(o4)))*d;
	u1 = U1;
	u2 = U2/l;
	u3 = U3/l;
 	u4 = U4;
 	
annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(graphics = {Rectangle(origin = {0, 1}, extent = {{-100, 99}, {100, -101}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 120}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
    end Speed_calculator;