model Angles_Subsystem
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {-14, 8}, extent = {{-10, -12}, {10, 16}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput u2 annotation(
    Placement(visible = true, transformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput u3 annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput u4 annotation(
    Placement(visible = true, transformation(origin = {-120, -20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -20}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput omega annotation(
    Placement(visible = true, transformation(origin = {-120, -70}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -70}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator1 annotation(
    Placement(visible = true, transformation(origin = {32, 20}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator2 annotation(
    Placement(visible = true, transformation(origin = {74, 20}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput phi annotation(
    Placement(visible = true, transformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput theta annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput psi annotation(
    Placement(visible = true, transformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator3 annotation(
    Placement(visible = true, transformation(origin = {32, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator4 annotation(
    Placement(visible = true, transformation(origin = {72, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator5 annotation(
    Placement(visible = true, transformation(origin = {30, -50}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator6 annotation(
    Placement(visible = true, transformation(origin = {80, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(integrator6.y, psi) annotation(
    Line(points = {{92, -60}, {104, -60}, {104, -60}, {110, -60}}, color = {0, 0, 127}));
  connect(integrator5.y, integrator6.u) annotation(
    Line(points = {{42, -50}, {48, -50}, {48, -60}, {68, -60}, {68, -60}}, color = {0, 0, 127}));
  connect(integrator5.y, angles1.Psi_dot) annotation(
    Line(points = {{42, -50}, {56, -50}, {56, 68}, {-46, 68}, {-46, 14}, {-26, 14}, {-26, 14}}, color = {0, 0, 127}));
  connect(angles1.Psi_dot_dot, integrator5.u) annotation(
    Line(points = {{-2, 2}, {6, 2}, {6, -50}, {18, -50}, {18, -50}}, color = {0, 0, 127}));
  connect(integrator3.y, angles1.Theta_dot) annotation(
    Line(points = {{44, -10}, {48, -10}, {48, 60}, {-44, 60}, {-44, 18}, {-26, 18}, {-26, 18}}, color = {0, 0, 127}));
  connect(integrator4.y, theta) annotation(
    Line(points = {{84, -10}, {90, -10}, {90, 0}, {110, 0}, {110, 0}}, color = {0, 0, 127}));
  connect(integrator3.y, integrator4.u) annotation(
    Line(points = {{44, -10}, {60, -10}, {60, -10}, {60, -10}}, color = {0, 0, 127}));
  connect(angles1.Theta_dot_dot, integrator3.u) annotation(
    Line(points = {{-2, 10}, {12, 10}, {12, -10}, {20, -10}, {20, -10}}, color = {0, 0, 127}));
  connect(integrator2.y, phi) annotation(
    Line(points = {{86, 20}, {92, 20}, {92, 60}, {110, 60}, {110, 60}}, color = {0, 0, 127}));
  connect(integrator1.y, angles1.Phi_dot) annotation(
    Line(points = {{44, 20}, {52, 20}, {52, 56}, {-40, 56}, {-40, 22}, {-26, 22}, {-26, 24}}, color = {0, 0, 127}));
  connect(integrator1.y, integrator2.u) annotation(
    Line(points = {{44, 20}, {62, 20}, {62, 20}, {62, 20}}, color = {0, 0, 127}));
  connect(angles1.Phi_dot_dot, integrator1.u) annotation(
    Line(points = {{-2, 20}, {20, 20}, {20, 20}, {20, 20}}, color = {0, 0, 127}));
  connect(u2, angles1.u2) annotation(
    Line(points = {{-120, 80}, {-50, 80}, {-50, 10}, {-26, 10}, {-26, 10}}, color = {0, 0, 127}));
  connect(u3, angles1.u3) annotation(
    Line(points = {{-120, 30}, {-58, 30}, {-58, 6}, {-26, 6}, {-26, 6}}, color = {0, 0, 127}));
  connect(u4, angles1.u4) annotation(
    Line(points = {{-120, -20}, {-88, -20}, {-88, 2}, {-26, 2}, {-26, 2}}, color = {0, 0, 127}));
  connect(omega, angles1.omega) annotation(
    Line(points = {{-120, -70}, {-74, -70}, {-74, -4}, {-26, -4}, {-26, -3}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(graphics = {Rectangle(origin = {-35, 41}, extent = {{-65, 59}, {135, -141}})}));
end Angles_Subsystem;
