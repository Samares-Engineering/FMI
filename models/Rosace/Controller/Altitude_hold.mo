model Altitude_hold
  Modelica.Blocks.Interfaces.RealInput h_f annotation(
    Placement(visible = true, transformation(origin = {-120, 60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -70}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput h_c annotation(
    Placement(visible = true, transformation(origin = {-120, -60}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  parameter Real Vz_c = -2.5;
  parameter Real Ts_h = 1.0 / 50.0;
  constant Real Kp_h = 0.1014048;
  constant Real Ki_h = 0.0048288;
  Real integrator(start = 532.2730285);
algorithm
  if h_f - h_c < (-50) then
    y := Vz_c;
  elseif h_f - h_c > 50 then
    y := -Vz_c;
  else
    y := Kp_h * (h_f - h_c) + Ki_h * integrator;
    integrator := integrator + Ts_h * (h_f - h_c);
  end if;
  annotation(
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 10}, extent = {{-60, 30}, {60, -30}}, textString = "%name%")}));
end Altitude_hold;
