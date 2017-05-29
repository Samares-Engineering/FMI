model H_filter
  Modelica.Blocks.Interfaces.RealInput h annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Real x1(start = -7511.42);
  Real x2(start = 10000.0);
  constant Real h_eq = 10000.0;
  parameter Real a0 = 0.766000101841272;
  parameter Real a1 = -1.734903205885821;
  parameter Real b0 = 0.014857648981438;
  parameter Real b1 = 0.016239246974013;
equation
//Output equation
  y = x2;
//State equation
  x1 = (-a0 * x2) + b0 * h;
  x2 = x1 - a1 * x2 + b1 * h;
  annotation(
    Diagram,
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 11}, extent = {{-60, 29}, {60, -31}}, textString = "%name%")}));
end H_filter;
