#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmi2.h"
#include "sim_support.h"
#include "fmu_wrapper.h"


#define NUMBER_OF_FMUS 2
#define NUMBER_OF_EDGES 0
#define MODEL_NAME "demo"
const char* NAMES_OF_FMUS[] = {"bouncingBall.fmu", "bouncingBall.fmu"};


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
	ScalarVariable *input_thrust_sv = getVariable (ctx->fmus->modelDescription, "thrust");
	ScalarVariable *output_altitute_sv = getVariable (ctx->fmus->modelDescription, "a");
	ScalarVariable *output_velocity_sv = getVariable (ctx->fmus->modelDescription, "v");

	/* Set the input */
	vr = getValueReference (input_thrust_sv);
	fmi2Flag = ctx->fmus->setReal (ctx->component, &vr, 1, &inputThrust);

	/* Calculate the Step */
	doStep (ctx->fmus, ctx->component,
			ctx->currentCommunicationPoint,
			ctx->communicationStepSize,
			ctx->noSetFMUStatePriorToCurrentPoint);

	/* Dump values */
	//outputRow(ctx->fmus, NUMBER_OF_FMUS, NAMES_OF_FMUS, ctx->currentCommunicationPoint, ctx->resultFile, ',', fmi2False);

	outputRow (ctx->fmus, ctx->component,
             ctx->currentCommunicationPoint,
             ctx->resultFile, ',', fmi2False);

	/* Get the outputs */
	vr = getValueReference (output_altitute_sv);
	fmi2Flag = ctx->fmus->getReal (ctx->component, &vr, 1, &r);
	moonLandingOuputs->output_altitute = r;

	vr = getValueReference (output_velocity_sv);
	fmi2Flag = ctx->fmus->getReal (ctx->component, &vr, 1, &r);
	moonLandingOuputs->output_velocity = r;

	return fmi2Flag;
}

/*int
Compute_Context(FMUContext * ctx){

	for(int i = 0 ; i < NUMBER_OF_FMUS; i++){
		doStep (&ctx->fmus[i], ctx->component[i],
					ctx->currentCommunicationPoint,
					ctx->communicationStepSize,
					ctx->noSetFMUStatePriorToCurrentPoint);
	}

	ctx->currentCommunicationPoint += ctx->communicationStepSize;

	outputRow_local (NUMBER_OF_FMUS, NAMES_OF_FMUS, ctx->fmus, ctx->component, ctx->currentCommunicationPoint, ctx->resultFile, ',', fmi2False);

	return 1;
}*/



/******************************************************************************
 */

int
main (int argc, char *argv[])
{
	double 			tStart = 0.0;
	double          tEnd = 2.0;
	double          h = 0.1;
	int             loggingOn = 0;
	char            csv_separator = ',';
	fmi2String     *categories = NULL;
	//char **categories = NULL;
	int             nCategories = 0;
	fmi2Boolean visible = fmi2False;

	FMUContext      ctx;

	//parseArguments(argc, argv, &tEnd, &h, &loggingOn, &csv_separator, &nCategories, &categories);
	//parseArguments(argc, argv, &fmuFileNames, &tEnd, &h, &loggingOn, &csv_separator, &nCategories, &categories);

	ctx.fmus = calloc(NUMBER_OF_FMUS, sizeof(FMU));
	ctx.component = calloc(NUMBER_OF_FMUS, sizeof(fmi2Component));

	/* 1/ FMU Activate Entrypoint */
	FMU_Activate_Entrypoint(NUMBER_OF_FMUS, NAMES_OF_FMUS, tEnd, h,
			loggingOn, csv_separator, nCategories, categories, &ctx);

	while (ctx.currentCommunicationPoint < tEnd) {

		//Compute_Entrypoint_MoonLanding (&ctx, inputThrust, moonLandingOuputs);

		for(int i = 0 ; i < NUMBER_OF_FMUS; i++){
			doStep (&(ctx.fmus[i]), ctx.component[i],
				ctx.currentCommunicationPoint,
				ctx.communicationStepSize,
				ctx.noSetFMUStatePriorToCurrentPoint);
		}

		ctx.currentCommunicationPoint += ctx.communicationStepSize;

		outputRow_local (NUMBER_OF_FMUS, NAMES_OF_FMUS, ctx.fmus, ctx.component, ctx.currentCommunicationPoint, ctx.resultFile, ',', fmi2False);
	}

	freeContext (ctx, NUMBER_OF_FMUS);

	//fclose (ctx.resultFile);
	printf ("CSV file written\n\n");



	/* MoonLanding specific part */

	/*fmi2Real        inputThrust;
  MoonLandingOuputs *moonLandingOuputs;
  moonLandingOuputs = (MoonLandingOuputs *) malloc (sizeof (MoonLandingOuputs));
  assert (moonLandingOuputs != NULL);*/

	/* 2/ Processing loop */

	/*while (ctx.currentCommunicationPoint < tEnd) {
    /* a) stupid controller that "just works" */

	/* This controller brings the lander close to the ground, at
       around t = 59.4, after that the lander eventually flies back */

	/*if (ctx.currentCommunicationPoint >= 0.0
        && ctx.currentCommunicationPoint < 59.4)
      inputThrust = 2568500.0;
    else
      if (ctx.currentCommunicationPoint < 100.0)
        inputThrust = 140000.0;
      else
        inputThrust = 0.0;

    /* b) Compute_Entrypoint */
	/*Compute_Entrypoint_MoonLanding (&ctx, inputThrust, moonLandingOuputs);

    printf ("%f %f %f %f\n", ctx.currentCommunicatiœonPoint,
            inputThrust,
            moonLandingOuputs->output_altitute,
            moonLandingOuputs->output_velocity);

    /* c) "time" management */

	//ctx.currentCommunicationPoint += ctx.communicationStepSize;
	//}

	/* End simulation */
	//printf ("\nEnd of the simulation.\n\n");

	//free (moonLandingOuputs);
	//freeContext (ctx);

	return EXIT_SUCCESS;
}
