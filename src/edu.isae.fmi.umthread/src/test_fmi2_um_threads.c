#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2.h"


int
main (int argc, char *argv[])
{
  
  fmi2Component c;
  fmi2Real currentCommunicationPoint = 0.0;
  fmi2Real stepSize=0.01;

  fmi2CallbackFunctions* fcbf;

  c = fmi2Instantiate("FMU_Test", fmi2CoSimulation, "012345", "myPath", fcbf, fmi2True, fmi2True);
  fmi2SetupExperiment(c, fmi2False, 0.0, 0.0, fmi2True, 1.0);
  fmi2EnterInitializationMode(c);
  fmi2ExitInitializationMode(c);

  fmi2DoStep(c, currentCommunicationPoint, stepSize, fmi2True);

  return EXIT_SUCCESS;
}
