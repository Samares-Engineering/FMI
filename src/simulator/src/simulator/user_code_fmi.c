/*
 * user_code_fmi.c
 *
 *  Created on: May 9, 2017
 *      Author: jmgauthier
 */

#include <stdlib.h>
#include <signal.h>

#include "debug.h"
#include "workload.h"
#include "constants.h"
#include "user_code_fmi.h"
#include "um_threads.h"
#include "external_clock.h"

abs_time shift(int second, long nanosecond) {
	abs_time c_time;
	clock_gettime(CLOCK_MONOTONIC, &c_time);

	long aux = c_time.tv_nsec + nanosecond;

	c_time.tv_sec += second + aux/1000000000L;
	c_time.tv_nsec = aux % 1000000000L;
	debug_printf("Second : %ld, ", c_time.tv_sec);
	debug_printf("Nanosecond : %ld \n", c_time.tv_nsec);
	return c_time;
}

void user_thread_fmi(int h) {
	int i = 0;

	um_thread_id my_id = get_current_context_id();

	debug_printf ("Starting thread %d\n", my_id);

	while (1) {
		if(getSClock()->currentTime != -1.0){
			debug_printf("Clock: %f\n", getSClock()->currentTime);
			for (i = 0; i< 5; i++) {
				debug_printf ("* %d\n", my_id);
				compute_during_n_times_100ms (1);
				getSClock()->currentTime += 0.1;
			}
		}
		if(getSClock()->currentTime >= getSClock()->startTime + getSClock()->h){
				getSClock()->currentTime = -1.0;
				delay_until(shift(10, 0L));
				kill((int) getpid(), SIGUSR1);
		}
	}
}

