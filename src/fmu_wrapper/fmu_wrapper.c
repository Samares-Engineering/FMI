#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fmi2.h"
#include "sim_support.h"
#include "fmu_wrapper.h"

#define FMU_WRAPPER_DEBUG

#ifdef FMU_WRAPPER_DEBUG
#define FMU_WRAPPER_PRINT(s, args...) fprintf(stderr, s, ##args); fflush (stderr);
#else
#define FMU_WRAPPER_PRINT(s, args...)
#endif

int fmuImport (const char *fmuFileName, FMU * fmu);

int initializeModel (FMU * fmu, fmi2Component c, const char *fmuFileName);

char *dummyresource = "file:///work/FMI/bin/foo/resources\\";

/******************************************************************************
 */

/* fmuFileName is an absolute path, e.g. "C:\test\a.fmu" */
/* or relative to the current dir, e.g. "..\test\a.fmu" */
static char    *
getFmuPath (const char *fmuFileName)
{
	/* Not sure why this is useful.  Just returning the filename. */
	return strdup (fmuFileName);
}

/******************************************************************************
 */

static char    *
getTmpPath ()
{
	char            template[13]; /* Lenght of "fmuTmpXXXXXX" + null */
	sprintf (template, "%s", "fmuTmpXXXXXX");
	char           *tmp = mkdtemp (template);
	if (tmp == NULL) {
		fprintf (stderr, "Couldn't create temporary directory\n");
		exit (1);
	}
	char           *results = calloc (sizeof (char), strlen (tmp) + 2);
	strncat (results, tmp, strlen (tmp));
	return strcat (results, "/");
}

/******************************************************************************
 */

static void
printModelDescription (ModelDescription * md)
{
	Element        *e = (Element *) md;
	int             n;            /* number of attributes */
	const char    **attributes = getAttributesAsArray (e, &n);
	Component      *component;

	if (!attributes) {
		FMU_WRAPPER_PRINT ("ModelDescription printing aborted.");
		return;
	}
#ifdef FMU_WRAPPER_DEBUG
	FMU_WRAPPER_PRINT ("%s\n", getElementTypeName (e));
	for (int i = 0; i < n; i += 2) {
		FMU_WRAPPER_PRINT ("  %s=%s\n", attributes[i], attributes[i + 1]);
	}
#endif                          /* FMU_WRAPPER_DEBUG */
	free ((void *)attributes);

#ifdef FMI_COSIMULATION
	component = getCoSimulation (md);
	if (!component) {
		error ("No CoSimulation element found in model description. This FMU is not for Co-Simulation.\n");
		exit (EXIT_FAILURE);
	}
#else                           /* FMI_MODEL_EXCHANGE */
	component = getModelExchange (md);
	if (!component) {
		error ("No ModelExchange element found in model description. This FMU is not for Model Exchange.\n");
		exit (EXIT_FAILURE);
	}
#endif                          /* FMI_COSIMULATION */

#ifdef FMU_WRAPPER_DEBUG
	FMU_WRAPPER_PRINT ("%s\n", getElementTypeName ((Element *) component));
	attributes = getAttributesAsArray ((Element *) component, &n);
	if (!attributes) {
		FMU_WRAPPER_PRINT ("ModelDescription printing aborted.");
		return;
	}
	for (int i = 0; i < n; i += 2) {
		FMU_WRAPPER_PRINT ("  %s=%s\n", attributes[i], attributes[i + 1]);
	}

	FMU_WRAPPER_PRINT ("\n\n");

	free ((void *)attributes);
#endif

}

/******************************************************************************
 */

static void    *
getAdr (int *success, HMODULE dllHandle, const char *functionName)
{
	void           *fp;
#ifdef _MSC_VER
	fp = GetProcAddress (dllHandle, functionName);
#else
	fp = dlsym (dllHandle, functionName);
#endif
	if (!fp) {
#ifdef _MSC_VER
#else
		FMU_WRAPPER_PRINT ("Error was: %s\n", dlerror ());
#endif
		FMU_WRAPPER_PRINT ("warning: Function %s not found in dll\n", functionName);
		*success = 0;
	}
	return fp;
}

/******************************************************************************
 */

