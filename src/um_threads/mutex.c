#include "debug.h"
#include "um_threads.h"
#include "timer_interrupt.h"
#include "mutex.h"

void mutex_init(mutex *m, int priority_) {
	m->priority = priority_;
	m->lock = false;
}

void mutex_lock(mutex *m) {	
	// Disactivate the timer 
	stop_timer();

	/*if (m->lock) {
		debug_printf("Shouldn't happen...\n");
		return;
	}

	m->lock = true;*/
	m->previous_priority = threads[get_current_context_id()].priority;
	threads[get_current_context_id()].priority = m->priority;
	
	// Reactivate the timer
	set_timer_next();
}

void mutex_unlock(mutex *m) {	
	// Disactivate the timer 
	stop_timer();

	//m->lock = false;
	threads[get_current_context_id()].priority = m->previous_priority;

	um_thread_yield();
	// Reactivate the timer is useless
}
