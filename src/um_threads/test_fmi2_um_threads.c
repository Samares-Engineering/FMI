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
  fmi2Real ccp;
  fmi2Real css;
  fmi2Boolean prior;
  fmi2CallbackFunctions* fcbf;

  fmi2Instantiate("FMU_Test", fmi2CoSimulation, "012345", "myPath", fcbf, fmi2True, fmi2True);
  fmi2DoStep(c, ccp, css, prior);

  return EXIT_SUCCESS;
}