/* Load the given dll and set function pointers in fmu */
/* Return 0 to indicate failure */
static int
loadDll (const char *dllPath, FMU * fmu)
{
	int             s = 1;
#ifdef _MSC_VER
	HMODULE         h = LoadLibrary (dllPath);
#else
	FMU_WRAPPER_PRINT ("dllPath = %s\n", dllPath);
	HMODULE         h = dlopen (dllPath, RTLD_LAZY);
#endif

	if (!h) {
		FMU_WRAPPER_PRINT ("error: Could not load %s\n", dllPath);
#ifdef _MSC_VER
#else
		FMU_WRAPPER_PRINT ("The error was: %s\n", dlerror ());
#endif
		return 0;                   /* failure */
	}
	fmu->dllHandle = h;
	fmu->getTypesPlatform          = (fmi2GetTypesPlatformTYPE *)      getAdr(&s, h, "fmi2GetTypesPlatform");
	fmu->getVersion                = (fmi2GetVersionTYPE *)            getAdr(&s, h, "fmi2GetVersion");
	fmu->setDebugLogging           = (fmi2SetDebugLoggingTYPE *)       getAdr(&s, h, "fmi2SetDebugLogging");
	fmu->instantiate               = (fmi2InstantiateTYPE *)           getAdr(&s, h, "fmi2Instantiate");
	fmu->freeInstance              = (fmi2FreeInstanceTYPE *)          getAdr(&s, h, "fmi2FreeInstance");
	fmu->setupExperiment           = (fmi2SetupExperimentTYPE *)       getAdr(&s, h, "fmi2SetupExperiment");
	fmu->enterInitializationMode   = (fmi2EnterInitializationModeTYPE *) getAdr(&s, h, "fmi2EnterInitializationMode");
	fmu->exitInitializationMode    = (fmi2ExitInitializationModeTYPE *) getAdr(&s, h, "fmi2ExitInitializationMode");
	fmu->terminate                 = (fmi2TerminateTYPE *)             getAdr(&s, h, "fmi2Terminate");
	fmu->reset                     = (fmi2ResetTYPE *)                 getAdr(&s, h, "fmi2Reset");
	fmu->getReal                   = (fmi2GetRealTYPE *)               getAdr(&s, h, "fmi2GetReal");
	fmu->getInteger                = (fmi2GetIntegerTYPE *)            getAdr(&s, h, "fmi2GetInteger");
	fmu->getBoolean                = (fmi2GetBooleanTYPE *)            getAdr(&s, h, "fmi2GetBoolean");
	fmu->getString                 = (fmi2GetStringTYPE *)             getAdr(&s, h, "fmi2GetString");
	fmu->setReal                   = (fmi2SetRealTYPE *)               getAdr(&s, h, "fmi2SetReal");
	fmu->setInteger                = (fmi2SetIntegerTYPE *)            getAdr(&s, h, "fmi2SetInteger");
	fmu->setBoolean                = (fmi2SetBooleanTYPE *)            getAdr(&s, h, "fmi2SetBoolean");
	fmu->setString                 = (fmi2SetStringTYPE *)             getAdr(&s, h, "fmi2SetString");
	fmu->getFMUstate               = (fmi2GetFMUstateTYPE *)           getAdr(&s, h, "fmi2GetFMUstate");
	fmu->setFMUstate               = (fmi2SetFMUstateTYPE *)           getAdr(&s, h, "fmi2SetFMUstate");
	fmu->freeFMUstate              = (fmi2FreeFMUstateTYPE *)          getAdr(&s, h, "fmi2FreeFMUstate");
	fmu->serializedFMUstateSize    = (fmi2SerializedFMUstateSizeTYPE *) getAdr(&s, h, "fmi2SerializedFMUstateSize");
	fmu->serializeFMUstate         = (fmi2SerializeFMUstateTYPE *)     getAdr(&s, h, "fmi2SerializeFMUstate");
	fmu->deSerializeFMUstate       = (fmi2DeSerializeFMUstateTYPE *)   getAdr(&s, h, "fmi2DeSerializeFMUstate");
	fmu->getDirectionalDerivative  = (fmi2GetDirectionalDerivativeTYPE *) getAdr(&s, h, "fmi2GetDirectionalDerivative");

#ifdef FMI_COSIMULATION
	fmu->setRealInputDerivatives   = (fmi2SetRealInputDerivativesTYPE *) getAdr(&s, h, "fmi2SetRealInputDerivatives");
	fmu->getRealOutputDerivatives  = (fmi2GetRealOutputDerivativesTYPE *) getAdr(&s, h, "fmi2GetRealOutputDerivatives");
	fmu->doStep                    = (fmi2DoStepTYPE *)                getAdr(&s, h, "fmi2DoStep");
	fmu->cancelStep                = (fmi2CancelStepTYPE *)            getAdr(&s, h, "fmi2CancelStep");
	fmu->getStatus                 = (fmi2GetStatusTYPE *)             getAdr(&s, h, "fmi2GetStatus");
	fmu->getRealStatus             = (fmi2GetRealStatusTYPE *)         getAdr(&s, h, "fmi2GetRealStatus");
	fmu->getIntegerStatus          = (fmi2GetIntegerStatusTYPE *)      getAdr(&s, h, "fmi2GetIntegerStatus");
	fmu->getBooleanStatus          = (fmi2GetBooleanStatusTYPE *)      getAdr(&s, h, "fmi2GetBooleanStatus");
	fmu->getStringStatus           = (fmi2GetStringStatusTYPE *)       getAdr(&s, h, "fmi2GetStringStatus");
	/* Methods for Hybrid Co-Simulation */
	/*fmu->doHybridStep              = (fmi2HybridDoStepTYPE *)          getAdr(&s, h, "fmi2HybridDoStep");
	fmu->getHybridMaxStepSize      = (fmi2HybridGetMaxStepSizeTYPE *)  getAdr(&s, h, "fmi2HybridGetMaxStepSize");
	fmu->setupHybridExperiment     = (fmi2HybridSetupExperimentTYPE *) getAdr(&s, h, "fmi2HybridSetupExperiment");
	fmu->getHybridReal             = (fmi2GetHybridRealTYPE *)         getAdr(&s, h, "fmi2GetHybridReal");
	fmu->getHybridInteger          = (fmi2GetHybridIntegerTYPE *)      getAdr(&s, h, "fmi2GetHybridInteger");
	fmu->getHybridBoolean          = (fmi2GetHybridBooleanTYPE *)      getAdr(&s, h, "fmi2GetHybridBoolean");
	fmu->getHybridString           = (fmi2GetHybridStringTYPE *)       getAdr(&s, h, "fmi2GetHybridString");
	fmu->setHybridReal             = (fmi2SetHybridRealTYPE *)         getAdr(&s, h, "fmi2SetHybridReal");
	fmu->setHybridInteger          = (fmi2SetHybridIntegerTYPE *)      getAdr(&s, h, "fmi2SetHybridInteger");
	fmu->setHybridBoolean          = (fmi2SetHybridBooleanTYPE *)      getAdr(&s, h, "fmi2SetHybridBoolean");
	fmu->setHybridString           = (fmi2SetHybridStringTYPE *)       getAdr(&s, h, "fmi2SetHybridString");*/
	//fmu->getMaxStepSize 		   = (fmi2GetMaxStepSizeTYPE *)		   getAdr(&s, h, "fmi2GetMaxStepSizeTYPE");
#else // FMI for Model Exchange
	fmu->enterEventMode            = (fmi2EnterEventModeTYPE *)        getAdr(&s, h, "fmi2EnterEventMode");
	fmu->newDiscreteStates         = (fmi2NewDiscreteStatesTYPE *)     getAdr(&s, h, "fmi2NewDiscreteStates");
	fmu->enterContinuousTimeMode   = (fmi2EnterContinuousTimeModeTYPE *) getAdr(&s, h, "fmi2EnterContinuousTimeMode");
	fmu->completedIntegratorStep   = (fmi2CompletedIntegratorStepTYPE *) getAdr(&s, h, "fmi2CompletedIntegratorStep");
	fmu->setTime                   = (fmi2SetTimeTYPE *)               getAdr(&s, h, "fmi2SetTime");
	fmu->setContinuousStates       = (fmi2SetContinuousStatesTYPE *)   getAdr(&s, h, "fmi2SetContinuousStates");
	fmu->getDerivatives            = (fmi2GetDerivativesTYPE *)        getAdr(&s, h, "fmi2GetDerivatives");
	fmu->getEventIndicators        = (fmi2GetEventIndicatorsTYPE *)    getAdr(&s, h, "fmi2GetEventIndicators");
	fmu->getContinuousStates       = (fmi2GetContinuousStatesTYPE *)   getAdr(&s, h, "fmi2GetContinuousStates");
	fmu->getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *) getAdr(&s, h, "fmi2GetNominalsOfContinuousStates");
