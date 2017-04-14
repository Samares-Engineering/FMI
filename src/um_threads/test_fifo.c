#include<stdlib.h>

#include "constants.h"
#include "debug.h"
#include "um_threads.h"
#include "fifo.h"
#include "user_code_mutex.h"
#include "workload.h"

#define PRIORITY_idle 0
#define PRIORITY_4 10
#define PRIORITY_3_1 20
#define PRIORITY_2 35
#define PRIORITY_1_2 30
#define PRIORITY_0_4 40

#define TEST_MUTEX 1
#define TEST_SEMAPHORE 0

#define BUFFER_LENGTH 2

/******************************************************************************/
/* Main entry point: configure a FIFO within priority scheduler               */

int main (int argc, char **argv) {

  um_thread_id tid;

  initialize_period();               /* initialize workload simulator         */
	configure_fifo_scheduler();
	
	init(MAX(PRIORITY_4, PRIORITY_1_2) + 1, BUFFER_LENGTH, MAX(PRIORITY_2, PRIORITY_3_1) + 1);
	 
	/* Before the question 5, only the thread of higher priority was running. */
	/* It was because every thread were ReADY, so the lower priority were mask by the higher. */
  tid = um_thread_create(user_thread_idle, STACKSIZE, PRIORITY_idle);

  tid = um_thread_create(user_thread_delay_0_4, STACKSIZE, PRIORITY_0_4);
  
  #if TEST_MUTEX == 1
  	  tid = um_thread_create(user_thread_delay_1_2, STACKSIZE, PRIORITY_1_2);
  	  tid = um_thread_create(user_thread_delay_4, STACKSIZE, PRIORITY_4);
  #endif
  
  #if TEST_SEMAPHORE == 1 // Producteur limitant
  		// Consommateur
  	  tid = um_thread_create(user_thread_delay_3_1, STACKSIZE, PRIORITY_3_1);
  	  tid = um_thread_create(user_thread_delay_3_1, STACKSIZE, PRIORITY_3_1 + 1);
  	  tid = um_thread_create(user_thread_delay_3_1, STACKSIZE, PRIORITY_3_1 + 2);
  	  // Producteur
  	  tid = um_thread_create(user_thread_delay_2, STACKSIZE, PRIORITY_2);
	#endif
	
	#if TEST_SEMAPHORE == 2 // Consommateur limitant
  		// Consommateur
  	  tid = um_thread_create(user_thread_delay_3_1, STACKSIZE, PRIORITY_3_1);
  	  // Producteur
  	  tid = um_thread_create(user_thread_delay_2, STACKSIZE, PRIORITY_2);
  	  tid = um_thread_create(user_thread_delay_2, STACKSIZE, PRIORITY_2 + 1);
  	  tid = um_thread_create(user_thread_delay_2, STACKSIZE, PRIORITY_2 + 2);
	#endif
  
  debug_printf("%d threads create\n", tid + 1);

  start_scheduler();                 /* force a swap to the first context     */
  
  return EXIT_SUCCESS; 
}
