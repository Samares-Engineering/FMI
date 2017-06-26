model Quadrotor
  Position_controller Position_controller1 annotation(
    Placement(visible = true, transformation(origin = {-40, 32}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  AA_control aA_control annotation(
    Placement(visible = true, transformation(origin = {10, 30}, extent = {{-10, -20}, {10, 20}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Xd annotation(
    Placement(visible = true, transformation(origin = {-94, 52}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Yd annotation(
    Placement(visible = true, transformation(origin = {-94, 38}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Zd annotation(
    Placement(visible = true, transformation(origin = {-94, 26}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Psid annotation(
    Placement(visible = true, transformation(origin = {-94, 14}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  System_Model system_Model annotation(
    Placement(visible = true, transformation(origin = {54, 32}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
equation
  connect(system_Model.Z, Position_controller1.Z) annotation(
    Line(points = {{66, 26}, {80, 26}, {80, 2}, {-60, 2}, {-60, 22}, {-52, 22}, {-52, 22}}, color = {0, 0, 127}));
  connect(system_Model.Y, Position_controller1.Y) annotation(
    Line(points = {{66, 28}, {78, 28}, {78, 70}, {-64, 70}, {-64, 32}, {-52, 32}, {-52, 32}}, color = {0, 0, 127}));
  connect(system_Model.X, Position_controller1.X) annotation(
    Line(points = {{66, 32}, {76, 32}, {76, 68}, {-60, 68}, {-60, 42}, {-52, 42}, {-52, 42}}, color = {0, 0, 127}));
  connect(system_Model.Psi, aA_control.Psi) annotation(
    Line(points = {{66, 36}, {74, 36}, {74, 64}, {-12, 64}, {-12, 42}, {-2, 42}, {-2, 42}}, color = {0, 0, 127}));
  connect(system_Model.Theta, aA_control.Theta) annotation(
    Line(points = {{66, 38}, {72, 38}, {72, 62}, {-10, 62}, {-10, 48}, {-2, 48}, {-2, 48}}, color = {0, 0, 127}));
  connect(system_Model.Phi, aA_control.Phi) annotation(
    Line(points = {{66, 42}, {70, 42}, {70, 60}, {-8, 60}, {-8, 54}, {-2, 54}, {-2, 54}}, color = {0, 0, 127}));
  connect(aA_control.tau_psi, system_Model.tau_psi) annotation(
    Line(points = {{22, 20}, {42, 20}, {42, 22}, {42, 22}}, color = {0, 0, 127}));
  connect(aA_control.tau_theta, system_Model.tau_theta) annotation(
    Line(points = {{22, 26}, {40, 26}, {40, 28}, {42, 28}}, color = {0, 0, 127}));
  connect(aA_control.tau_phi, system_Model.tau_phi) annotation(
    Line(points = {{22, 36}, {40, 36}, {40, 36}, {42, 36}}, color = {0, 0, 127}));
  connect(aA_control.T, system_Model.T) annotation(
    Line(points = {{22, 40}, {40, 40}, {40, 42}, {42, 42}}, color = {0, 0, 127}));
  connect(system_Model.Omega, aA_control.Omega) annotation(
    Line(points = {{66, 22}, {68, 22}, {68, -2}, {-6, -2}, {-6, 6}, {-2, 6}, {-2, 6}}, color = {0, 0, 127}));
  connect(Position_controller1.Z, aA_control.Z) annotation(
    Line(points = {{-52, 22}, {-60, 22}, {-60, 2}, {-12, 2}, {-12, 18}, {-2, 18}}, color = {0, 0, 127}));
  connect(aA_control.Psid, Psid.y) annotation(
    Line(points = {{-2, 24}, {-10, 24}, {-10, 20}, {-28, 20}, {-28, 4}, {-90, 4}, {-90, 14}}, color = {0, 0, 127}));
  connect(Psid.y, Position_controller1.Psid) annotation(
    Line(points = {{-90, 14}, {-71, 14}, {-71, 16}, {-52, 16}}, color = {0, 0, 127}));
  connect(aA_control.Zd, Zd.y) annotation(
    Line(points = {{-2, 12}, {-70, 12}, {-70, 26}, {-90, 26}, {-90, 26}}, color = {0, 0, 127}));
  connect(Zd.y, Position_controller1.Zd) annotation(
    Line(points = {{-90, 26}, {-52, 26}}, color = {0, 0, 127}));
  connect(Xd.y, Position_controller1.Xd) annotation(
    Line(points = {{-90, 52}, {-70, 52}, {-70, 46}, {-52, 46}, {-52, 48}}, color = {0, 0, 127}));
  connect(Yd.y, Position_controller1.Yd) annotation(
    Line(points = {{-90, 38}, {-52, 38}}, color = {0, 0, 127}));
  connect(Position_controller1.Thetad, aA_control.Thetad) annotation(
    Line(points = {{-28, 24}, {-12, 24}, {-12, 30}, {-2, 30}, {-2, 30}}, color = {0, 0, 127}));
  connect(Position_controller1.Phid, aA_control.Phid) annotation(
    Line(points = {{-28, 40}, {-12, 40}, {-12, 36}, {-2, 36}, {-2, 36}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end Quadrotor;
