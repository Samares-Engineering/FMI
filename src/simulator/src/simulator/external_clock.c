/*
 * external_clock.c
 *
 *  Created on: May 9, 2017
 *      Author: jmgauthier
 */

#include "external_clock.h"
#include "debug.h"

simulatorClock* sclock;

void init_sclock(){
	sclock = calloc(1, sizeof(simulatorClock));
	sclock->h = 0.0;
	sclock->currentTime = 0.0;
	sclock->startTime = 0.0;
	clock_gettime(CLOCK_MONOTONIC, &(sclock->c_time));
}

void set_sclock_currentTime(float time){
	sclock->currentTime = time;
}

void set_sclock_communicationPoint(float h){
	sclock->h = h;
	//debug_printf("H clock: %f", sclock->h);
}

simulatorClock* getSClock(){
	return sclock;
}

void print_logical_clock(void){
	debug_printf("Clock: %f\n", sclock->currentTime);
}

void set_sclock_absolute_time(void){
	clock_gettime(CLOCK_MONOTONIC, &(sclock->c_time));
}

void set_sclock_startTime(float time){
	sclock->startTime = time;
}
