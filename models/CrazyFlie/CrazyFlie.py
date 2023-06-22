from pymodelica import compile_fmu
from pyfmi import load_fmu

def run_demo():
	print("Compiling the FMUs")
	system_model = compile_fmu("Quadrotor_all","Quadrotor_all.mo", target='cs', version='2.0');
