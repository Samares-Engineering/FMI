/*
 * external_clock.h
 *
 *  Created on: May 6, 2017
 *      Author: jmgauthier
 */

#ifndef SIMULATOR_EXTERNAL_CLOCK_H_
#define SIMULATOR_EXTERNAL_CLOCK_H_

typedef struct _simulatorClock{
	float startTime;
	float h;
	float currentTime;
}simulatorClock;

void initClock();
void setClockCommunicationPoint(float h);
void setClockStartTime(float startTime);
simulatorClock* getSClock();

#endif /* SIMULATOR_EXTERNAL_CLOCK_H_ */
