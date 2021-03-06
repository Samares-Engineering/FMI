# FMI

To test the code perform the follwing steps: 

1. Go to the /src folder.
2. Open a console and type "make all". 
3. A binary file is built in the folder ../bin 
4. Launch the binary with the command: ./FMI_prototype MoonLanding.fmu
5. The fmu is loaded and simulated. 
6. Simulation results are generated in the result.csv file.

To clean the binary and temporary files, perform the following steps: 

1. Go to the /src folder.
2. Open a console and type "make distclean".

# FMU Models 

In the models folder, you will find two FMUs: bouncingBall.fmu and MoonLanding.fmu. 

## Bouncing Ball
The bouncingBall.fmu has been generated using the submodule FMUSDK2. To generate the fmu, perform the following steps: 

1. Clone the FMUSDK2 available [here](https://github.com/cxbrooks/fmusdk2) (or use the FMUSDK2 submodule directly). 
2. Go to the fmusdk2 folder and open a console.
3. Type the "make all" command. 
4. FMUs for co-simulation are built in the folder fmu20/fmu/cs.
5. Go to the folder fmu20/bin
6. Type the "./fmusim_cs ../fmu/cs/bouncingBall.fmu" command to simulate the fmu. 
7. To clean the project go to the fmusdk2 folder and type the "make distclean" command.

## Moon Landing (inspired from Peter Fritzon)
The MoonLanding.fmu file has been generated with JModelica using the python file MoonLanding.py. This fmu is compliant with Linux 64bits. 

To generate an FMU from the Modelica file (MoonLanding.mo), perform the following steps: 

1. Install JModelica for your OS. 
2. Launch the IPython console from JModelica. 
3. Launch the examples of the JModelica documentation to test the JModelica deployment. 
4. Place the MoonLanding.py and the MoonLanding.mo files into the right folder (same folder as the fmu generated by the previous step) 
5. Launch the following commands:
	* import MoonLanding
	* MoonLanding.run_demo()
6. An FMU should be generated and simulated by JModelica.
