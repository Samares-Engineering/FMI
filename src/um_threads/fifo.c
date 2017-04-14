#include "constants.h"
#include "debug.h"
#include "fifo.h"
#include "um_threads.h"
#include "timer_interrupt.h"

/******************************************************************************/
um_thread_id scheduler_fifo (void) {
  int i;
  um_thread_id elected_thread = 0;

	while (elected_thread < um_thread_index && threads[elected_thread].state != READY)
			elected_thread++;

  for (i = elected_thread + 1 ; i < um_thread_index ; ++i)
  	if (threads[i].state == READY && threads[i].priority > threads[elected_thread].priority)
  		elected_thread = i;

  return threads[elected_thread].tid;
}

/******************************************************************************/
void configure_fifo_scheduler (void) {
  configure_scheduler(scheduler_fifo); /* initialize the scheduler            */
  init_timer();												 /* initialize the timer 		 						*/	
}

/******************************************************************************/
