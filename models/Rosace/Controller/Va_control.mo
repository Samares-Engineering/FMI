model Va_control
  Modelica.Blocks.Interfaces.RealInput Va_f annotation(
    Placement(visible = true, transformation(origin = {-120, 70}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput Vz_f annotation(
    Placement(visible = true, transformation(origin = {-120, 20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput q_f annotation(
    Placement(visible = true, transformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput Va_c annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  parameter Real Ts_K1 = 1.0 / 50.0;
  Real integrator;
  /* Vz Speed controller */
  constant Real K1_intVa = 0.049802610664357;
  constant Real K1_Va = -0.486813084356079;
  constant Real K1_Vz = -0.077603095495388;
  constant Real K1_q = 21.692383376322041;
  constant Real Va_eq = 230.0;
  constant Real delta_th_eq = 1.5868660794926;
equation
  y = K1_intVa * integrator + K1_Va * (Va_f - Va_eq) + K1_Vz * Vz_f + K1_q * q_f + delta_th_eq;
//integrator = pre(integrator) + Ts_K1 * (Va_c - Va_f + Va_eq);
  integrator = integrator + Ts_K1 * (Va_c - Va_f + Va_eq);
  annotation(
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 10}, extent = {{-60, 30}, {60, -30}}, textString = "%name%")}));
end Va_control;
