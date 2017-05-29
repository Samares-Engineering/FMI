#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "fmi2.h"
#include "sim_support.h"
#include "fmu_wrapper.h"

/******************************************************************************/
void moonlanding_fmu_entrypoint (fmi2Real *a_out,
                                 fmi2Real thrust_in,
                                 fmi2Real *v_out)
{
  const char     *fmuFileName ="MoonLanding.fmu";
  double          tEnd = 110.0;
  double          h = 0.1;
  static bool    initialized = false;
  static FMUContext      ctx;

  /* 1/ FMU activation */

  if (!initialized) {
    ctx.fmu = malloc (sizeof (FMU));
    FMU_Activate_Entrypoint (fmuFileName, tEnd, h, &ctx);
    initialized = true;
  }

  /* 2/ Regular compute entrypoint */

  fmi2ValueReference vr;
  fmi2Real        r;
  fmi2Status      fmi2Flag;

  /* Get the scalar variables */
  ScalarVariable *thrust_sv = getVariable (ctx.fmu->modelDescription, "thrust");
  ScalarVariable *a_sv = getVariable (ctx.fmu->modelDescription, "a");
  ScalarVariable *v_sv = getVariable (ctx.fmu->modelDescription, "v");

  /* Set the input */
  vr = getValueReference (thrust_sv);
  fmi2Flag = ctx.fmu->setReal (ctx.component, &vr, 1, &thrust_in);

  /* Calculate the Step */
  doStep (ctx.fmu, ctx.component,
          ctx.currentCommunicationPoint,
          ctx.communicationStepSize,
          ctx.noSetFMUStatePriorToCurrentPoint);

  /* Dump values */
  outputRow (ctx.fmu, ctx.component,
             ctx.currentCommunicationPoint,
             ctx.resultFile, ',', fmi2False);

  /* Get the outputs */
  vr = getValueReference (a_sv);
  fmi2Flag = ctx.fmu->getReal (ctx.component, &vr, 1, &r);
  *a_out = r;

  vr = getValueReference (v_sv);
  fmi2Flag = ctx.fmu->getReal (ctx.component, &vr, 1, &r);
  *v_out = r;

  ctx.currentCommunicationPoint += ctx.communicationStepSize;

  /* 3) terminate the simulation */

  if (ctx.currentCommunicationPoint > tEnd)  {
    freeContext (ctx);
    exit (0);
  }
}