#endif

	if (fmu->getVersion == NULL && fmu->instantiate == NULL) {
		FMU_WRAPPER_PRINT ("warning: Functions from FMI 2.0 could not be found in %s\n", dllPath);
		FMU_WRAPPER_PRINT ("warning: Simulator will look for FMI 2.0 RC1 functions names...\n");
		fmu->getTypesPlatform = (fmi2GetTypesPlatformTYPE *) getAdr (&s, h, "fmiGetTypesPlatform");
		fmu->getVersion = (fmi2GetVersionTYPE *) getAdr (&s, h, "fmiGetVersion");
		fmu->setDebugLogging = (fmi2SetDebugLoggingTYPE *) getAdr (&s, h, "fmiSetDebugLogging");
		fmu->instantiate = (fmi2InstantiateTYPE *) getAdr (&s, h, "fmiInstantiate");
		fmu->freeInstance = (fmi2FreeInstanceTYPE *) getAdr (&s, h, "fmiFreeInstance");
		fmu->setupExperiment = (fmi2SetupExperimentTYPE *) getAdr (&s, h, "fmiSetupExperiment");
		fmu->enterInitializationMode = (fmi2EnterInitializationModeTYPE *) getAdr (&s, h, "fmiEnterInitializationMode");
		fmu->exitInitializationMode = (fmi2ExitInitializationModeTYPE *) getAdr (&s, h, "fmiExitInitializationMode");
		fmu->terminate = (fmi2TerminateTYPE *) getAdr (&s, h, "fmiTerminate");
		fmu->reset = (fmi2ResetTYPE *) getAdr (&s, h, "fmiReset");
		fmu->getReal = (fmi2GetRealTYPE *) getAdr (&s, h, "fmiGetReal");
		fmu->getInteger = (fmi2GetIntegerTYPE *) getAdr (&s, h, "fmiGetInteger");
		fmu->getBoolean = (fmi2GetBooleanTYPE *) getAdr (&s, h, "fmiGetBoolean");
		fmu->getString = (fmi2GetStringTYPE *) getAdr (&s, h, "fmiGetString");
		fmu->setReal = (fmi2SetRealTYPE *) getAdr (&s, h, "fmiSetReal");
		fmu->setInteger = (fmi2SetIntegerTYPE *) getAdr (&s, h, "fmiSetInteger");
		fmu->setBoolean = (fmi2SetBooleanTYPE *) getAdr (&s, h, "fmiSetBoolean");
		fmu->setString = (fmi2SetStringTYPE *) getAdr (&s, h, "fmiSetString");
		fmu->getFMUstate = (fmi2GetFMUstateTYPE *) getAdr (&s, h, "fmiGetFMUstate");
		fmu->setFMUstate = (fmi2SetFMUstateTYPE *) getAdr (&s, h, "fmiSetFMUstate");
		fmu->freeFMUstate = (fmi2FreeFMUstateTYPE *) getAdr (&s, h, "fmiFreeFMUstate");
		fmu->serializedFMUstateSize = (fmi2SerializedFMUstateSizeTYPE *) getAdr (&s, h, "fmiSerializedFMUstateSize");
		fmu->serializeFMUstate = (fmi2SerializeFMUstateTYPE *) getAdr (&s, h, "fmiSerializeFMUstate");
		fmu->deSerializeFMUstate = (fmi2DeSerializeFMUstateTYPE *) getAdr (&s, h, "fmiDeSerializeFMUstate");
		fmu->getDirectionalDerivative = (fmi2GetDirectionalDerivativeTYPE *) getAdr (&s, h, "fmiGetDirectionalDerivative");
#ifdef FMI_COSIMULATION
		fmu->setRealInputDerivatives = (fmi2SetRealInputDerivativesTYPE *) getAdr (&s, h, "fmiSetRealInputDerivatives");
		fmu->getRealOutputDerivatives = (fmi2GetRealOutputDerivativesTYPE *) getAdr (&s, h, "fmiGetRealOutputDerivatives");
		fmu->doStep = (fmi2DoStepTYPE *) getAdr (&s, h, "fmiDoStep");
		fmu->cancelStep = (fmi2CancelStepTYPE *) getAdr (&s, h, "fmiCancelStep");
		fmu->getStatus = (fmi2GetStatusTYPE *) getAdr (&s, h, "fmiGetStatus");
		fmu->getRealStatus = (fmi2GetRealStatusTYPE *) getAdr (&s, h, "fmiGetRealStatus");
		fmu->getIntegerStatus = (fmi2GetIntegerStatusTYPE *) getAdr (&s, h, "fmiGetIntegerStatus");
		fmu->getBooleanStatus = (fmi2GetBooleanStatusTYPE *) getAdr (&s, h, "fmiGetBooleanStatus");
		fmu->getStringStatus = (fmi2GetStringStatusTYPE *) getAdr (&s, h, "fmiGetStringStatus");
		/* Methods for Hybrid Co-Simulation */
		/*fmu->doHybridStep              = (fmi2HybridDoStepTYPE *)          getAdr(&s, h, "fmi2HybridDoStep");
		fmu->getHybridMaxStepSize      = (fmi2HybridGetMaxStepSizeTYPE *)  getAdr(&s, h, "fmi2HybridGetMaxStepSize");
		fmu->setupHybridExperiment     = (fmi2HybridSetupExperimentTYPE *) getAdr(&s, h, "fmi2HybridSetupExperiment");
		fmu->getHybridReal             = (fmi2GetHybridRealTYPE *)         getAdr(&s, h, "fmi2GetHybridReal");
		fmu->getHybridInteger          = (fmi2GetHybridIntegerTYPE *)      getAdr(&s, h, "fmi2GetHybridInteger");
		fmu->getHybridBoolean          = (fmi2GetHybridBooleanTYPE *)      getAdr(&s, h, "fmi2GetHybridBoolean");
		fmu->getHybridString           = (fmi2GetHybridStringTYPE *)       getAdr(&s, h, "fmi2GetHybridString");
		fmu->setHybridReal             = (fmi2SetHybridRealTYPE *)         getAdr(&s, h, "fmi2SetHybridReal");
		fmu->setHybridInteger          = (fmi2SetHybridIntegerTYPE *)      getAdr(&s, h, "fmi2SetHybridInteger");
		fmu->setHybridBoolean          = (fmi2SetHybridBooleanTYPE *)      getAdr(&s, h, "fmi2SetHybridBoolean");
		fmu->setHybridString           = (fmi2SetHybridStringTYPE *)       getAdr(&s, h, "fmi2SetHybridString");
		fmu->getMaxStepSize 		   = (fmi2GetMaxStepSizeTYPE *)		   getAdr(&s, h, "fmi2GetMaxStepSizeTYPE");*/

#else   /* FMI2 for Model Exchange */
		fmu->enterEventMode = (fmi2EnterEventModeTYPE *) getAdr (&s, h, "fmiEnterEventMode");
		fmu->newDiscreteStates = (fmi2NewDiscreteStatesTYPE *) getAdr (&s, h, "fmiNewDiscreteStates");
		fmu->enterContinuousTimeMode = (fmi2EnterContinuousTimeModeTYPE *) getAdr (&s, h, "fmiEnterContinuousTimeMode");
		fmu->completedIntegratorStep = (fmi2CompletedIntegratorStepTYPE *) getAdr (&s, h, "fmiCompletedIntegratorStep");
		fmu->setTime = (fmi2SetTimeTYPE *) getAdr (&s, h, "fmiSetTime");
		fmu->setContinuousStates = (fmi2SetContinuousStatesTYPE *) getAdr (&s, h, "fmiSetContinuousStates");
		fmu->getDerivatives = (fmi2GetDerivativesTYPE *) getAdr (&s, h, "fmiGetDerivatives");
		fmu->getEventIndicators = (fmi2GetEventIndicatorsTYPE *) getAdr (&s, h, "fmiGetEventIndicators");
		fmu->getContinuousStates = (fmi2GetContinuousStatesTYPE *) getAdr (&s, h, "fmiGetContinuousStates");
		fmu->getNominalsOfContinuousStates = (fmi2GetNominalsOfContinuousStatesTYPE *) getAdr (&s, h, "fmiGetNominalsOfContinuousStates");
#endif
	}
	return s;
}

