model Quadrotor_FMU
  Position_controller Position_controller1 annotation(
    Placement(visible = true, transformation(origin = {-40, 32}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  AA_control aA_control annotation(
    Placement(visible = true, transformation(origin = {12, 30}, extent = {{-10, -20}, {10, 20}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Xd annotation(
    Placement(visible = true, transformation(origin = {-94, 52}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Yd annotation(
    Placement(visible = true, transformation(origin = {-94, 38}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Zd annotation(
    Placement(visible = true, transformation(origin = {-94, 26}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Psid annotation(
    Placement(visible = true, transformation(origin = {-94, 14}, extent = {{-4, -4}, {4, 4}}, rotation = 0)));
  System_Model_me_FMU system_Model_me_FMU2 annotation(
    Placement(visible = true, transformation(origin = {66, 8}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(system_Model_me_FMU2.Omega, aA_control.Phi) annotation(
    Line(points = {{78, 16}, {86, 16}, {86, 62}, {-8, 62}, {-8, 54}, {0, 54}, {0, 54}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.Phi, aA_control.Theta) annotation(
    Line(points = {{78, 12}, {82, 12}, {82, 60}, {-14, 60}, {-14, 48}, {0, 48}, {0, 48}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.Psi, aA_control.Psi) annotation(
    Line(points = {{78, 10}, {96, 10}, {96, -18}, {-10, -18}, {-10, 42}, {0, 42}, {0, 42}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.Theta, Position_controller1.X) annotation(
    Line(points = {{78, 8}, {94, 8}, {94, -16}, {-74, -16}, {-74, 42}, {-52, 42}, {-52, 42}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.X, Position_controller1.Y) annotation(
    Line(points = {{78, 4}, {92, 4}, {92, -12}, {-66, -12}, {-66, 32}, {-52, 32}, {-52, 32}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.Y, Position_controller1.Z) annotation(
    Line(points = {{78, 2}, {86, 2}, {86, -4}, {-64, -4}, {-64, 22}, {-52, 22}, {-52, 22}}, color = {0, 0, 127}));
  connect(system_Model_me_FMU2.Z, aA_control.Omega) annotation(
    Line(points = {{78, 0}, {80, 0}, {80, -4}, {-6, -4}, {-6, 6}, {0, 6}, {0, 6}}, color = {0, 0, 127}));
  connect(aA_control.T, system_Model_me_FMU2.T) annotation(
    Line(points = {{24, 40}, {46, 40}, {46, 15}, {55, 15}}, color = {0, 0, 127}));
  connect(aA_control.tau_phi, system_Model_me_FMU2.tau_phi) annotation(
    Line(points = {{24, 36}, {44, 36}, {44, 13}, {55, 13}}, color = {0, 0, 127}));
  connect(aA_control.tau_theta, system_Model_me_FMU2.tau_psi) annotation(
    Line(points = {{24, 26}, {42, 26}, {42, 10}, {55, 10}}, color = {0, 0, 127}));
  connect(aA_control.tau_psi, system_Model_me_FMU2.tau_theta) annotation(
    Line(points = {{24, 20}, {40, 20}, {40, 7}, {55, 7}}, color = {0, 0, 127}));
  connect(Position_controller1.Phid, aA_control.Phid) annotation(
    Line(points = {{-28, 40}, {-12, 40}, {-12, 36}, {0, 36}}, color = {0, 0, 127}));
  connect(Position_controller1.Thetad, aA_control.Thetad) annotation(
    Line(points = {{-28, 24}, {-12, 24}, {-12, 30}, {0, 30}}, color = {0, 0, 127}));
  connect(aA_control.Zd, Zd.y) annotation(
    Line(points = {{0, 12}, {-70, 12}, {-70, 26}, {-90, 26}}, color = {0, 0, 127}));
  connect(aA_control.Psid, Psid.y) annotation(
    Line(points = {{0, 24}, {-10, 24}, {-10, 20}, {-28, 20}, {-28, 4}, {-90, 4}, {-90, 14}}, color = {0, 0, 127}));
  connect(Position_controller1.Z, aA_control.Z) annotation(
    Line(points = {{-52, 22}, {-60, 22}, {-60, 2}, {-12, 2}, {-12, 18}, {0, 18}}, color = {0, 0, 127}));
  connect(Psid.y, Position_controller1.Psid) annotation(
    Line(points = {{-90, 14}, {-71, 14}, {-71, 16}, {-52, 16}}, color = {0, 0, 127}));
  connect(Zd.y, Position_controller1.Zd) annotation(
    Line(points = {{-90, 26}, {-52, 26}}, color = {0, 0, 127}));
  connect(Xd.y, Position_controller1.Xd) annotation(
    Line(points = {{-90, 52}, {-70, 52}, {-70, 46}, {-52, 46}, {-52, 48}}, color = {0, 0, 127}));
  connect(Yd.y, Position_controller1.Yd) annotation(
    Line(points = {{-90, 38}, {-52, 38}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")));
end Quadrotor_FMU;
