#include <pthread.h>

#include "debug.h"
#include "um_multi_threads.h"
#include "multi_timer_interrupt.h"
#include "multi_table_driven.h"

schedule_table *the_table;
um_thread_id current_thread;

pthread_t core_thread[MAX_CORE];

/******************************************************************************/
um_thread_id scheduler_multi_table_driven (void) {

	current_thread = (current_thread + 1) % the_table->size;
	
	table_entry var_aux = the_table->table_entries[current_thread];

	multi_setup_timer(var_aux.slot_time, false);
	
  return var_aux.a_thread;
}

void *launch_core(void *attr_) {

	param_core* attr = attr_;
	
	pthread_setaffinity_np(pthread_self(), sizeof(attr->mask), &(attr->mask));
	multi_init_timer();
	scheduler(attr->id);
	
	pthread_exit(NULL);
} 

/******************************************************************************/
void configure_multi_table_driven_scheduler (schedule_table *table) {
  configure_scheduler(scheduler_multi_table_driven, launch_core);   /* initialize the scheduler */
  
  current_thread = 0;
  the_table = table;
  
  return;
}


/******************************************************************************/