/******************************************************************************
 */

char            dummyPath[] = "foo/";

int
fmuImport (const char* fmuFileName, FMU * fmu)
{
	char           *fmuPath;
	char           *tmpPath;
	char           *xmlPath;
	char           *dllPath;
	const char     *modelId;

	FMU_WRAPPER_PRINT ("Loading FMU %s. \n\n", fmuFileName);

	fmuPath = getFmuPath (fmuFileName);
	if (!fmuPath)
		exit (EXIT_FAILURE);


	FMU_WRAPPER_PRINT ("FMU Path %s. \n\n", fmuPath);
	/* tmpPath = getTmpPath(); */
	tmpPath = dummyPath;

	FMU_WRAPPER_PRINT ("Unzip the %s file.\n\n", fmuFileName);
	if (!unzip (fmuPath, tmpPath))
		exit (EXIT_FAILURE);

	FMU_WRAPPER_PRINT ("Parse modeldescription.xml file.\n\n");
	xmlPath = calloc (sizeof (char), strlen (tmpPath) + strlen (XML_FILE) + 1);
	sprintf (xmlPath, "%s%s", tmpPath, XML_FILE);
	fmu->modelDescription = parse (xmlPath);
	free (xmlPath);

	printModelDescription (fmu->modelDescription);
	modelId = getAttributeValue ((Element *) getCoSimulation (fmu->modelDescription), att_modelIdentifier);
	dllPath = calloc (sizeof (char), strlen (tmpPath) + strlen (DLL_DIR)
			+ strlen (modelId) + strlen (DLL_SUFFIX) + 1);
	sprintf (dllPath, "%s%s%s%s", tmpPath, DLL_DIR, modelId, DLL_SUFFIX);

	FMU_WRAPPER_PRINT ("Load DLL file.\n\n");
	if (!loadDll (dllPath, fmu)) {
		free (dllPath);

		dllPath = calloc (sizeof (char), strlen (tmpPath) + strlen (DLL_DIR2)
				+ strlen (modelId) + strlen (DLL_SUFFIX2) + 1);
		sprintf (dllPath, "%s%s%s%s", tmpPath, DLL_DIR2, modelId, DLL_SUFFIX2);
		if (!loadDll (dllPath, fmu))
			exit (EXIT_FAILURE);
	}
	free (dllPath);
	free (fmuPath);
	//free(tmpPath);

	FMU_WRAPPER_PRINT ("FMU %s Loaded.\n\n", fmuFileName);

	return 1;                     /* Success */
}

