model Drone_Model1
  Modelica.Blocks.Sources.Step Xd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-182, 58}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Yd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-182, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Zd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-184, -4}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Psid(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-184, -32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Position_controller position_controller1 annotation(
    Placement(visible = true, transformation(origin = {-107, 16.8}, extent = {{-21, -25.2}, {21, 25.2}}, rotation = 0)));
  AA_control aA_control1 annotation(
    Placement(visible = true, transformation(origin = {-45.5, -1}, extent = {{-14.5, -29}, {14.5, 29}}, rotation = 0)));
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {56, 10}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {100, 12}, extent = {{-10, -16}, {10, 14}}, rotation = 0)));
  Speed_calculator speed_calculator1 annotation(
    Placement(visible = true, transformation(origin = {6, 6}, extent = {{-18, -18}, {18, 18}}, rotation = 0)));
equation
  connect(Xd.y, position_controller1.Xd) annotation(
    Line(points = {{-170, 58}, {-154, 58}, {-154, 38}, {-132, 38}}, color = {0, 0, 127}));
  connect(Yd.y, position_controller1.Yd) annotation(
    Line(points = {{-170, 24}, {-132, 24}}, color = {0, 0, 127}));
  connect(Zd.y, position_controller1.Zd) annotation(
    Line(points = {{-172, -4}, {-132, -4}, {-132, 10}}, color = {0, 0, 127}));
  connect(position_controller1.Phid, aA_control1.Phid) annotation(
    Line(points = {{-84, 27}, {-76.5, 27}, {-76.5, 16}, {-63, 16}}, color = {0, 0, 127}));
  connect(position_controller1.Thetad, aA_control1.Thetad) annotation(
    Line(points = {{-84, 6}, {-63, 6}, {-63, -1}}, color = {0, 0, 127}));
  connect(displacement1.X, position_controller1.X) annotation(
    Line(points = {{112, 22}, {114, 22}, {114, 80}, {-144, 80}, {-144, 28}, {-132, 28}, {-132, 31}}, color = {0, 0, 127}));
  connect(displacement1.Y, position_controller1.Y) annotation(
    Line(points = {{112, 12}, {116, 12}, {116, 84}, {-148, 84}, {-148, 17}, {-132, 17}}, color = {0, 0, 127}));
  connect(position_controller1.Z, displacement1.Z) annotation(
    Line(points = {{-132, 3}, {-148, 3}, {-148, -42}, {120, -42}, {120, 2}, {112, 2}}, color = {0, 0, 127}));
  connect(position_controller1.Psid, Psid.y) annotation(
    Line(points = {{-132, -4}, {-172, -4}, {-172, -32}}, color = {0, 0, 127}));
  connect(aA_control1.tau_psi, speed_calculator1.U4) annotation(
    Line(points = {{-30, -30}, {-18, -30}, {-18, -8}, {-16, -8}}, color = {0, 0, 127}));
  connect(aA_control1.tau_theta, speed_calculator1.U3) annotation(
    Line(points = {{-30, -15}, {-25, -15}, {-25, 2}, {-16, 2}}, color = {0, 0, 127}));
  connect(aA_control1.tau_phi, speed_calculator1.U2) annotation(
    Line(points = {{-30, 13}, {-16, 13}, {-16, 12}}, color = {0, 0, 127}));
  connect(aA_control1.T, speed_calculator1.U1) annotation(
    Line(points = {{-30, 28}, {-16, 28}, {-16, 20}}, color = {0, 0, 127}));
  connect(aA_control1.Omega, angles1.omega) annotation(
    Line(points = {{-63, -71}, {-70, -71}, {-70, -38}, {44, -38}, {44, 1}}, color = {0, 0, 127}));
  connect(aA_control1.Psid, Psid.y) annotation(
    Line(points = {{-63, -18}, {-82, -18}, {-82, -32}, {-172, -32}}, color = {0, 0, 127}));
  connect(aA_control1.Z, displacement1.Z) annotation(
    Line(points = {{-63, -36}, {-80, -36}, {-80, -44}, {114, -44}, {114, 4}, {112, 4}, {112, 2}}, color = {0, 0, 127}));
  connect(aA_control1.Zd, Zd.y) annotation(
    Line(points = {{-63, -53}, {-78, -53}, {-78, -38}, {-162, -38}, {-162, -4}, {-172, -4}}, color = {0, 0, 127}));
  connect(aA_control1.Psi, angles1.Psi) annotation(
    Line(points = {{-63, 34}, {-78, 34}, {-78, 64}, {80, 64}, {80, 1}, {67, 1}}, color = {0, 0, 127}));
  connect(aA_control1.Theta, angles1.Theta) annotation(
    Line(points = {{-63, 51}, {-76, 51}, {-76, 60}, {76, 60}, {76, 10}, {67, 10}}, color = {0, 0, 127}));
  connect(aA_control1.Phi, angles1.Phi) annotation(
    Line(points = {{-63, 69}, {-74, 69}, {-74, 56}, {74, 56}, {74, 19}, {67, 19}}, color = {0, 0, 127}));
  connect(displacement1.u1, speed_calculator1.u1) annotation(
    Line(points = {{88, 24}, {32, 24}, {32, 14}, {26, 14}, {26, 14}}, color = {0, 0, 127}));
  connect(speed_calculator1.omega, angles1.omega) annotation(
    Line(points = {{26, 20}, {36, 20}, {36, 2}, {44, 2}, {44, 0}}, color = {0, 0, 127}));
  connect(angles1.u2, speed_calculator1.u2) annotation(
    Line(points = {{44, 20}, {38, 20}, {38, 6}, {26, 6}, {26, 6}}, color = {0, 0, 127}));
  connect(angles1.u3, speed_calculator1.u3) annotation(
    Line(points = {{44, 14}, {34, 14}, {34, -2}, {26, -2}, {26, -2}}, color = {0, 0, 127}));
  connect(speed_calculator1.u4, angles1.u4) annotation(
    Line(points = {{26, -8}, {40, -8}, {40, 6}, {44, 6}, {44, 6}}, color = {0, 0, 127}));
  connect(angles1.Phi, displacement1.Phi) annotation(
    Line(points = {{67, 19}, {86, 19}, {86, 16}, {88, 16}}, color = {0, 0, 127}));
  connect(angles1.Theta, displacement1.Theta) annotation(
    Line(points = {{67, 10}, {79.5, 10}, {79.5, 8}, {88, 8}}, color = {0, 0, 127}));
  connect(angles1.Psi, displacement1.Psi) annotation(
    Line(points = {{67, 1}, {78, 1}, {78, 0}, {88, 0}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Diagram(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    Icon(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Drone_Model1;