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


/*#define NUMBER_OF_FMUS 2
#define NUMBER_OF_EDGES 1
#define MODEL_NAME "demo"

const char* NAMES_OF_FMUS[] = {"inc20pt.fmu", "scale20pt.fmu"};
*/
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

/*
void parseArguments2(int argc, char *argv[], int *nb_FMU, fmi2Real *tEnd, fmi2Real *h,
		int *loggingOn, char *csv_separator, int *nCategories, fmi2String *logCategories[]) {
	// parse command line arguments

	if (argc > 1) {
		if (sscanf(argv[1],"%d", nb_FMU) != 1) {
			printf("error: The given number of FMU (%s) is not a number\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	} else {
		printf("error: no fmu file\n");
		printHelp(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (argc > 2) {
		if (sscanf(argv[2],"%lf", tEnd) != 1) {
			printf("error: The given end time (%s) is not a number\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}
	if (argc > 3) {
		if (sscanf(argv[3],"%lf", h) != 1) {
			printf("error: The given stepsize (%s) is not a number\n", argv[3]);
			exit(EXIT_FAILURE);
		}
	}
	if (argc > 4) {
		if (sscanf(argv[4],"%d", loggingOn) != 1 || *loggingOn < 0 || *loggingOn > 1) {
			printf("error: The given logging flag (%s) is not boolean\n", argv[4]);
			exit(EXIT_FAILURE);
		}
	}
	if (argc > 5) {
		if (strlen(argv[5]) != 1) {
			printf("error: The given CSV separator char (%s) is not valid\n", argv[5]);
			exit(EXIT_FAILURE);
		}
		switch (argv[5][0]) {
		case 'c': *csv_separator = ','; break; // comma
		case 's': *csv_separator = ';'; break; // semicolon
		default:  *csv_separator = argv[5][0]; break; // any other char
		}
	}
	if (argc > 6) {
		int i;
		*nCategories = argc - 6;
		*logCategories = (fmi2String *)calloc(sizeof(char *), *nCategories);
		for (i = 0; i < *nCategories; i++) {
			(*logCategories)[i] = argv[i + 6];
		}
	}
}
*/
/*
void setupConnections(FMU* fmus, portConnection* connections) {
	connections[0].sourceFMU = &fmus[0];
	connections[0].sourcePort = getValueReference(getScalarVariable(fmus[0].modelDescription, 0));
	connections[0].sourceType = fmi2_Integer;
	connections[0].sinkFMU = &fmus[1];
	connections[0].sinkPort = getValueReference(getScalarVariable(fmus[1].modelDescription, 0));
	connections[0].sinkType = fmi2_Real;

	connections[1].sourceFMU = &fmus[1];
    connections[1].sourcePort = getValueReference(getScalarVariable(fmus[1].modelDescription, 1));
    connections[1].sourceType = fmi2_Real;
    connections[1].sinkFMU = &fmus[2];
    connections[1].sinkPort = getValueReference(getScalarVariable(fmus[2].modelDescription, 0));
    connections[1].sinkType = fmi2_Real;
}
*/
/*
static fmi2Status checkForLegacyFMUs(FMU* fmus, bool *isLegacyFmu, int*legacyFmuIndex) {

	printf("Checking for legacy FMUs!\n");
	int legacyFmus = 0;

	for (int i = 0; i < NUMBER_OF_FMUS; i++) {
		if (!fmus[i].canGetAndSetFMUstate) {
			legacyFmus++;
			*legacyFmuIndex = i;
			*isLegacyFmu = true;
			if (legacyFmus > 1) {
				printf("More than one legacy FMU detected. The system cannot be simulated.\n");
				return fmi2Error;
			}
		}
	}

	return fmi2OK;
}
*/
/*
void terminateSimulation(FMU *fmus, int returnValue, FILE* file, double h,
		int nSteps, double tStart, double tEnd) {

	const char* STATUS[] = { "fmi2OK", "fmi2Warning", "fmi2Discard",
			"fmi2Error", "fmi2Fatal", "fmi2Pending" };

	for (int i = 0; i < NUMBER_OF_FMUS; i++) {
		fmus[i].terminate(fmus[i].component);
		if (fmus[i].lastFMUstate != NULL) {
			fmi2Status status = fmus[i].freeFMUstate(fmus[i].component,
					&fmus[i].lastFMUstate);
			printf("Terminating with status: %s\n", STATUS[status]);
		}

		fmus[i].freeInstance(fmus[i].component);
	}

	// print simulation summary
	if (returnValue == 1) {
		printf("Simulation from %g to %g terminated successful\n", tStart,
				tEnd);
	} else {
		printf("Simulation from %g to %g terminated early!\n", tStart, tEnd);
	}
	printf("  steps ............ %d\n", nSteps);
	printf("  fixed step size .. %g\n", h);
	fclose(file);

	return;
}
*/
/*
static fmi2Status setValue(portConnection* connection) {
	fmi2Status fmi2Flag;
	fmi2Integer tempInt;
	fmi2Real tempReal;
	fmi2Boolean tempBoolean;
	fmi2String tempString;

	// get source value and cast if necessary
	switch (connection->sourceType) {
	case fmi2_Integer:
		fmi2Flag = connection->sourceFMU->getInteger(connection->sourceFMU->component, &connection->sourcePort, 1, &tempInt);
		tempReal = (fmi2Real) tempInt;
		tempBoolean = (tempInt == 0 ? fmi2False : fmi2True);
		break;
	case fmi2_Real:
		fmi2Flag = connection->sourceFMU->getReal(connection->sourceFMU->component, &connection->sourcePort, 1, &tempReal);
		tempInt = (fmi2Integer) round(tempReal);
		tempBoolean = (tempReal == 0.0 ? fmi2False : fmi2True);
		break;
	case fmi2_Boolean:
		fmi2Flag = connection->sourceFMU->getBoolean(connection->sourceFMU->component, &connection->sourcePort, 1, &tempBoolean);
		tempInt = (fmi2Integer) tempBoolean;
		tempReal = (fmi2Real) tempBoolean;
		break;
	case fmi2_String:
		fmi2Flag = connection->sourceFMU->getString(connection->sourceFMU->component, &connection->sourcePort, 1, &tempString);
		break;
	default:
		return fmi2Error;
	}

	if (fmi2Flag > fmi2Warning) {
		printf("Getting the value of an FMU caused an error.");
		return fmi2Flag;
	}

	if (connection->sourceType != connection->sinkType && (connection->sinkType == fmi2_String || connection->sourceType == fmi2_String)) {
		printf("A connection of FMUs has incompatible data types. Terminating simulation.\n");
		return fmi2Error;
	}

	// set sink value
	switch (connection->sinkType) {
	case fmi2_Integer:
		fmi2Flag = connection->sinkFMU->setInteger(connection->sinkFMU->component, &connection->sinkPort, 1, &tempInt);
		break;
	case fmi2_Real:
		fmi2Flag = connection->sinkFMU->setReal(connection->sinkFMU->component, &connection->sinkPort, 1, &tempReal);
		break;
	case fmi2_Boolean:
		fmi2Flag = connection->sinkFMU->setBoolean(connection->sinkFMU->component, &connection->sinkPort, 1, &tempBoolean);
		break;
	case fmi2_String:
		fmi2Flag = connection->sinkFMU->setString(connection->sinkFMU->component, &connection->sinkPort, 1, &tempString);
		break;
	default:
		return fmi2Error;
	}
	return fmi2Flag;
}
*/
/*
static fmi2Status rollbackFMUs(FMU *fmus) {
	for (int i = 0; i < NUMBER_OF_FMUS; i++) {
		if (fmus[i].canGetAndSetFMUstate && !fmus[i].canGetMaxStepSize) {
			fmi2Status localStatus = fmus[i].setFMUstate(fmus[i].component, fmus[i].lastFMUstate);
			if (localStatus > fmi2Warning) {
				printf("Rolling back FMU (%s) failed!\n", NAMES_OF_FMUS[i]);
				return localStatus;
			}
		}
	}
	return fmi2OK;
}
*/
// simulate the given FMUs from tStart = 0 to tEnd.
/*static int simulate(FMUContext * ctx, portConnection* connections, double h,
		fmi2Boolean loggingOn, char separator, double tStart, double tEnd) {

	// Simulation variables
	fmi2Real time = tStart;
	fmi2Real stepSize = h;
	int nSteps = 0;
	//FILE* file;
	int legacyFmuIndex = 0;
	bool isLegacyFmu = false;

	// Open result file
	if (!(file = fopen(RESULT_FILE, "w"))) {
		printf("could not write %s because:\n", RESULT_FILE);
		printf("    %s\n", strerror(errno));
		return 0;
	}

	// Check for legacy FMUs
	if (checkForLegacyFMUs(ctx->fmus, &isLegacyFmu, &legacyFmuIndex) > fmi2Warning) {
		terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
		return 0;
	}

	// output solution for time t0
	//outputRow(ctx->fmus, NUMBER_OF_FMUS, NAMES_OF_FMUS, time, ctx->resultFile, separator, TRUE);
	//outputRow(ctx->fmus, NUMBER_OF_FMUS, NAMES_OF_FMUS, time, ctx->resultFile, separator, FALSE);

	// Simulation loop
	while (time < tEnd) {

		// Set connection values
		for (int i = 0; i < NUMBER_OF_EDGES; i++) {
			setValue(&connections[i]);
		}

		// Compute the maximum step size
		// (I) Predictable FMUs
		for (int i = 0; i < NUMBER_OF_FMUS; i++) {
			if (ctx->fmus[i].canGetMaxStepSize) {

				fmi2Real maxStepSize;
				fmi2Status currentStatus = ctx->fmus[i].getMaxStepSize(ctx->fmus[i].component, &maxStepSize);
				if (currentStatus > fmi2Warning) {
					printf("Could get the MaxStepSize for FMU (%s). Terminating simulation.\n", NAMES_OF_FMUS[i]);
					terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
					return 0;
				}
				stepSize = min(stepSize, maxStepSize);
			}
		}



		// Compute the maximum step size
		// (II) Rollback FMUs
		for (int i = 0; i < NUMBER_OF_FMUS; i++) {
			if (ctx->fmus[i].canGetAndSetFMUstate && !ctx->fmus[i].canGetMaxStepSize) {
				fmi2Real maxStepSize;
				fmi2Status currentStatus = ctx->fmus[i].getFMUstate(ctx->fmus[i].component, &(ctx->fmus[i]).lastFMUstate);
				if (currentStatus > fmi2Warning) {
					printf("Saving state of FMU (%s) failed. Terminating simulation. Terminating simulation.\n", NAMES_OF_FMUS[i]);
					terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
					return 0;
				}
				currentStatus = ctx->fmus[i].doStep(ctx->fmus[i].component, time, stepSize, fmi2False);
				if (currentStatus > fmi2Discard) {
					printf("Could not step FMU (%s) while determining the step size. Terminating simulation.\n", NAMES_OF_FMUS[i]);
					terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
					return 0;
				}
				fmi2Real lastSuccessfulTime;
				currentStatus = ctx->fmus[i].getRealStatus(ctx->fmus[i].component, fmi2LastSuccessfulTime, &lastSuccessfulTime);
				if (currentStatus > fmi2Warning) {
					printf("Could get the last successful time instant for FMU (%s). Terminating simulation.\n", NAMES_OF_FMUS[i]);
					terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
					return 0;
				}
				maxStepSize = lastSuccessfulTime - time;
				stepSize = min(stepSize, maxStepSize);
			}
		}

		// Compute the maximum step size
		// (III) Legacy FMUs
		if (isLegacyFmu) {
			fmi2Real maxStepSize;
			fmi2Status currentStatus = ctx->fmus[legacyFmuIndex].doStep(ctx->fmus[legacyFmuIndex].component, time, stepSize, fmi2False);
			if (currentStatus > fmi2Discard) {
				printf("Could not step FMU (%s) [Legacy FMU]. Terminating simulation.\n", NAMES_OF_FMUS[legacyFmuIndex]);
				terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
				return 0;
			}
			fmi2Real lastSuccessfulTime;
			currentStatus = ctx->fmus[legacyFmuIndex].getRealStatus(ctx->fmus[legacyFmuIndex].component, fmi2LastSuccessfulTime, &lastSuccessfulTime);
			if (currentStatus > fmi2Warning) {
				printf("Could get the last successful time instant for FMU (%s). Terminating simulation.\n", NAMES_OF_FMUS[legacyFmuIndex]);
				terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
				return 0;
			}
			maxStepSize = lastSuccessfulTime - time;
			stepSize = min(stepSize, maxStepSize);
		}

		// Rolling back FMUs of type (II)
		{
			fmi2Status currentStatus = rollbackFMUs(ctx->fmus);
			if (currentStatus > fmi2Warning) {
				printf("Error while rolling back FMUs. Terminating simulation.");
				terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
				return 0;
			}
		}

		// Perform doStep() for all FMUs with the discovered stepSize
		for (int i = 0; i < NUMBER_OF_FMUS; i++) {
			if (ctx->fmus[i].canGetMaxStepSize || ctx->fmus[i].canGetAndSetFMUstate) {
				fmi2Status currentStatus = ctx->fmus[i].doStep(ctx->fmus[i].component, time, stepSize, fmi2False);
				if (currentStatus > fmi2Discard) {
					printf("Could not step FMU (%s) after minimum step has been determined. Terminating simulation.\n", NAMES_OF_FMUS[i]);
					terminateSimulation(ctx->fmus, 0, ctx->resultFile, h, nSteps, tStart, tEnd);
					return 0;
				}
			}
		}

		time += stepSize;
		outputRow(ctx->fmus, NUMBER_OF_FMUS, NAMES_OF_FMUS, time, ctx->resultFile, separator,FALSE);
		nSteps++;
	}

	terminateSimulation(ctx->fmus, 1, ctx->resultFile, h, nSteps, tStart, tEnd);
	return 1;
}
*/