/******************************************************************************
 */

int
doStep (FMU * fmu, fmi2Component c, fmi2Real currentCommunicationPoint,
		fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint)
{

	fmi2Status      fmi2Flag;

	fmi2Flag = fmu->doStep (c, currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint);
	if (fmi2Flag == fmi2Discard) {
		fmi2Boolean     b;

		if (fmi2OK != fmu->getBooleanStatus (c, fmi2Terminated, &b)) {
			return error ("Could not complete simulation of the model. getBooleanStatus return other than fmi2OK.\n\n");
		}
		if (b == fmi2True) {
			return error ("The model requested to end the simulation.\n\n");
		}
		return error ("Could not complete simulation of the model.\n\n");
	}
	/*
	 * if (fmi2Flag != fmi2OK) return error("Could not complete simulation of the
	 * model.\n\n");
	 */

	FMU_WRAPPER_PRINT ("Do one step. %d\n\n", fmi2Flag);

	return fmi2Flag;
}

/******************************************************************************
 */

//static fmi2Component initializeFMU(FMU *fmu, fmi2Boolean visible, fmi2Boolean loggingOn, int nCategories, const fmi2String categories[], double tStart, double tEnd) {

//fmi2Status fmi2Flag;                     // return code of the fmu functions

// instantiate the fmu
/*fmu->callbacks.logger = fmuLogger;
	fmu->callbacks.allocateMemory = calloc;
	fmu->callbacks.freeMemory = free;
	fmu->callbacks.stepFinished = NULL; // fmi2DoStep has to be carried out synchronously
	fmu->callbacks.componentEnvironment = fmu; // pointer to current fmu from the environment.

	fmi2Real tolerance = 0;                 // used in setting up the experiment
	fmi2Boolean toleranceDefined = fmi2False; // true if model description define tolerance
	ValueStatus vs = valueIllegal;

	// handle to the parsed XML file
	ModelDescription* md = fmu->modelDescription;
	// global unique id of the fmu
	const char *guid = getAttributeValue((Element *) md, att_guid);
	// check for ability to get and set state

	fmu->canGetAndSetFMUstate = getAttributeBool((Element*) getCoSimulation(md),
			att_canGetAndSetFMUstate, &vs);
	fmu->canGetMaxStepSize = getAttributeBool((Element*) getCoSimulation(md),
			att_canGetMaxStepSize, &vs);
	// instance name
	const char *instanceName = getAttributeValue(
			(Element *) getCoSimulation(md), att_modelIdentifier);
	// path to the fmu resources as URL, "file://C:\QTronic\sales"
	char *fmuResourceLocation = getTempResourcesLocation(); // TODO: returns crap. got to save the location for every FMU somehow.
	// instance of the fmu
	fmi2Component comp = fmu->instantiate(instanceName, fmi2CoSimulation, guid,
			fmuResourceLocation, &fmu->callbacks, visible, loggingOn);
	printf("instance name: %s, \nguid: %s, \nressourceLocation: %s\n",
			instanceName, guid, fmuResourceLocation);
	free(fmuResourceLocation);

	if (!comp) {
		printf("Could not initialize model with guid: %s\n", guid);
		return NULL;
	}

	Element *defaultExp = getDefaultExperiment(fmu->modelDescription);
	if (defaultExp) {
		tolerance = getAttributeDouble(defaultExp, att_tolerance, &vs);
	}
	if (vs == valueDefined) {
		toleranceDefined = fmi2True;
	}

	if (nCategories > 0) {
		fmi2Flag = fmu->setDebugLogging(comp, fmi2True, nCategories,
				(const fmi2String*) categories);
		if (fmi2Flag > fmi2Warning) {
			error("could not initialize model; failed FMI set debug logging");
			return NULL;
		}
	}

	fmi2Flag = fmu->setupExperiment(comp, toleranceDefined, tolerance, tStart,
			fmi2True, tEnd);
	if (fmi2Flag > fmi2Warning) {
		error("could not initialize model; failed FMI setup experiment");
		return NULL;
	}
	fmi2Flag = fmu->enterInitializationMode(comp);
	if (fmi2Flag > fmi2Warning) {
		error("could not initialize model; failed FMI enter initialization mode");
		return NULL;
	}
	printf("initialization mode entered\n");
	fmi2Flag = fmu->exitInitializationMode(comp);
	printf("successfully initialized.\n");

	if (fmi2Flag > fmi2Warning) {
		error("could not initialize model; failed FMI exit initialization mode");
		return NULL;
	}

	return comp;*/
