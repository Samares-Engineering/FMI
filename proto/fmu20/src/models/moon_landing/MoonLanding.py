from pymodelica import compile_fmu
from pyfmi import load_fmu
import pylab as P
import numpy as N

def run_demo(with_plots=True):
		# compiling the FMUs
	print("Compiling the MoonLanding model")
	moon_landing_fmu = compile_fmu("MoonLanding","MoonLanding.mo", target='cs', version='2.0',compiler_log_level='d:compilation_moon_landing_log.txt', compiler_options={"cs_solver":1, "cs_step_size":0.001}) 
