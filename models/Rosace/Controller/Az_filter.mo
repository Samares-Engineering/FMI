model Az_filter
  Modelica.Blocks.Interfaces.RealInput az annotation(
    Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Real x1;
  Real x2;
  parameter Real a0 = 0.411240701442774;
  parameter Real a1 = -1.158045899830964;
  parameter Real b0 = 0.107849979167580;
  parameter Real b1 = 0.145344822444230;
initial equation
  x1 = 0.0;
  x2 = 0.0;
equation
//Output equation
  y = x2;
//State equation
  x1 = (-a0 * x2) + b0 * az;
  x2 = x1 - a1 * x2 + b1 * az;
  annotation(
    Diagram,
    Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 11}, extent = {{-60, 29}, {60, -31}}, textString = "%name%")}));
end Az_filter;
