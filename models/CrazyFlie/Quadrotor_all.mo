class Quadrotor_all
model Angles

	import Modelica.SIunits;
  	parameter SIunits.Length l = 0.23;              // Length
  	parameter SIunits.MomentOfInertia Ix = 7.5e-3;  //Quadrotor moment of inertia around X axis
  	parameter SIunits.MomentOfInertia Iy = 7.5e-3;  //Quadrotor moment of inertia around Y axis
 	parameter SIunits.MomentOfInertia Iz = 1.3e-2;  //Quadrotor moment of inertia around Z axis
 	parameter SIunits.MomentOfInertia Jr = 6.5e-5;  //Total rotational moment of inertia around the propeller axis
	parameter Real b = 3.13e-5;                     //Thrust factor
  	parameter Real d = 7.5e-7;                      // Drag factor
	Real Phi_dot, Theta_dot, Psi_dot, Phi_dot_dot, Theta_dot_dot, Psi_dot_dot;
	
 Modelica.Blocks.Interfaces.RealInput u2 annotation(
    Placement(visible = true, transformation(origin = {-120, 78}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u3 annotation(
    Placement(visible = true, transformation(origin = {-120, 26}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput u4 annotation(
    Placement(visible = true, transformation(origin = {-120, -32}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput omega annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Phi annotation(
    Placement(visible = true, transformation(origin = {110, 80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 88}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Theta annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Psi annotation(
    Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
	Phi_dot_dot = (Iy-Iz)/Ix*Theta_dot*Psi_dot + Jr/Ix*Theta_dot*omega + l/Ix*u2;
	Theta_dot_dot = (Iz-Ix)/Iy*Phi_dot*Psi_dot - Jr/Iy*Phi_dot*omega + l/Iy*u3;
	Psi_dot_dot = (Ix-Iy)/Iz*Phi_dot*Theta_dot + 1/Iz*u4;
	Phi_dot = der(Phi); 
	Phi_dot_dot = der(Phi_dot);
	Theta_dot = der(Theta); 
	Theta_dot_dot = der(Theta_dot);
	Psi_dot = der(Psi); 
	Psi_dot_dot = der(Psi_dot);
	
annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(coordinateSystem(extent = {{-100, -120}, {100, 120}}),graphics = {Rectangle(origin = {0, 0}, extent = {{-100, 120}, {100, -120}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 120}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Angles;

model Displacement
import Modelica.SIunits;
final constant Real g = Modelica.Constants.g_n; //Acceleration of the gravity	
parameter SIunits.Mass m = 0.65;             // Mass 	
parameter SIunits.MomentOfInertia Ix = 7.5e-3;  //Quadrotor moment of inertia around X axis 	
parameter SIunits.MomentOfInertia Iy = 7.5e-3;  //Quadrotor moment of inertia around Y axis 	
parameter SIunits.MomentOfInertia Iz = 1.3e-3;  //Quadrotor moment of inertia around Z axis	
parameter SIunits.MomentOfInertia Jr = 6.5e-5;  //Total rotational moment of inertia around the propeller axis	
parameter Real b = 3.13e-5;                     //Thrust factor 	
parameter Real d = 7.5e-7;                    // Drag factor
Real X_dot, Y_dot, Z_dot, X_dot_dot, Y_dot_dot, Z_dot_dot;
 Modelica.Blocks.Interfaces.RealInput u1 annotation(
    Placement(visible = true, transformation(origin = {-120, 110}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 110}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Phi annotation(
    Placement(visible = true, transformation(origin = {-120, 40}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 40}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Theta annotation(
    Placement(visible = true, transformation(origin = {-120, -40}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -40}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput Psi annotation(
    Placement(visible = true, transformation(origin = {-120, -110}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -110}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput X annotation(
    Placement(visible = true, transformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Y annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput Z annotation(
    Placement(visible = true, transformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

equation
X_dot_dot = (cos(Phi)*sin(Theta)*cos(Psi) + sin(Phi)*sin(Psi))*u1/m - X_dot*d/m;
Y_dot_dot = (cos(Phi)*sin(Theta)*sin(Psi) + sin(Phi)*cos(Psi))*u1/m - Y_dot*d/m;
Z_dot_dot = cos(Phi)*cos(Theta)*u1/m - Z_dot*d/m - g;	
X_dot = der(X); 
X_dot_dot = der(X_dot);	
Y_dot = der(Y); 
Y_dot_dot = der(Y_dot);	
Z_dot = der(Z); 
Z_dot_dot = der(Z_dot);

annotation(
    Diagram(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}})),
    Icon(coordinateSystem(grid = {2, 1}, extent = {{-100, -160}, {100, 140}}),graphics = {Rectangle(origin = {0, 0}, extent = {{-100, 160}, {100, -180}})}),
    version = "",
    uses,
    __OpenModelica_commandLineOptions = "");
end Displacement;

model Speed_calculator
	import Modelica.SIunits;
  	parameter SIunits.Length l = 0.23;           // Length
	parameter Real b = 3.13e-5;                  //Thrust factor
  	parameter Real d = 7.5e-7;                   // Drag factor
	Real o1, o2, o3, o4;
 Modelica.Blocks.Interfaces.RealInput U1 annotation(
    Placement(visible = true, transformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U2 annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U3 annotation(
    Placement(visible = true, transformation(origin = {-120, -28}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -24}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealInput U4 annotation(
    Placement(visible = true, transformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -80}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u1 annotation(
    Placement(visible = true, transformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u2 annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u3 annotation(
    Placement(visible = true, transformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput u4 annotation(
    Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
 Modelica.Blocks.Interfaces.RealOutput omega annotation(
    Placement(visible = true, transformation(origin = {110, 80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 80}, 
extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    
equation
    o1 = 1/(4*b)*U1 + 1/(2*b*l)*U3 - 1/(4*d)*U4;
    o2 = 1/(4*b)*U1 - 1/(2*b*l)*U2 + 1/(4*d)*U4;
    o3 = 1/(4*b)*U1 - 1/(2*b*l)*U3 - 1/(4*d)*U4;
    o4 = 1/(4*b)*U1 + 1/(2*b*l)*U2 + 1/(4*d)*U4;
	omega = (-sqrt(abs(o1)) + sqrt(abs(o2)) - sqrt(abs(o3)) + sqrt(abs(o4)))*d;
	u1 = U1;
	u2 = U2/l;
	u3 = U3/l;
 	u4 = U4;
 	
annotation(
    uses(Modelica(version = "3.2.2")),
    Icon(graphics = {Rectangle(origin = {0, 1}, extent = {{-100, 99}, {100, -101}})}),
    Diagram(coordinateSystem(extent = {{-100, -120}, {100, 120}})),
    version = "",
    __OpenModelica_commandLineOptions = "");
end Speed_calculator;

  Displacement displacement1 annotation(
    Placement(visible = true, transformation(origin = {76, 22}, extent = {{-10, -16}, {10, 14}}, rotation = 0)));
  Angles angles1 annotation(
    Placement(visible = true, transformation(origin = {-4, 24}, extent = {{-10, -12}, {10, 12}}, rotation = 0)));
  Speed_calculator speed_calculator1 annotation(
    Placement(visible = true, transformation(origin = {-48, 24}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput T annotation(
    Placement(visible = true, transformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_phi annotation(
    Placement(visible = true, transformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_theta annotation(
    Placement(visible = true, transformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -30}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealInput tau_psi annotation(
    Placement(visible = true, transformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -90}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Phi annotation(
    Placement(visible = true, transformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Theta annotation(
    Placement(visible = true, transformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Psi annotation(
    Placement(visible = true, transformation(origin = {110, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput X annotation(
    Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Y annotation(
    Placement(visible = true, transformation(origin = {110, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Z annotation(
    Placement(visible = true, transformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Interfaces.RealOutput Omega annotation(
    Placement(visible = true, transformation(origin = {110, -92}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -90}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(Omega, angles1.omega) annotation(
    Line(points = {{110, -92}, {-30, -92}, {-30, 16}, {-16, 16}}, color = {0, 0, 127}));
  connect(displacement1.Z, Z) annotation(
    Line(points = {{88, 14}, {90, 14}, {90, -60}, {110, -60}}, color = {0, 0, 127}));
  connect(displacement1.Y, Y) annotation(
    Line(points = {{88, 22}, {92, 22}, {92, -30}, {110, -30}}, color = {0, 0, 127}));
  connect(Phi, angles1.Phi) annotation(
    Line(points = {{110, 90}, {24, 90}, {24, 32}, {8, 32}}, color = {0, 0, 127}));
  connect(Theta, angles1.Theta) annotation(
    Line(points = {{110, 60}, {30, 60}, {30, 24}, {8, 24}}, color = {0, 0, 127}));
  connect(Psi, angles1.Psi) annotation(
    Line(points = {{110, 30}, {96, 30}, {96, 52}, {16, 52}, {16, 14}, {8, 14}, {8, 16}}, color = {0, 0, 127}));
  connect(X, displacement1.X) annotation(
    Line(points = {{110, 0}, {94, 0}, {94, 32}, {88, 32}}, color = {0, 0, 127}));
  connect(tau_psi, speed_calculator1.U4) annotation(
    Line(points = {{-120, -90}, {-80, -90}, {-80, 16}, {-60, 16}, {-60, 16}}, color = {0, 0, 127}));
  connect(tau_theta, speed_calculator1.U3) annotation(
    Line(points = {{-120, -30}, {-90, -30}, {-90, 22}, {-60, 22}, {-60, 22}}, color = {0, 0, 127}));
  connect(tau_phi, speed_calculator1.U2) annotation(
    Line(points = {{-120, 30}, {-82, 30}, {-82, 26}, {-60, 26}, {-60, 28}}, color = {0, 0, 127}));
  connect(T, speed_calculator1.U1) annotation(
    Line(points = {{-120, 90}, {-76, 90}, {-76, 32}, {-60, 32}, {-60, 32}}, color = {0, 0, 127}));
  connect(speed_calculator1.u1, displacement1.u1) annotation(
    Line(points = {{-36, 28}, {-32, 28}, {-32, 48}, {52, 48}, {52, 36}, {64, 36}, {64, 33}}, color = {0, 0, 127}));
  connect(angles1.Psi, displacement1.Psi) annotation(
    Line(points = {{8, 14}, {48, 14}, {48, 11}, {64, 11}}, color = {0, 0, 127}));
  connect(angles1.Theta, displacement1.Theta) annotation(
    Line(points = {{8, 24}, {50, 24}, {50, 18}, {64, 18}}, color = {0, 0, 127}));
  connect(angles1.Phi, displacement1.Phi) annotation(
    Line(points = {{8, 32}, {52, 32}, {52, 26}, {64, 26}}, color = {0, 0, 127}));
  connect(speed_calculator1.u4, angles1.u4) annotation(
    Line(points = {{-36, 16}, {-22, 16}, {-22, 20}, {-16, 20}, {-16, 20}}, color = {0, 0, 127}));
  connect(speed_calculator1.u3, angles1.u3) annotation(
    Line(points = {{-36, 20}, {-24, 20}, {-24, 26}, {-16, 26}, {-16, 28}}, color = {0, 0, 127}));
  connect(speed_calculator1.u2, angles1.u2) annotation(
    Line(points = {{-36, 24}, {-26, 24}, {-26, 34}, {-16, 34}, {-16, 34}}, color = {0, 0, 127}));
  connect(speed_calculator1.omega, angles1.omega) annotation(
    Line(points = {{-36, 32}, {-30, 32}, {-30, 14}, {-16, 14}, {-16, 14}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")),
    Diagram(coordinateSystem(extent = {{-100, -140}, {100, 140}})),
    Icon(coordinateSystem(extent = {{-100, -140}, {100, 140}}),graphics = {Rectangle(extent = {{-100, 140}, {100, -140}})}),
    version = "",
    __OpenModelica_commandLineOptions = "");


end Quadrotor_all;