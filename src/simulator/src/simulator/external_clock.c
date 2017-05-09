/*
 * external_clock.c
 *
 *  Created on: May 9, 2017
 *      Author: jmgauthier
 */

#include "external_clock.h"

simulatorClock* sclock;

void initClock(){
	sclock = calloc(1, sizeof(simulatorClock));
	sclock->startTime=0.0;
	sclock->h = 0.0;
	sclock->currentTime = 0.0;
}

void setClockCommunicationPoint(float h){
	sclock->h = h;
	//debug_printf("H clock: %f", sclock->h);
}

void setClockStartTime(float startTime){
	sclock->startTime = startTime;
}

simulatorClock* getSClock(){
	return sclock;
}
