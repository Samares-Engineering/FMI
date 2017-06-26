model System_Model
  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {76, 22}, extent = {{-10, -16}, {10, 14}}, rotation = 0)));
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {-4, 24}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  Speed_calculator speed_calculator1 annotation(
    Placement(visible = true, transformation(origin = {-48, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput T annotation(
    Placement(visible = true, transformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_phi annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_theta annotation(
    Placement(visible = true, transformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_psi annotation(
    Placement(visible = true, transformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Phi annotation(
    Placement(visible = true, transformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Theta annotation(
    Placement(visible = true, transformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Psi annotation(
    Placement(visible = true, transformation(origin = {110, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput X annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Y annotation(
    Placement(visible = true, transformation(origin = {110, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Z annotation(
    Placement(visible = true, transformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Omega annotation(
    Placement(visible = true, transformation(origin = {110, -92}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(Omega, angles1.omega) annotation(
    Line(points = {{110, -92}, {-30, -92}, {-30, 16}, {-16, 16}}, color = {0, 0, 127}));
  connect(displacement1.Z, Z) annotation(
    Line(points = {{88, 14}, {90, 14}, {90, -60}, {110, -60}}, color = {0, 0, 127}));
  connect(displacement1.Y, Y) annotation(
    Line(points = {{88, 22}, {92, 22}, {92, -30}, {110, -30}}, color = {0, 0, 127}));
  connect(Phi, angles1.Phi) annotation(
    Line(points = {{110, 90}, {24, 90}, {24, 32}, {8, 32}}, color = {0, 0, 127}));
  connect(Theta, angles1.Theta) annotation(
    Line(points = {{110, 60}, {30, 60}, {30, 24}, {8, 24}}, color = {0, 0, 127}));
  connect(Psi, angles1.Psi) annotation(
    Line(points = {{110, 30}, {96, 30}, {96, 52}, {16, 52}, {16, 14}, {8, 14}, {8, 16}}, color = {0, 0, 127}));
  connect(X, displacement1.X) annotation(
    Line(points = {{110, 0}, {94, 0}, {94, 32}, {88, 32}}, color = {0, 0, 127}));
  connect(tau_psi, speed_calculator1.U4) annotation(
    Line(points = {{-120, -90}, {-80, -90}, {-80, 16}, {-60, 16}, {-60, 16}}, color = {0, 0, 127}));
  connect(tau_theta, speed_calculator1.U3) annotation(
    Line(points = {{-120, -30}, {-90, -30}, {-90, 22}, {-60, 22}, {-60, 22}}, color = {0, 0, 127}));
  connect(tau_phi, speed_calculator1.U2) annotation(
    Line(points = {{-120, 30}, {-82, 30}, {-82, 26}, {-60, 26}, {-60, 28}}, color = {0, 0, 127}));
  connect(T, speed_calculator1.U1) annotation(
    Line(points = {{-120, 90}, {-76, 90}, {-76, 32}, {-60, 32}, {-60, 32}}, color = {0, 0, 127}));
  connect(speed_calculator1.u1, displacement1.u1) annotation(
    Line(points = {{-36, 28}, {-32, 28}, {-32, 48}, {52, 48}, {52, 36}, {64, 36}, {64, 33}}, color = {0, 0, 127}));
  connect(angles1.Psi, displacement1.Psi) annotation(
    Line(points = {{8, 14}, {48, 14}, {48, 11}, {64, 11}}, color = {0, 0, 127}));
  connect(angles1.Theta, displacement1.Theta) annotation(
    Line(points = {{8, 24}, {50, 24}, {50, 18}, {64, 18}}, color = {0, 0, 127}));
  connect(angles1.Phi, displacement1.Phi) annotation(
    Line(points = {{8, 32}, {52, 32}, {52, 26}, {64, 26}}, color = {0, 0, 127}));
  connect(speed_calculator1.u4, angles1.u4) annotation(
    Line(points = {{-36, 16}, {-22, 16}, {-22, 20}, {-16, 20}, {-16, 20}}, color = {0, 0, 127}));
  connect(speed_calculator1.u3, angles1.u3) annotation(
    Line(points = {{-36, 20}, {-24, 20}, {-24, 26}, {-16, 26}, {-16, 28}}, color = {0, 0, 127}));
  connect(speed_calculator1.u2, angles1.u2) annotation(
    Line(points = {{-36, 24}, {-26, 24}, {-26, 34}, {-16, 34}, {-16, 34}}, color = {0, 0, 127}));
  connect(speed_calculator1.omega, angles1.omega) annotation(
    Line(points = {{-36, 32}, {-30, 32}, {-30, 14}, {-16, 14}, {-16, 14}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Diagram(coordinateSystem(extent = {{-100, -140}, {100, 140}})),
    Icon(coordinateSystem(extent = {{-100, -140}, {100, 140}}),graphics = {Rectangle(extent = {{-100, 140}, {100, -140}})}),
    version = "",
    __OpenModelica_commandLineOptions = "");

end System_Model;