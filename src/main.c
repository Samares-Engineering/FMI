#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2.h"
#include "sim_support.h"

#include "fmu_wrapper.h"

typedef struct {
  fmi2Real        output_altitute;
  fmi2Real        output_velocity;
}               MoonLandingOuputs;

/******************************************************************************
 */

int
Compute_Entrypoint_MoonLanding (FMUContext * ctx,
                                fmi2Real inputThrust,
                                MoonLandingOuputs * moonLandingOuputs)
{
  fmi2ValueReference vr;
  fmi2Real        r;
  fmi2Status      fmi2Flag;

  /* Get the scalar variables */
  ScalarVariable *input_thrust_sv = getVariable (ctx->fmu->modelDescription, "thrust");
  ScalarVariable *output_altitute_sv = getVariable (ctx->fmu->modelDescription, "a");
  ScalarVariable *output_velocity_sv = getVariable (ctx->fmu->modelDescription, "v");

  /* Set the input */
  vr = getValueReference (input_thrust_sv);
  fmi2Flag = ctx->fmu->setReal (ctx->component, &vr, 1, &inputThrust);

  /* Calculate the Step */
  doStep (ctx->fmu, ctx->component,
          ctx->currentCommunicationPoint,
          ctx->communicationStepSize,
          ctx->noSetFMUStatePriorToCurrentPoint);

  /* Dump values */
  outputRow (ctx->fmu, ctx->component,
             ctx->currentCommunicationPoint,
             ctx->resultFile, ',', fmi2False);

  /* Get the outputs */
  vr = getValueReference (output_altitute_sv);
  fmi2Flag = ctx->fmu->getReal (ctx->component, &vr, 1, &r);
  moonLandingOuputs->output_altitute = r;

  vr = getValueReference (output_velocity_sv);
  fmi2Flag = ctx->fmu->getReal (ctx->component, &vr, 1, &r);
  moonLandingOuputs->output_velocity = r;

  return fmi2Flag;
}

/******************************************************************************
 */

int
main (int argc, char *argv[])
{
  const char     *fmuFileName;
  double          tEnd = 1.0;
  double          h = 0.1;
  int             loggingOn = 0;
  char            csv_separator = ',';
  fmi2String     *categories = NULL;
  int             nCategories = 0;
  FMUContext      ctx;
  parseArguments (argc, argv, &fmuFileName, &tEnd, &h, &loggingOn,
                  &csv_separator, &nCategories, &categories);

  ctx.fmu = malloc (sizeof (FMU));

  /* 1/ FMU Activate Entrypoint */
  FMU_Activate_Entrypoint
    (fmuFileName, tEnd, h, loggingOn,
     csv_separator, nCategories, categories, &ctx);

  /* MoonLanding specific part */

  fmi2Real        inputThrust = 10000.0;        /* Dummy input set to constant */
  MoonLandingOuputs *moonLandingOuputs;
  moonLandingOuputs = (MoonLandingOuputs *) malloc (sizeof (MoonLandingOuputs));
  assert (moonLandingOuputs != NULL);

  /* 2/ Processing loop */
  while (ctx.currentCommunicationPoint < tEnd) {

    /* 3/ Compute_Entrypoint */
    Compute_Entrypoint_MoonLanding (&ctx, inputThrust, moonLandingOuputs);

    printf ("OUPUT ALTITUDE === %f\n", moonLandingOuputs->output_altitute);
    printf ("OUPUT VELOCITY === %f\n\n", moonLandingOuputs->output_velocity);

    /* "time" management */
    ctx.currentCommunicationPoint += ctx.communicationStepSize;
  }

  /* End simulation */
  printf ("\nEnd of the simulation.\n\n");

  free (moonLandingOuputs);
  freeContext (ctx);

  return EXIT_SUCCESS;
}
