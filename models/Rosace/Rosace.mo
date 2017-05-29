package Rosace
  model Rosace_model
    Rosace.Environment.Engine engine1 annotation(
      Placement(visible = true, transformation(origin = {-28, 20}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Environment.Elevator elevator1 annotation(
      Placement(visible = true, transformation(origin = {-28, -18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Environment.Aircraft_Dynamics aircraft_Dynamics1 annotation(
      Placement(visible = true, transformation(origin = {32, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Va_filter va_filter1 annotation(
      Placement(visible = true, transformation(origin = {90, 60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Vz_filter vz_filter1 annotation(
      Placement(visible = true, transformation(origin = {90, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Q_filter q_filter1 annotation(
      Placement(visible = true, transformation(origin = {90, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Az_filter az_filter1 annotation(
      Placement(visible = true, transformation(origin = {90, -30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.H_filter h_filter1 annotation(
      Placement(visible = true, transformation(origin = {90, -60}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Altitude_hold altitude_hold1 annotation(
      Placement(visible = true, transformation(origin = {142, -64}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Vz_control vz_control1 annotation(
      Placement(visible = true, transformation(origin = {190, -10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Rosace.Controller.Va_control va_control1 annotation(
      Placement(visible = true, transformation(origin = {190, 30}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Modelica.Blocks.Sources.RealExpression realExpression1(y = 0.0)  annotation(
      Placement(visible = true, transformation(origin = {224, 6}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
    Modelica.Blocks.Sources.RealExpression realExpression2(y = 11000)  annotation(
      Placement(visible = true, transformation(origin = {80, -86}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  equation
    connect(realExpression2.y, altitude_hold1.h_f) annotation(
      Line(points = {{92, -86}, {120, -86}, {120, -70}, {130, -70}, {130, -72}}, color = {0, 0, 127}));
    connect(realExpression1.y, va_control1.Va_c) annotation(
      Line(points = {{235, 6}, {244, 6}, {244, 16}, {169, 16}, {169, 22}, {178, 22}}, color = {0, 0, 127}));
    connect(va_control1.y, engine1.delta_th_c) annotation(
      Line(points = {{202, 30}, {234, 30}, {234, 80}, {-60, 80}, {-60, 20}, {-40, 20}, {-40, 20}}, color = {0, 0, 127}));
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
    connect(vz_control1.y, elevator1.delta_e_c) annotation(
      Line(points = {{202, -10}, {220, -10}, {220, -100}, {-60, -100}, {-60, -18}, {-40, -18}}, color = {0, 0, 127}));
    connect(aircraft_Dynamics1.az, az_filter1.az) annotation(
      Line(points = {{44, -4}, {70, -4}, {70, -30}, {78, -30}}, color = {0, 0, 127}));
    connect(aircraft_Dynamics1.Vz, vz_filter1.Vz) annotation(
      Line(points = {{43, 4}, {71, 4}, {71, 30}, {78, 30}}, color = {0, 0, 127}));
    connect(aircraft_Dynamics1.Va, va_filter1.Va) annotation(
      Line(points = {{44, 8}, {60, 8}, {60, 60}, {78, 60}}, color = {0, 0, 127}));
    connect(aircraft_Dynamics1.h_out, h_filter1.h) annotation(
      Line(points = {{44, -8}, {60, -8}, {60, -60}, {78, -60}}, color = {0, 0, 127}));
    connect(aircraft_Dynamics1.q_out, q_filter1.q) annotation(
      Line(points = {{43, 0}, {78, 0}}, color = {0, 0, 127}));
    connect(engine1.y, aircraft_Dynamics1.T) annotation(
      Line(points = {{-17, 20}, {2.5, 20}, {2.5, 5}, {20, 5}}, color = {0, 0, 127}));
    connect(elevator1.y, aircraft_Dynamics1.delta_e) annotation(
      Line(points = {{-17, -18}, {2, -18}, {2, -5}, {20, -5}}, color = {0, 0, 127}));
    annotation(
      Diagram(coordinateSystem(extent = {{-100, -100}, {250, 100}})),
      Icon(coordinateSystem(extent = {{-100, -100}, {250, 100}})),
      __OpenModelica_commandLineOptions = "");
  end Rosace_model;


  package Controller
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


    model Vz_filter
      Modelica.Blocks.Interfaces.RealInput Vz annotation(
        Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      Modelica.Blocks.Interfaces.RealOutput y annotation(
        Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      Real x1;
      Real x2;
      parameter Real a0 = 0.956543675476034;
      parameter Real a1 = -1.955578398054313;
      parameter Real b0 = 0.000479064865372430;
      parameter Real b1 = 0.000486212556348925;
    initial equation
      x1 = 0.0;
      x2 = 0.0;
    equation
//Output equation
      y = x2;
//State equation
      x1 = (-a0 * x2) + b0 * Vz;
      x2 = x1 - a1 * x2 + b1 * Vz;
      annotation(
        Diagram,
        Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 11}, extent = {{-60, 29}, {60, -31}}, textString = "%name%")}));
    end Vz_filter;

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

    model H_filter
      Modelica.Blocks.Interfaces.RealInput h annotation(
        Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      Modelica.Blocks.Interfaces.RealOutput y annotation(
        Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      Real x1 (start=-7511.42);
      Real x2 (start=10000.0);
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
      
      parameter Real Ts_K2 = 1.0/50.0;
      Real integrator;
      
      /* Vz Speed controller */
      constant Real K2_intVz  = 0.000627342822264;
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
      
      parameter Real Ts_K1 = 1.0/50.0;
      Real integrator;
      
      /* Vz Speed controller */
      constant Real K1_intVa  = 0.049802610664357;
      constant Real K1_Va = -0.486813084356079;
      constant Real K1_Vz = -0.077603095495388;
      constant Real K1_q = 21.692383376322041;
      constant Real Va_eq = 230.0;
      
      constant Real delta_th_eq = 1.5868660794926;
      
    equation
      y =  K1_intVa * integrator + K1_Va * (Va_f - Va_eq) + K1_Vz * Vz_f + K1_q * q_f + delta_th_eq;
//integrator = pre(integrator) + Ts_K1 * (Va_c - Va_f + Va_eq);
      integrator = integrator + Ts_K1 * (Va_c - Va_f + Va_eq);
      annotation(
        Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 10}, extent = {{-60, 30}, {60, -30}}, textString = "%name%")}));
    end Va_control;














  end Controller;

  package Environment
    model Engine
      parameter Real tau = 0.75;
      parameter Real delta_th_eq = 1.5868660794926;
      Modelica.Blocks.Interfaces.RealInput delta_th_c annotation(
        Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      Modelica.Blocks.Interfaces.RealOutput y(start = delta_th_eq) annotation(
        Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      Real x1(start = delta_th_eq);
    equation
//Output equation
      y = 26350.0 * x1;
//State equation
      der(x1) = (-tau * x1) + tau * delta_th_c;
      annotation(
        Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {-1, 16}, extent = {{-59, 24}, {61, -36}}, textString = "%name%")}, coordinateSystem(initialScale = 0.1)));
    end Engine;

    model Elevator
      parameter Real omega = 25.0;
      parameter Real xi = 0.85;
      parameter Real delta_e_eq = 0.012009615652468;
      Modelica.Blocks.Interfaces.RealInput delta_e_c annotation(
        Placement(visible = true, transformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 0}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      Modelica.Blocks.Interfaces.RealOutput y(start = delta_e_eq) annotation(
        Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      Real x1(start = delta_e_eq);
      Real x2(start = 0.0);
    equation
//Output equation
      y = x1;
//State equation
      der(x1) = x2;
      der(x2) = (-omega * omega * x1) - 2.0 * xi * omega * x2 + omega * omega * delta_e_c;
      annotation(
        Icon(graphics = {Rectangle(origin = {-79, 75}, extent = {{-21, 25}, {179, -175}}), Text(origin = {22, -1}, extent = {{-82, 41}, {38, -19}}, textString = "%name%")}));
    end Elevator;

    model Aircraft_Dynamics
      /* Atmosphere parameters */
      constant Real T0_h = -0.0065;
      constant Real T0_0 = 288.15;
      constant Real g0 = 9.80665;
      constant Real rho0 = 1.225;
      constant Real Rs = 287.05;
      /* Aircraft parameters */
      constant Real masse = 57837.5;
      constant Real I_y = 3781272.0;
      constant Real S = 122.6;
      constant Real cbar = 4.29;
      constant Real CD_0 = 0.016;
      constant Real CD_alpha = 2.5;
      constant Real CD_deltae = 0.05;
      constant Real CL_alpha = 5.5;
      constant Real CL_deltae = 0.193;
      constant Real alpha_0 = -0.05;
      constant Real Cm_0 = 0.04;
      constant Real Cm_alpha = -0.83;
      constant Real Cm_deltae = -1.5;
      constant Real Cm_q = -30.0;
      /* Trimming parameters */
      constant Real h_eq = 10000.0;
      constant Real Va_eq = 230.0;
      constant Real Vz_eq = 0.0;
      constant Real alpha_eq = 0.026485847681737;
      constant Real theta_eq = 0.026485847681737;
      Modelica.Blocks.Interfaces.RealInput delta_e annotation(
        Placement(visible = true, transformation(origin = {-120, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, -54}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      //Elevator deflection
      Modelica.Blocks.Interfaces.RealInput T annotation(
        Placement(visible = true, transformation(origin = {-120, -50}, extent = {{-20, -20}, {20, 20}}, rotation = 0), iconTransformation(origin = {-120, 50}, extent = {{-20, -20}, {20, 20}}, rotation = 0)));
      //Engine thrust
      Modelica.Blocks.Interfaces.RealOutput Va annotation(
        Placement(visible = true, transformation(origin = {110, 80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 84}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      //True airspeed
      Modelica.Blocks.Interfaces.RealOutput Vz annotation(
        Placement(visible = true, transformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      //Vertical air speed
      Modelica.Blocks.Interfaces.RealOutput q_out annotation(
        Placement(visible = true, transformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      //Pitch rate
      Modelica.Blocks.Interfaces.RealOutput az annotation(
        Placement(visible = true, transformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -40}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      //Vertical acceleration
      Modelica.Blocks.Interfaces.RealOutput h_out annotation(
        Placement(visible = true, transformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0), iconTransformation(origin = {110, -80}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
      //Altitude
      Real u(start = 0.0);
      Real w(start = 0.0);
      Real theta(start = 0.0);
      Real q(start = 0.0);
      Real h(start = 0.0);
      Real CD;
      Real CL;
      Real Cm;
      Real Xa;
      Real Za;
      Real Ma;
      Real alpha;
      Real qbar;
      Real V;
      Real rho;
    initial equation
      u = Va_eq * cos(theta_eq);
      w = Va_eq * sin(theta_eq);
      q = 0.0;
      theta = theta_eq;
      h = h_eq;
    equation
//Output equations
      Va = V;
      Vz = w * cos(theta) - u * sin(theta);
      q_out = q;
      az = g0 * cos(theta) + Za / masse;
      h_out = h;
      rho = rho0 * (1.0 + T0_h / T0_0 * h) ^ ((-g0 / (Rs * T0_h)) - 1.0);
      alpha = atan(w / u);
      V = sqrt(u * u + w * w);
      qbar = 0.5 * rho * V * V;
      CL = CL_deltae * delta_e + CL_alpha * (alpha - alpha_0);
      CD = CD_0 + CD_deltae * delta_e + CD_alpha * (alpha - alpha_0) * (alpha - alpha_0);
      Cm = Cm_0 + Cm_deltae * delta_e + Cm_alpha * alpha + 0.5 * Cm_q * q * cbar / V;
      Xa = -qbar * S * (CD * cos(alpha) - CL * sin(alpha));
      Za = -qbar * S * (CD * sin(alpha) + CL * cos(alpha));
      Ma = qbar * cbar * S * Cm;
//State equations
      der(u) = (-g0 * sin(theta)) - q * w + (Xa + T) / masse;
      der(w) = g0 * cos(theta) + q * u + Za / masse;
      der(q) = Ma / I_y;
      der(theta) = q;
      der(h) = u * sin(theta) - w * cos(theta);
      annotation(
        Icon(graphics = {Rectangle(extent = {{-100, 100}, {100, -100}}), Text(origin = {0, 10}, extent = {{-60, 30}, {60, -30}}, textString = "%name%")}, coordinateSystem(initialScale = 0.1)));
    end Aircraft_Dynamics;
  end Environment;
  annotation(
    uses(Modelica(version = "3.2.2")));
end Rosace;