int
main (int argc, char *argv[])
{
	//const char     *fmuFileName;

	//const char* fmuFileNames[NUMBER_OF_FMUS];


	double tStart = 0.0;
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

	//ctx.fmu = malloc (sizeof (FMU));
	ctx.fmus = calloc(NUMBER_OF_FMUS, sizeof(FMU));
	ctx.component = calloc(NUMBER_OF_FMUS, sizeof(fmi2Component));

	//portConnection* connections = calloc(NUMBER_OF_EDGES, sizeof(portConnection));

	/* 1/ FMU Activate Entrypoint */
	FMU_Activate_Entrypoint(NUMBER_OF_FMUS, NAMES_OF_FMUS, tEnd, h,
			loggingOn, csv_separator, nCategories, categories, &ctx);

	//setupConnections(ctx.fmus, connections);


	/*printf("FMU Simulator: run '%s' from t=0..%g with step size h=%g, "
			"loggingOn=%d, csv separator='%c' ", MODEL_NAME, tEnd, h, loggingOn, csv_separator);
	printf("log categories={ ");
	for (int i = 0; i < nCategories; i++) {
		printf("%s ", categories[i]);
	}
	printf("}\n");*/


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

	//simulate(&ctx, connections, h, loggingOn, csv_separator, tStart, tEnd);
	//printf("CSV file '%s' written\n", RESULT_FILE);


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
