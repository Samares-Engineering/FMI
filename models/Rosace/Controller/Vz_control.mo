model Vz_control
  Modelica.Blocks.Interfaces.RealInput Vz_f annotation(
    Placement(visible = true, transformation(origin = {-120, 70}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput Vz_c annotation(
    Placement(visible = true, transformation(origin = {-120, 20}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput q_f annotation(
    Placement(visible = true, transformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput az_f annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  parameter Real Ts_K2 = 1.0 / 50.0;
  Real integrator;
  /* Vz Speed controller */
  constant Real K2_intVz = 0.000627342822264;
  constant Real K2_Vz = -0.003252836726554;
  constant Real K2_q = 0.376071446897134;
  constant Real K2_az = -0.001566907423747;
  constant Real delta_e_eq = 0.012009615652468;
equation
  y = K2_intVz * integrator + K2_Vz * Vz_f + K2_q * q_f + K2_az * az_f + delta_e_eq;
//integrator = pre(integrator) + Ts_K2 * (Vz_c - Vz_f);
  integrator = integrator + Ts_K2 * (Vz_c - Vz_f);
  annotation(
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 10}, extent = {{-60, 30}, {60, -30}}, textString = "%name%")}));
end Vz_control;
