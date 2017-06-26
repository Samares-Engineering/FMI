model Drone_Model
  Speed_calculator speed_calculator1 annotation(
    Placement(visible = true, transformation(origin = {-92.408, 29.891}, extent = {{-13.7424, -16.491}, {13.7424, 16.491}}, rotation = 0)));
  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {73.201, 31.8561}, extent = {{-12.3588, -19.7742}, {12.3588, 17.3024}}, rotation = 0)));
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {-3, 26.56}, extent = {{-9, -12.96}, {9, 12.96}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step1(height = 200) annotation(
    Placement(visible = true, transformation(origin = {-184, 48}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step2(height = 250) annotation(
    Placement(visible = true, transformation(origin = {-182, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step3(height = 200) annotation(
    Placement(visible = true, transformation(origin = {-184, -4}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step step4(height = 200) annotation(
    Placement(visible = true, transformation(origin = {-184, -32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(step4.y, speed_calculator1.U4) annotation(
    Line(points = {{-173, -32}, {-150, -32}, {-150, 17}, {-109, 17}}, color = {0, 0, 127}));
  connect(angles1.Phi, displacement1.Phi) annotation(
    Line(points = {{7, 36}, {16.5, 36}, {16.5, 37}, {58, 37}}, color = {0, 0, 127}));
  connect(angles1.Theta, displacement1.Theta) annotation(
    Line(points = {{7, 27}, {58, 27}}, color = {0, 0, 127}));
  connect(angles1.Psi, displacement1.Psi) annotation(
    Line(points = {{7, 17}, {36.5, 17}, {36.5, 18}, {58, 18}}, color = {0, 0, 127}));
  connect(speed_calculator1.u1, angles1.u2) annotation(
    Line(points = {{-77, 36}, {-14, 36}}, color = {0, 0, 127}));
  connect(speed_calculator1.u2, angles1.u3) annotation(
    Line(points = {{-77, 30}, {-14, 30}}, color = {0, 0, 127}));
  connect(speed_calculator1.u3, angles1.u4) annotation(
    Line(points = {{-77, 23}, {-14, 23}}, color = {0, 0, 127}));
  connect(speed_calculator1.u4, angles1.omega) annotation(
    Line(points = {{-77, 17}, {-14, 17}}, color = {0, 0, 127}));
  connect(speed_calculator1.omega, displacement1.u1) annotation(
    Line(points = {{-77, 43}, {-10.5, 43}, {-10.5, 45}, {58, 45}}, color = {0, 0, 127}));
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
