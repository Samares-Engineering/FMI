model Drone_Model
  Speed_calculator speed_calculator1 annotation(
    Placement(visible = true, transformation(origin = {-92.408, 29.891}, extent = {{-13.7424, -16.491}, {13.7424, 16.491}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step1(height = 1) annotation(
    Placement(visible = true, transformation(origin = {-184, 48}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step2(height = 1) annotation(
    Placement(visible = true, transformation(origin = {-182, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step3(height = 1) annotation(
    Placement(visible = true, transformation(origin = {-184, -4}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step4(height = 1) annotation(
    Placement(visible = true, transformation(origin = {-184, -32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Angles_Subsystem angles_Subsystem1 annotation(
    Placement(visible = true, transformation(origin = {-10, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Displacement_Subsystem displacement_Subsystem1 annotation(
    Placement(visible = true, transformation(origin = {50, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(speed_calculator1.u1, displacement_Subsystem1.u1) annotation(
    Line(points = {{-78, 36}, {-42, 36}, {-42, 12}, {30, 12}, {30, 22}, {38, 22}, {38, 24}}, color = {0, 0, 127}));
  connect(angles_Subsystem1.psi, displacement_Subsystem1.psi) annotation(
    Line(points = {{2, 24}, {26, 24}, {26, 28}, {38, 28}, {38, 28}}, color = {0, 0, 127}));
  connect(angles_Subsystem1.theta, displacement_Subsystem1.theta) annotation(
    Line(points = {{2, 30}, {28, 30}, {28, 32}, {38, 32}, {38, 34}}, color = {0, 0, 127}));
  connect(angles_Subsystem1.phi, displacement_Subsystem1.phi) annotation(
    Line(points = {{2, 36}, {26, 36}, {26, 38}, {38, 38}, {38, 38}}, color = {0, 0, 127}));
  connect(speed_calculator1.u4, angles_Subsystem1.u4) annotation(
    Line(points = {{-78, 16}, {-26, 16}, {-26, 28}, {-22, 28}, {-22, 28}}, color = {0, 0, 127}));
  connect(speed_calculator1.u3, angles_Subsystem1.u3) annotation(
    Line(points = {{-78, 24}, {-28, 24}, {-28, 34}, {-22, 34}, {-22, 34}}, color = {0, 0, 127}));
  connect(speed_calculator1.u2, angles_Subsystem1.u2) annotation(
    Line(points = {{-78, 30}, {-30, 30}, {-30, 38}, {-22, 38}, {-22, 38}}, color = {0, 0, 127}));
  connect(speed_calculator1.omega, angles_Subsystem1.omega) annotation(
    Line(points = {{-78, 44}, {-36, 44}, {-36, 22}, {-22, 22}, {-22, 24}}, color = {0, 0, 127}));
  connect(step4.y, speed_calculator1.U4) annotation(
    Line(points = {{-173, -32}, {-150, -32}, {-150, 17}, {-109, 17}}, color = {0, 0, 127}));
  connect(step1.y, speed_calculator1.U1) annotation(
    Line(points = {{-172, 48}, {-152, 48}, {-152, 43}, {-109, 43}}, color = {0, 0, 127}));
  connect(step2.y, speed_calculator1.U2) annotation(
    Line(points = {{-171, 24}, {-141, 24}, {-141, 35}, {-109, 35}}, color = {0, 0, 127}));
  connect(step3.y, speed_calculator1.U3) annotation(
    Line(points = {{-173, -4}, {-152, -4}, {-152, 26}, {-109, 26}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Diagram(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    Icon(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Drone_Model;
