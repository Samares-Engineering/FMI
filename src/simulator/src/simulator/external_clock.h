/*
 * external_clock.h
 *
 *  Created on: May 6, 2017
 *      Author: jmgauthier
 */

#ifndef SIMULATOR_EXTERNAL_CLOCK_H_
#define SIMULATOR_EXTERNAL_CLOCK_H_

#include "um_threads.h"

typedef struct _simulatorClock{
	float h;
	float currentTime;
	float startTime;
	abs_time c_time;
}simulatorClock;

void init_sclock();
void set_sclock_communicationPoint(float h);
simulatorClock* getSClock();
void set_sclock_currentTime(float time);

void print_logical_clock(void);
void set_sclock_absolute_time(void);
void set_sclock_startTime(float time);

#endif /* SIMULATOR_EXTERNAL_CLOCK_H_ */
