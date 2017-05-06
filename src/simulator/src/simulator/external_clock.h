/*
 * external_clock.h
 *
 *  Created on: May 6, 2017
 *      Author: jmgauthier
 */

#ifndef SIMULATOR_EXTERNAL_CLOCK_H_
#define SIMULATOR_EXTERNAL_CLOCK_H_

typedef struct{
	float startTime;
	float timeStep;
	float currentTime;
}simulator_clock;

void start_clock();

void pause_clock();

#endif /* SIMULATOR_EXTERNAL_CLOCK_H_ */
