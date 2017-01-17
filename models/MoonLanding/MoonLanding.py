from pymodelica import compile_fmu
from pyfmi import load_fmu
import pylab as P
import numpy as N

def run_demo():
	print("Compiling Modelica models into FMUs")
	moon_landing_fmu = compile_fmu("MoonLanding","MoonLanding.mo", target='cs', version='2.0',compiler_log_level='d:compilation_moon_landing_log.txt', compiler_options={"cs_solver":1, "cs_step_size":0.001})
	
	print("Loading FMUs")
	moonLander = load_fmu(moon_landing_fmu, log_level=7)

	Tstart = 0
	Tend = 200
	moonLander.time = Tstart
	
	print("Instantiation and initialization of experiments")
	moonLander.setup_experiment(start_time = Tstart, stop_time = Tend, stop_time_defined = True)
	moonLander.initialize()
	print("FMUs initialized")

	moonLander_values_sol = [moonLander.get_variable_valueref('a')] + \
	 [moonLander.get_variable_valueref('v')] + \
	 [moonLander.get_variable_valueref('thrust')]

	thrust = [moonLander.get_variable_valueref('thrust')]
	altitude = [moonLander.get_variable_valueref('a')]
	velocity = [moonLander.get_variable_valueref('v')]

	#Get the initial values for the solution
	t_sol = [Tstart]
	sol = [moonLander.get_real(moonLander_values_sol)]

	#Setting the time
	time = Tstart
	dt = 0.1 #Step-size

	print("Start of the integration loop")
	
	while time < Tend:

		h = min(dt, Tend-time)

		#Call slaves
		status = moonLander.do_step(time,h,True)

		if(status == 'FMI_OK'):
			print("Step accepted by MoonLander FMU")
		
		time = time + h
		t_sol += [time]
		sol += [moonLander.get_real(moonLander_values_sol)]

	P.figure(1)
	P.plot(t_sol, N.array(sol)[:,0])
	P.title(moonLander.get_name())
	P.ylabel('Altitude (m)')
	P.xlabel('Time (s)')
	
	P.figure(2)
	P.plot(t_sol, N.array(sol)[:,1])
	P.title(moonLander.get_name())
	P.ylabel('Velocity (m/s)')
	P.xlabel('Time (s)')

	P.figure(3)
	P.plot(t_sol, N.array(sol)[:,2])
	P.title(moonLander.get_name())
	P.ylabel('Thrust (N)')
	P.xlabel('Time (s)')

	P.show()
			
		
