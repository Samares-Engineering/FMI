model Displacement_Subsystem
  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {-40, 8}, extent = {{-10, -16}, {10, 14}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput phi annotation(
    Placement(visible = true, transformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput theta annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput psi annotation(
    Placement(visible = true, transformation(origin = {-120, -20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -20}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput u1 annotation(
    Placement(visible = true, transformation(origin = {-120, -70}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -70}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput x annotation(
    Placement(visible = true, transformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput z annotation(
    Placement(visible = true, transformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator1 annotation(
    Placement(visible = true, transformation(origin = {28, 52}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator2 annotation(
    Placement(visible = true, transformation(origin = {66, 52}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator3 annotation(
    Placement(visible = true, transformation(origin = {28, 16}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator4 annotation(
    Placement(visible = true, transformation(origin = {64, 16}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator5 annotation(
    Placement(visible = true, transformation(origin = {26, -26}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Continuous.Integrator integrator6 annotation(
    Placement(visible = true, transformation(origin = {58, -26}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(u1, displacement1.u1) annotation(
    Line(points = {{-120, -70}, {-74, -70}, {-74, 22}, {-52, 22}, {-52, 22}}, color = {0, 0, 127}));
  connect(psi, displacement1.Psi) annotation(
    Line(points = {{-120, -20}, {-80, -20}, {-80, 8}, {-52, 8}, {-52, 8}}, color = {0, 0, 127}));
  connect(theta, displacement1.Theta) annotation(
    Line(points = {{-120, 30}, {-80, 30}, {-80, 12}, {-52, 12}, {-52, 14}}, color = {0, 0, 127}));
  connect(phi, displacement1.Phi) annotation(
    Line(points = {{-120, 80}, {-78, 80}, {-78, 18}, {-52, 18}, {-52, 18}}, color = {0, 0, 127}));
  connect(integrator5.y, displacement1.Z_dot) annotation(
    Line(points = {{38, -26}, {42, -26}, {42, 66}, {-66, 66}, {-66, -8}, {-52, -8}, {-52, -8}}, color = {0, 0, 127}));
  connect(integrator3.y, displacement1.Y_dot) annotation(
    Line(points = {{40, 16}, {48, 16}, {48, 86}, {-62, 86}, {-62, -2}, {-52, -2}, {-52, -2}}, color = {0, 0, 127}));
  connect(integrator6.y, z) annotation(
    Line(points = {{70, -26}, {82, -26}, {82, -60}, {110, -60}, {110, -60}}, color = {0, 0, 127}));
  connect(integrator5.y, integrator6.u) annotation(
    Line(points = {{38, -26}, {46, -26}, {46, -26}, {46, -26}}, color = {0, 0, 127}));
  connect(displacement1.Z_dot_dot, integrator5.u) annotation(
    Line(points = {{-28, -2}, {2, -2}, {2, -28}, {14, -28}, {14, -26}}, color = {0, 0, 127}));
  connect(integrator4.y, y) annotation(
    Line(points = {{76, 16}, {86, 16}, {86, 0}, {110, 0}, {110, 0}}, color = {0, 0, 127}));
  connect(integrator3.y, integrator4.u) annotation(
    Line(points = {{40, 16}, {50, 16}, {50, 16}, {52, 16}}, color = {0, 0, 127}));
  connect(displacement1.Y_dot_dot, integrator3.u) annotation(
    Line(points = {{-28, 8}, {4, 8}, {4, 16}, {16, 16}, {16, 16}}, color = {0, 0, 127}));
  connect(integrator1.y, displacement1.X_dot) annotation(
    Line(points = {{40, 52}, {50, 52}, {50, 82}, {-70, 82}, {-70, 2}, {-52, 2}, {-52, 2}}, color = {0, 0, 127}));
  connect(integrator2.y, x) annotation(
    Line(points = {{78, 52}, {90, 52}, {90, 60}, {110, 60}, {110, 60}}, color = {0, 0, 127}));
  connect(integrator1.y, integrator2.u) annotation(
    Line(points = {{40, 52}, {52, 52}, {52, 52}, {54, 52}}, color = {0, 0, 127}));
  connect(displacement1.X_dot_dot, integrator1.u) annotation(
    Line(points = {{-28, 18}, {-8, 18}, {-8, 52}, {16, 52}, {16, 52}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(graphics = {Rectangle(origin = {-77, 91}, extent = {{-23, 9}, {177, -191}})}));
end Displacement_Subsystem;
