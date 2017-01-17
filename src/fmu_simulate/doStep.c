/* ---------------------------------------------------------------------------*
 * fmuTemplate.c
 * Implementation of the FMI interface based on functions and macros to
 * be defined by the includer of this file. 
 * If FMI_COSIMULATION is defined, this implements "FMI for Co-Simulation 2.0",
 * otherwise "FMI for Model Exchange 2.0".
 * The "FMI for Co-Simulation 2.0", implementation assumes that exactly the
 * following capability flags are set to fmi2True:
 *    canHandleVariableCommunicationStepSize, i.e. fmi2DoStep step size can vary
 * and all other capability flags are set to default, i.e. to fmi2False or 0.
 *
 * Revision history
 *  07.03.2014 initial version released in FMU SDK 2.0.0
 *  02.04.2014 allow modules to request termination of simulation, better time
 *             event handling, initialize() moved from fmi2EnterInitialization to
 *             fmi2ExitInitialization, correct logging message format in fmi2DoStep.
 *  10.04.2014 use FMI 2.0 headers that prefix function and types names with 'fmi2'.
 *  13.06.2014 when fmi2setDebugLogging is called with 0 categories, set all
 *             categories to loggingOn value.
 *  09.07.2014 track all states of Model-exchange and Co-simulation and check
 *             the allowed calling sequences, explicit isTimeEvent parameter for
 *             eventUpdate function of the model, lazy computation of computed values.
 *
 * Author: Adrian Tirea
 * Copyright QTronic GmbH. All rights reserved.
 * ---------------------------------------------------------------------------*/

// macro to be used to log messages. The macro check if current 
// log category is valid and, if true, call the logger provided by simulator.
#define FILTERED_LOG(instance, status, categoryIndex, message, ...) if (isCategoryLogged(instance, categoryIndex)) \
        instance->functions->logger(instance->functions->componentEnvironment, instance->instanceName, status, \
        logCategoriesNames[categoryIndex], message, ##__VA_ARGS__);

static fmi2String logCategoriesNames[] = {"logAll", "logError", "logFmiCall", "logEvent"};

// array of value references of states
#if NUMBER_OF_REALS>0
fmi2ValueReference vrStates[NUMBER_OF_STATES] = STATES;
#endif

#ifndef max
#define max(a,b) ((a)>(b) ? (a) : (b))
#endif

static fmi2Boolean invalidState(ModelInstance *comp, const char *f, int statesExpected) {
    if (!comp)
        return fmi2True;
    if (!(comp->state & statesExpected)) {
        comp->state = modelError;
        FILTERED_LOG(comp, fmi2Error, LOG_ERROR, "%s: Illegal call sequence.", f)
        return fmi2True;
    }
    return fmi2False;
}

fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint,
                    fmi2Real communicationStepSize, fmi2Boolean noSetFMUStatePriorToCurrentPoint) {
    ModelInstance *comp = (ModelInstance *)c;
    double h = communicationStepSize / 10;
    int k;
#if NUMBER_OF_EVENT_INDICATORS>0 || NUMBER_OF_REALS>0 
    int i;
#endif
    const int n = 10; // how many Euler steps to perform for one do step
#if NUMBER_OF_REALS>0 
    //double prevState[max(NUMBER_OF_STATES, 1)];
#endif
#if NUMBER_OF_EVENT_INDICATORS>0
    double prevEventIndicators[max(NUMBER_OF_EVENT_INDICATORS, 1)];
#endif
    int stateEvent = 0;
    int timeEvent = 0;

    if (invalidState(comp, "fmi2DoStep", MASK_fmi2DoStep))
        return fmi2Error;

    FILTERED_LOG(comp, fmi2OK, LOG_FMI_CALL, "fmi2DoStep: "
        "currentCommunicationPoint = %g, "
        "communicationStepSize = %g, "
        "noSetFMUStatePriorToCurrentPoint = fmi2%s",
        currentCommunicationPoint, communicationStepSize, noSetFMUStatePriorToCurrentPoint ? "True" : "False")

    if (communicationStepSize <= 0) {
        FILTERED_LOG(comp, fmi2Error, LOG_ERROR,
            "fmi2DoStep: communication step size must be > 0. Fount %g.", communicationStepSize)
        comp->state = modelError;
        return fmi2Error;
    }

#if NUMBER_OF_EVENT_INDICATORS>0
    // initialize previous event indicators with current values
    for (i = 0; i < NUMBER_OF_EVENT_INDICATORS; i++) {
        prevEventIndicators[i] = getEventIndicator(comp, i);
    }
#endif

    // break the step into n steps and do forward Euler.
    comp->time = currentCommunicationPoint;
    for (k = 0; k < n; k++) {
        comp->time += h;

#if NUMBER_OF_REALS>0
        //for (i = 0; i < NUMBER_OF_STATES; i++) {
        //    prevState[i] = r(vrStates[i]);
        //}
        for (i = 0; i < NUMBER_OF_STATES; i++) {
            fmi2ValueReference vr = vrStates[i];
            r(vr) += h * getReal(comp, vr + 1); // forward Euler step
        }
#endif

#if NUMBER_OF_EVENT_INDICATORS>0
        // check for state event
        for (i = 0; i < NUMBER_OF_EVENT_INDICATORS; i++) {
            double ei = getEventIndicator(comp, i);
            if (ei * prevEventIndicators[i] < 0) {
                FILTERED_LOG(comp, fmi2OK, LOG_EVENT,
                    "fmi2DoStep: state event at %g, z%d crosses zero -%c-", comp->time, i, ei < 0 ? '\\' : '/')
                stateEvent++;
            }
            prevEventIndicators[i] = ei;
        }
#endif
        // check for time event
        if (comp->eventInfo.nextEventTimeDefined && ((comp->time - comp->eventInfo.nextEventTime) > -0.0000000001)) {
            FILTERED_LOG(comp, fmi2OK, LOG_EVENT, "fmi2DoStep: time event detected at %g", comp->time)
            timeEvent = 1;
        }

        if (stateEvent || timeEvent) {
            eventUpdate(comp, &comp->eventInfo, timeEvent);
            timeEvent = 0;
            stateEvent = 0;
        }

        // terminate simulation, if requested by the model in the previous step
        if (comp->eventInfo.terminateSimulation) {
            FILTERED_LOG(comp, fmi2Discard, LOG_ALL, "fmi2DoStep: model requested termination at t=%g", comp->time)
            comp->state = modelStepFailed;
            return fmi2Discard; // enforce termination of the simulation loop
        }
    }
    return fmi2OK;
}
