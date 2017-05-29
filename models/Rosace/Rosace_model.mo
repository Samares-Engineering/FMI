model Rosace_model
  Va_filter va_filter1 annotation(
    Placement(visible = true, transformation(origin = {90, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Vz_filter vz_filter1 annotation(
    Placement(visible = true, transformation(origin = {90, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Q_filter q_filter1 annotation(
    Placement(visible = true, transformation(origin = {90, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Az_filter az_filter1 annotation(
    Placement(visible = true, transformation(origin = {90, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  H_filter h_filter1 annotation(
    Placement(visible = true, transformation(origin = {90, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Altitude_hold altitude_hold1 annotation(
    Placement(visible = true, transformation(origin = {142, -64}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Vz_control vz_control1 annotation(
    Placement(visible = true, transformation(origin = {190, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Va_control va_control1 annotation(
    Placement(visible = true, transformation(origin = {190, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.RealExpression realExpression1(y = 0.0) annotation(
    Placement(visible = true, transformation(origin = {224, 6}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.RealExpression realExpression2(y = 11000) annotation(
    Placement(visible = true, transformation(origin = {80, -86}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Aircraft_Dynamics aircraft_Dynamics annotation(
    Placement(visible = true, transformation(origin = {28, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Engine engine annotation(
    Placement(visible = true, transformation(origin = {-30, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Elevator elevator annotation(
    Placement(visible = true, transformation(origin = {-30, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(vz_control1.y, elevator.delta_e_c) annotation(
    Line(points = {{202, -10}, {220, -10}, {220, -100}, {-60, -100}, {-60, -30}, {-42, -30}, {-42, -30}}, color = {0, 0, 127}));
  connect(elevator.y, aircraft_Dynamics.delta_e) annotation(
    Line(points = {{-19, -30}, {0, -30}, {0, -6}, {16, -6}}, color = {0, 0, 127}));
  connect(va_control1.y, engine.delta_th_c) annotation(
    Line(points = {{202, 30}, {220, 30}, {220, 80}, {-60, 80}, {-60, 30}, {-42, 30}, {-42, 30}}, color = {0, 0, 127}));
  connect(engine.y, aircraft_Dynamics.T) annotation(
    Line(points = {{-18, 30}, {0, 30}, {0, 6}, {16, 6}, {16, 6}}, color = {0, 0, 127}));
  connect(va_filter1.Va, aircraft_Dynamics.Va) annotation(
    Line(points = {{78, 60}, {48, 60}, {48, 8}, {39, 8}}, color = {0, 0, 127}));
  connect(h_filter1.h, aircraft_Dynamics.h_out) annotation(
    Line(points = {{78, -60}, {48, -60}, {48, -8}, {40, -8}, {40, -8}}, color = {0, 0, 127}));
  connect(vz_filter1.Vz, aircraft_Dynamics.Vz) annotation(
    Line(points = {{78, 30}, {59.5, 30}, {59.5, 4}, {39, 4}}, color = {0, 0, 127}));
  connect(az_filter1.az, aircraft_Dynamics.az) annotation(
    Line(points = {{78, -30}, {60, -30}, {60, -4}, {40, -4}, {40, -4}}, color = {0, 0, 127}));
  connect(q_filter1.q, aircraft_Dynamics.q_out) annotation(
    Line(points = {{78, 0}, {38, 0}, {38, 0}, {40, 0}}, color = {0, 0, 127}));
  connect(realExpression2.y, altitude_hold1.h_f) annotation(
    Line(points = {{92, -86}, {120, -86}, {120, -70}, {130, -70}, {130, -72}}, color = {0, 0, 127}));
  connect(realExpression1.y, va_control1.Va_c) annotation(
    Line(points = {{235, 6}, {244, 6}, {244, 16}, {169, 16}, {169, 22}, {178, 22}}, color = {0, 0, 127}));
  connect(q_filter1.y, va_control1.q_f) annotation(
    Line(points = {{102, 0}, {148, 0}, {148, 28}, {178, 28}, {178, 26}}, color = {0, 0, 127}));
  connect(vz_filter1.y, va_control1.Vz_f) annotation(
    Line(points = {{102, 30}, {164, 30}, {164, 34}, {178, 34}, {178, 34}}, color = {0, 0, 127}));
  connect(va_filter1.y, va_control1.Va_f) annotation(
    Line(points = {{102, 60}, {166, 60}, {166, 38}, {178, 38}, {178, 38}}, color = {0, 0, 127}));
  connect(vz_filter1.y, vz_control1.Vz_f) annotation(
    Line(points = {{102, 30}, {158, 30}, {158, -2}, {178, -2}, {178, -2}}, color = {0, 0, 127}));
  connect(q_filter1.y, vz_control1.q_f) annotation(
    Line(points = {{102, 0}, {140, 0}, {140, -12}, {178, -12}, {178, -14}}, color = {0, 0, 127}));
  connect(az_filter1.y, vz_control1.az_f) annotation(
    Line(points = {{102, -30}, {168, -30}, {168, -18}, {178, -18}, {178, -18}}, color = {0, 0, 127}));
  connect(altitude_hold1.y, vz_control1.Vz_c) annotation(
    Line(points = {{154, -64}, {162, -64}, {162, -6}, {178, -6}, {178, -6}}, color = {0, 0, 127}));
  connect(h_filter1.y, altitude_hold1.h_c) annotation(
    Line(points = {{102, -60}, {120, -60}, {120, -59}, {130, -59}}, color = {0, 0, 127}));
  annotation(
    Diagram(coordinateSystem(extent = {{-100, -100}, {250, 100}})),
    Icon(coordinateSystem(extent = {{-100, -100}, {250, 100}})),
    __OpenModelica_commandLineOptions = "");
end Rosace_model;
