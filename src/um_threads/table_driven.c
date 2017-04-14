#include<stdbool.h>
#include<pthread.h>

#include "debug.h"
#include "constants.h"
#include "table_driven.h"
#include "um_threads.h"
#include "timer_interrupt.h"

schedule_table *the_table;
um_thread_id current_thread;

/******************************************************************************/
um_thread_id scheduler_table_driven (void) {

	current_thread = (current_thread + 1) % the_table->size;
	
	table_entry var_aux = the_table->table_entries[current_thread];
	
	setup_timer(var_aux.slot_time, false);
	
  return var_aux.a_thread;
}

/******************************************************************************/
void configure_table_driven_scheduler (schedule_table *table) {
  configure_scheduler(scheduler_table_driven);   /* initialize the scheduler */
  init_timer();																	 /* initialize the timer 		 */	
  
  current_thread = 0;
  the_table = table;
  
  return;
}

/******************************************************************************/
