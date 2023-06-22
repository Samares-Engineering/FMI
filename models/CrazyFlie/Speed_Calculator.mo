model Speed_calculator
  	parameter Real l = 0.23;           // Length
	parameter Real b = 3.13e-5;                  //Thrust factor
  	parameter Real d = 7.5e-7;                   // Drag factor
	Real omegasqr1, omegasqr2, omegasqr3, omegasqr4;
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
  omegasqr1 = U1*(1/(4*b)) + U3*(1/(2*b*l)) - U4*(1/(4*d));
  omegasqr2 = U1*(1/(4*b)) - U2*(1/(2*b*l)) + U4*(1/(4*d));
  omegasqr3 = U1*(1/(4*b)) - U3*(1/(2*b*l)) - U4*(1/(4*d));
  omegasqr4 = 1/(4*b)*U1 + U2*(1/(2*b*l)) + U4*(1/(4*d));
  
  u1 = b*(omegasqr1 + omegasqr2 + omegasqr3 + omegasqr4);
  u2 = b*(omegasqr4 - omegasqr2);
  u3 = b*(omegasqr1 - omegasqr3);
  u4 = d*(- omegasqr1 + omegasqr2 - omegasqr3 + omegasqr4);
  omega = (-sqrt(abs(omegasqr1)) + sqrt(abs(omegasqr2)) - sqrt(abs(omegasqr3)) + sqrt(abs(omegasqr4)))*d;

annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(graphics = {Rectangle(origin = {0, 1}, extent = {{-100, 99}, {100, -101}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 120}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
    end Speed_calculator;
