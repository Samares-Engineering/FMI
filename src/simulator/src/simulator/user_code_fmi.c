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

abs_time shift(unsigned long ms) {
	abs_time c_time;
	clock_gettime(CLOCK_MONOTONIC, &c_time);
	c_time.tv_sec = ms / 1000;
	c_time.tv_nsec = (ms % 1000) * 1000000;
	return c_time;
}

void user_thread_fmi() {
	int i = 0;
	//abs_time c_time;

	um_thread_id my_id = get_current_context_id();
	debug_printf ("Starting thread %d\n", my_id);

	while (1) {
		/*for (i = 0; i< 5; i++) {

			debug_printf ("* %d\n", my_id);
			//debug_printf ("Increment clock and launch scheduler %d\n", my_id);
			//kill((int) getpid(), SIGUSR1);
			//print_logical_clock();

			compute_during_n_times_100ms (1);

			//kill((int) getpid(), SIGUSR2);
		}
		//kill((int) getpid(), SIGUSR1);
		um_thread_yield ();*/


		delay_until(shift(10000));
		printf("o<\n");
	}
}

/*void user_thread_fmi_2() {
	abs_time c_time;

	int i = 0;

	um_thread_id my_id = get_current_context_id();

	while (1) {
		for(i = 0; i<3; ++i){
			debug_printf ("Do Something %d\n", my_id);
			compute_during_n_times_100ms (2);
			kill((int) getpid(), SIGUSR1);
			print_logical_clock();
		}

		delay_until(shift(10, 0L));
	}

}

void user_thread_fmi_3() {
	abs_time c_time;

	int i = 0;

	um_thread_id my_id = get_current_context_id();

	//delay_until(shift(3, 400000000L));

	while (1) {
		for(i = 0; i<3; ++i){
			debug_printf ("Do Something %d\n", my_id);
			compute_during_n_times_100ms (2);
			kill((int) getpid(), SIGUSR1);
			print_logical_clock();
		}

		delay_until(shift(2, 0L));
	}

}*/
