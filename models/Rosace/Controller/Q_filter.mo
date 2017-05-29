model Q_filter
  Modelica.Blocks.Interfaces.RealInput q annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Real x1;
  Real x2;
  parameter Real a0 = 0.766000101841272;
  parameter Real a1 = -1.734903205885821;
  parameter Real b0 = 0.014857648981438;
  parameter Real b1 = 0.016239246974013;
initial equation
  x1 = 0.0;
  x2 = 0.0;
equation
//Output equation
  y = x2;
//State equation
  x1 = (-a0 * x2) + b0 * q;
  x2 = x1 - a1 * x2 + b1 * q;
  annotation(
    Diagram,
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 11}, extent = {{-60, 29}, {60, -31}}, textString = "%name%")}));
end Q_filter;