//}

int
initializeModel (FMU * fmu, fmi2Component c, const char *fmuFileName)
{
	fmi2Status      fmi2Flag;

	FMU_WRAPPER_PRINT ("Initialization of the FMU %s.\n", fmuFileName);

	fmi2Flag = fmu->enterInitializationMode (c);
	if (fmi2Flag > fmi2Warning) {
		return error ("Could not initialize model; failed FMI enter initialization mode");
	}
	fmi2Flag = fmu->exitInitializationMode (c);
	if (fmi2Flag > fmi2Warning) {
		return error ("Could not initialize model; failed FMI exit initialization mode");
	}
	return 1;
}

/******************************************************************************
 */

int
FMU_Activate_Entrypoint (int numberOfFMUs, const char* fmuFileName[], double tEnd, double h, fmi2Boolean loggingOn, char separator,
		int nCategories, const fmi2String categories[], FMUContext * ctx)
{
	double          time;
	double          tStart = 0;   /* start time */

	const char     *guid;         /* global unique id of the fmu */
	const char     *instanceName; /* instance name */
	char           *fmuResourceLocation;  /* Dummy */

	fmi2Status      fmi2Flag;     /* return code of the fmu functions */
	fmi2Component   c;            /* instance of the fmu */
	ModelDescription *md;         /* handle to the parsed XML file */
	fmi2Real        tolerance = 0;/* used in setting up the experiment */
	fmi2Boolean     toleranceDefined = fmi2False; /* true if model description
	 * define tolerance */
	fmi2Boolean     visible = fmi2False;  /* no simulator user interface */
	fmi2CallbackFunctions callbacks = {fmuLogger, calloc, free, NULL, ctx->fmus};

	ValueStatus     vs = 0;
	Element        *defaultExp;
	FILE           *file;


	if (!(file = fopen (RESULT_FILE, "w"))) {
		printf ("Could not write %s because:\n", RESULT_FILE);
		printf ("    %s\n\n", strerror (errno));
		return 0;
	}

	/* Import FMU */
	for(int i = 0; i < numberOfFMUs; i++){

		fmuResourceLocation = malloc (strlen (dummyresource) + 2);
		strcpy (fmuResourceLocation, dummyresource);

		fmuImport (fmuFileName[i], &(ctx->fmus[i]));

		md = ctx->fmus[i].modelDescription;
		guid = getAttributeValue ((Element *) md, att_guid);

		instanceName = getAttributeValue ((Element *) getCoSimulation (md), att_modelIdentifier);



		c = ctx->fmus[i].instantiate(instanceName, fmi2CoSimulation, guid, fmuResourceLocation, &callbacks, visible, loggingOn);
		free (fmuResourceLocation);
		if (!c)
			return error ("Could not instantiate model");

		ctx->component[i] = c;


		if (nCategories > 0) {
			fmi2Flag = ctx->fmus[i].setDebugLogging (c, fmi2True, nCategories, categories);
			if (fmi2Flag > fmi2Warning)
				return error ("Could not finish instantiation; failed to set debug logging");
		}

		defaultExp = getDefaultExperiment (md);
		if (defaultExp)
			tolerance = getAttributeDouble (defaultExp, att_tolerance, &vs);
		if (vs == valueDefined)
			toleranceDefined = fmi2True;
		fmi2Flag = ctx->fmus[i].setupExperiment (c, toleranceDefined, tolerance, tStart, fmi2True, tEnd);
		if (fmi2Flag > fmi2Warning)
			return error ("Could not finish instantiation; failed FMI setup experiment");

		//initializeFMU(&(ctx->fmus[i]), visible, loggingOn, nCategories, categories, tStart, tEnd);
		initializeModel (&(ctx->fmus[i]), c, fmuFileName[i]);
	}

	outputRow_local (numberOfFMUs, fmuFileName, ctx->fmus, ctx->component, tStart, file, separator, fmi2True);   /* output column names */
	outputRow_local (numberOfFMUs, fmuFileName, ctx->fmus, ctx->component, tStart, file, separator, fmi2False);  /* output values */


	//outputRow(ctx->fmus, numberOfFMUs, fmuFileName, tStart, file, separator, fmi2True);
	//outputRow(ctx->fmus, numberOfFMUs, fmuFileName, tStart, file, separator, fmi2False);


	time = tStart;

	/* Setting up the FMU context */
	ctx->currentCommunicationPoint = time;
	ctx->communicationStepSize = h;
	ctx->noSetFMUStatePriorToCurrentPoint = fmi2True;
	ctx->resultFile = file;

	return 1;
}

