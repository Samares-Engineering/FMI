model Drone_Model_FMU
  Modelica.Blocks.Sources.Step Xd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-182, 58}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Yd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-182, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Zd(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-184, -4}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Step Psid(height = 1, startTime = 0) annotation(
    Placement(visible = true, transformation(origin = {-184, -32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Position_controller position_controller1 annotation(
    Placement(visible = true, transformation(origin = {-109, 8.8}, extent = {{-21, -25.2}, {21, 25.2}}, rotation = 0)));
  AA_control aA_control1 annotation(
    Placement(visible = true, transformation(origin = {-49.5, 9}, extent = {{-14.5, -29}, {14.5, 29}}, rotation = 0)));
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {56, 10}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {100, 12}, extent = {{-10, -16}, {10, 14}}, rotation = 0)));
  Speed_calculator_me_FMU speed_calculator_me_FMU1 annotation(
    Placement(visible = true, transformation(origin = {5, 11}, extent = {{-17, -17}, {17, 17}}, rotation = 0)));
equation
  connect(speed_calculator_me_FMU1.u4, angles1.u4) annotation(
    Line(points = {{24, 6}, {42, 6}, {42, 8}, {44, 8}}, color = {0, 0, 127}));
  connect(speed_calculator_me_FMU1.u3, angles1.u3) annotation(
    Line(points = {{24, 10}, {38, 10}, {38, 14}, {44, 14}, {44, 14}}, color = {0, 0, 127}));
  connect(speed_calculator_me_FMU1.u2, angles1.u2) annotation(
    Line(points = {{24, 14}, {34, 14}, {34, 18}, {44, 18}, {44, 20}}, color = {0, 0, 127}));
  connect(speed_calculator_me_FMU1.u1, displacement1.u1) annotation(
    Line(points = {{24, 18}, {30, 18}, {30, 30}, {86, 30}, {86, 22}, {88, 22}, {88, 24}}, color = {0, 0, 127}));
  connect(speed_calculator_me_FMU1.omega, angles1.omega) annotation(
    Line(points = {{24, 22}, {28, 22}, {28, 0}, {44, 0}, {44, 2}}, color = {0, 0, 127}));
  connect(aA_control1.tau_psi, speed_calculator_me_FMU1.U4) annotation(
    Line(points = {{-34, -6}, {-16, -6}, {-16, 10}, {-14, 10}}, color = {0, 0, 127}));
  connect(aA_control1.tau_theta, speed_calculator_me_FMU1.U3) annotation(
    Line(points = {{-34, 2}, {-20, 2}, {-20, 14}, {-14, 14}}, color = {0, 0, 127}));
  connect(aA_control1.tau_phi, speed_calculator_me_FMU1.U2) annotation(
    Line(points = {{-34, 16}, {-22, 16}, {-22, 19}, {-14, 19}}, color = {0, 0, 127}));
  connect(aA_control1.T, speed_calculator_me_FMU1.U1) annotation(
    Line(points = {{-34, 24}, {-14, 24}, {-14, 23}}, color = {0, 0, 127}));
  connect(angles1.Phi, displacement1.Phi) annotation(
    Line(points = {{67, 19}, {86, 19}, {86, 16}, {88, 16}}, color = {0, 0, 127}));
  connect(angles1.Theta, displacement1.Theta) annotation(
    Line(points = {{67, 10}, {79.5, 10}, {79.5, 8}, {88, 8}}, color = {0, 0, 127}));
  connect(angles1.Psi, displacement1.Psi) annotation(
    Line(points = {{67, 1}, {78, 1}, {78, 0}, {88, 0}}, color = {0, 0, 127}));
  connect(aA_control1.Phi, angles1.Phi) annotation(
    Line(points = {{-66, 44}, {-74, 44}, {-74, 56}, {74, 56}, {74, 19}, {67, 19}}, color = {0, 0, 127}));
  connect(aA_control1.Theta, angles1.Theta) annotation(
    Line(points = {{-66, 36}, {-76, 36}, {-76, 60}, {76, 60}, {76, 10}, {67, 10}}, color = {0, 0, 127}));
  connect(aA_control1.Psi, angles1.Psi) annotation(
    Line(points = {{-66, 26}, {-78, 26}, {-78, 64}, {80, 64}, {80, 1}, {67, 1}}, color = {0, 0, 127}));
  connect(aA_control1.Omega, angles1.omega) annotation(
    Line(points = {{-66, -26}, {-70, -26}, {-70, -38}, {44, -38}, {44, 1}}, color = {0, 0, 127}));
  connect(aA_control1.Zd, Zd.y) annotation(
    Line(points = {{-66, -18}, {-78, -18}, {-78, -38}, {-162, -38}, {-162, -4}, {-172, -4}, {-172, -4}}, color = {0, 0, 127}));
  connect(position_controller1.Psid, Psid.y) annotation(
    Line(points = {{-134, -22}, {-172, -22}, {-172, -32}, {-172, -32}}, color = {0, 0, 127}));
  connect(position_controller1.Z, displacement1.Z) annotation(
    Line(points = {{-134, -12}, {-148, -12}, {-148, -42}, {120, -42}, {120, 2}, {112, 2}, {112, 2}, {112, 2}}, color = {0, 0, 127}));
  connect(displacement1.Y, position_controller1.Y) annotation(
    Line(points = {{112, 12}, {116, 12}, {116, 84}, {-148, 84}, {-148, 8}, {-134, 8}, {-134, 8}}, color = {0, 0, 127}));
  connect(displacement1.X, position_controller1.X) annotation(
    Line(points = {{112, 22}, {114, 22}, {114, 80}, {-144, 80}, {-144, 28}, {-134, 28}, {-134, 30}}, color = {0, 0, 127}));
  connect(aA_control1.Z, displacement1.Z) annotation(
    Line(points = {{-66, -8}, {-80, -8}, {-80, -44}, {114, -44}, {114, 4}, {112, 4}, {112, 2}, {112, 2}}, color = {0, 0, 127}));
  connect(aA_control1.Psid, Psid.y) annotation(
    Line(points = {{-66, 0}, {-82, 0}, {-82, -32}, {-174, -32}, {-174, -32}, {-172, -32}}, color = {0, 0, 127}));
  connect(position_controller1.Thetad, aA_control1.Thetad) annotation(
    Line(points = {{-86, -6}, {-86, -6}, {-86, 10}, {-66, 10}, {-66, 8}}, color = {0, 0, 127}));
  connect(position_controller1.Phid, aA_control1.Phid) annotation(
    Line(points = {{-86, 24}, {-80, 24}, {-80, 18}, {-66, 18}, {-66, 18}}, color = {0, 0, 127}));
  connect(Zd.y, position_controller1.Zd) annotation(
    Line(points = {{-172, -4}, {-134, -4}, {-134, -2}, {-134, -2}}, color = {0, 0, 127}));
  connect(Yd.y, position_controller1.Yd) annotation(
    Line(points = {{-170, 24}, {-160, 24}, {-160, 18}, {-134, 18}, {-134, 20}}, color = {0, 0, 127}));
  connect(Xd.y, position_controller1.Xd) annotation(
    Line(points = {{-170, 58}, {-154, 58}, {-154, 40}, {-134, 40}, {-134, 40}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Diagram(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    Icon(coordinateSystem(extent = {{-200, -100}, {150, 100}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Drone_Model_FMU;
