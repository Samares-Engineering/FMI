model Va_filter
  Modelica.Blocks.Interfaces.RealInput Va annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Real x1(start = -219.895);
  Real x2(start = 230.0);
  constant Real Va_eq = 230.0;
  parameter Real a0 = 0.956543675476034;
  parameter Real a1 = -1.955578398054313;
  parameter Real b0 = 0.000479064865372430;
  parameter Real b1 = 0.000486212556348925;
equation
//Output equation
  y = x2;
//State equation
  x1 = (-a0 * x2) + b0 * Va;
  x2 = x1 - a1 * x2 + b1 * Va;
  annotation(
    Diagram,
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 11}, extent = {{-60, 29}, {60, -31}}, textString = "%name%")}));
end Va_filter;