/******************************************************************************
 */
void
freeContext (FMUContext ctx, int numberOfFMUs)
{
	for(int i = 0; i < numberOfFMUs; i++){
		FMU_WRAPPER_PRINT ("Release FMU %d\n\n", i+1);
		ctx.fmus[i].terminate (ctx.component[i]);
		//ctx.fmu->freeInstance (ctx.component);

		//fclose (ctx.resultFile);
		//FMU_WRAPPER_PRINT ("CSV file '%s' written\n\n", RESULT_FILE);

		dlclose (ctx.fmus[i].dllHandle);
		freeModelDescription (ctx.fmus[i].modelDescription);
	}
}


// output time and all variables in CSV format
// if separator is ',', columns are separated by ',' and '.' is used for floating-point numbers.
// otherwise, the given separator (e.g. ';' or '\t') is to separate columns, and ',' is used
// as decimal dot in floating-point numbers.
void outputRow_local(int numberOfFMUs, const char* NAMES_OF_FMUS[], FMU *fmus, fmi2Component * component, double time, FILE* file, char separator, fmi2Boolean header) {
	char buffer[32];

	// print first column
	if (header) {
		fprintf(file, "time");
	}
	else {
		if (separator==',') {
			fprintf(file, "%.17f", time);
		}
		else {
			// separator is e.g. ';' or '\t'
			doubleToCommaString_local(buffer, time);
			fprintf(file, "%s", buffer);
		}
	}

	// print all other columns
	int j = 0;
	for (j = 0; j < numberOfFMUs; j++)
	{
		int k;
		fmi2Real r;
		fmi2Integer i;
		fmi2Boolean b;
		fmi2String s;
		fmi2ValueReference vr;
		fmi2Integer hv;

		FMU *fmu = &fmus[j];
		int n = getScalarVariableSize(fmu->modelDescription);
		fmi2Component c = component[j];

		for (k = 0; k < n; k++) {
			ScalarVariable* sv = getScalarVariable(fmu->modelDescription, k);
			if (header) {
				// output names only
				if (separator == ',') {
					// treat array element, e.g. print a[1, 2] as a[1.2]
					const char* s = getAttributeValue((Element *)sv, att_name);
					fprintf(file, "%c", separator);
					fprintf(file, "%s_", NAMES_OF_FMUS[j]);
					while (*s) {
						if (*s != ' ') {
							fprintf(file, "%c", *s == ',' ? '.' : *s);
						}
						s++;
					}
				}
				else {
					fprintf(file, "%c%s", separator, getAttributeValue((Element *)sv, att_name));
				}
			}
			else {
				vr = getValueReference(sv);
				switch (getElementType(getTypeSpec(sv))) {
				case elm_Real:
					fmu->getReal(c, &vr, 1, &r);
					if (separator == ',') {
						fprintf(file, ",%.16g", r);
					} else {
						// separator is e.g. ';' or '\t'
						doubleToCommaString_local(buffer, r);
						fprintf(file, "%c%s", separator, buffer);
					}
					break;
				case elm_Integer:
				case elm_Enumeration:
					fmu->getInteger(c, &vr, 1, &i);
					fprintf(file, "%c%d", separator, i);
					break;
				case elm_Boolean:
					fmu->getBoolean(c, &vr, 1, &b);
					fprintf(file, "%c%d", separator, b);
					break;
				case elm_String:
					fmu->getString(c, &vr, 1, &s);
					fprintf(file, "%c%s", separator, s);
					break;
				default:
					fprintf(file, "%cNoValueForType=%d", separator, getElementType(getTypeSpec(sv)));
				}
			}
		} // for fmus variables
	} // for fmus

	// terminate this row
	fprintf(file, "\n");
}

void doubleToCommaString_local(char* buffer, double r){
	char* comma;
	sprintf(buffer, "%.16g", r);
	comma = strchr(buffer, '.');
	if (comma) *comma = ',';
}

