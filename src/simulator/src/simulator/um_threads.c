#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>

#include "constants.h"
#include "debug.h"
#include "um_threads.h"
#include "timer_interrupt.h"

#ifdef FMU_SLAVE

#include "external_clock.h"

#endif

/******************************************************************************/
um_thread_t threads[MAX_THREADS];

uint32_t um_thread_index = 0;   

int sched_current_context_id = 0;  /* Current thread executing                */
ucontext_t *sched_context;         /* a pointer to the running thread         */

scheduler_function the_scheduler;

waiting_list *w_list = NULL;



/******************************************************************************/
um_thread_id um_thread_create
(void (*function)(void), 
 stack_size_t stack_size,
 priority_t priority)
{
  void *stack;
  int err;

  err = getcontext(&(threads[um_thread_index].um_context));
  if (err < 0)
    perror("getcontext");

  if (stack_size == 0)
    threads[um_thread_index].stack_size = STACKSIZE;
  else
    threads[um_thread_index].stack_size = stack_size;

  /* Allocate memory for the thread stack */
  stack = malloc(threads[um_thread_index].stack_size);
  if (stack == NULL) {
    perror("malloc");
    exit(1);
  }

  /* Initialze the  ucontext structure:
   * - stack and stack size
   * - reset sigmask
   */
  threads[um_thread_index].um_context.uc_stack.ss_sp    = stack;
  threads[um_thread_index].um_context.uc_stack.ss_size  
    = threads[um_thread_index].stack_size;

  threads[um_thread_index].um_context.uc_stack.ss_flags = 0;
  sigemptyset(&threads[um_thread_index].um_context.uc_sigmask);
  
  /* Attach user function */
  makecontext(&threads[um_thread_index].um_context, function, 0);

  /* Update internal arrays of threads */
  threads[um_thread_index].tid = um_thread_index;
  threads[um_thread_index].priority = priority;
  threads[um_thread_index].state = READY;
  
  debug_printf("Created thread context: %p, tid %d, function %p\n", 
	 &(threads[um_thread_index].um_context), threads[um_thread_index].tid, 
	 function);

  return um_thread_index++;
}

/******************************************************************************/
ucontext_t *get_context (um_thread_id tid) {
  return &(threads[tid].um_context);
}

/******************************************************************************/
ucontext_t *get_current_context (void) {
  return sched_context;
}

/******************************************************************************/
um_thread_id get_current_context_id (void) {
  return sched_current_context_id;
}

/******************************************************************************/
void start_scheduler (void) {
  sched_current_context_id = 0;
  sched_context = get_context(sched_current_context_id);
  debug_printf("Starting scheduler @ %p\n", sched_context);
#ifdef FMU_SLAVE
  set_sclock_absolute_time();
#endif
  scheduler();
}

/******************************************************************************/
/* The scheduling algorithm; selects the next context to run, then starts it. */

void scheduler(void) {
  um_thread_id previous = sched_current_context_id;

  if (threads[sched_current_context_id].state == RUNNING) {
	  threads[sched_current_context_id].state = READY;
	  do_awake_list();
  }
  
  sched_current_context_id = the_scheduler ();
  
  sched_context = get_context (sched_current_context_id);
  threads[sched_current_context_id].state = RUNNING;  
#ifdef FMU_SLAVE
  print_timestamp();
#endif
  debug_printf("Switching from %d to %d\n",
	       previous, sched_current_context_id);
  
  setcontext(sched_context); /* go */
}

void do_awake_list(void) {
	abs_time c_time;
	waiting_list *aux;
	

	// awake all threads which needed and take them out of the waiting_list Rq : the timer resolution is 1ms so we check within this resolution
	if (w_list != NULL) {
#ifdef FMU_SLAVE
		clock_gettime(CLOCK_MONOTONIC, &c_time);

		stop_timer();
		float trigger_time = c_time.tv_sec - (w_list->t).tv_sec + (float)(c_time.tv_nsec - (w_list->t).tv_nsec) / 1000000000L;

		while(w_list != NULL && trigger_time >= 0.0 && trigger_time <= getSClock()->startTime + getSClock()->h) {
			debug_printf("----> thread %d = %f, current_abs = %f, trigger = %f, end of step = %f\n", w_list->tid, (w_list->t).tv_sec + (float)((w_list->t).tv_nsec) / 1000000000L, c_time.tv_sec + (float)(c_time.tv_nsec) / 1000000000L, trigger_time, getSClock()->startTime + getSClock()->h);

			//debug_printf("----> %d (%d.%ld)\n", w_list->tid, (int)(w_list->t).tv_sec % 1000, (long)(w_list->t).tv_nsec/CLOCKS_PER_SEC);
		  	threads[w_list->tid].state = READY;
		  	aux = w_list->next;
		  	free(w_list);
		  	w_list = aux;
		}

		// set the time for the next thread
		set_timer_next();
#else

		clock_gettime(CLOCK_MONOTONIC, &c_time);

		stop_timer();
		while(w_list != NULL && ((w_list->t).tv_sec < c_time.tv_sec || ((w_list->t).tv_sec == c_time.tv_sec && ((w_list->t).tv_nsec <= c_time.tv_nsec + 999999L)))) {
  			debug_printf("----> %d (%d.%ld)\n", w_list->tid, (int)(w_list->t).tv_sec % 1000, (long)(w_list->t).tv_nsec/CLOCKS_PER_SEC);
  			threads[w_list->tid].state = READY;
  			aux = w_list->next;
  			free(w_list);
  			w_list = aux;
  	  	}
		
		// set the time for the next thread
		set_timer_next();


#endif
	}

	return;
}

void set_timer_next() {
	abs_time c_time;

	if (w_list != NULL) {
		clock_gettime(CLOCK_MONOTONIC, &c_time);
		setup_timer((int) (((w_list->t).tv_sec - c_time.tv_sec) * 1000 + ((w_list->t).tv_nsec - c_time.tv_nsec)/1000000), false);
	}
}

/******************************************************************************/
ucontext_t yield_context;
void* yield_stack;

void um_thread_yield (void) {
	
	/* Create new scheduler context */
  getcontext(&yield_context);
  yield_context.uc_stack.ss_sp    = yield_stack;
  yield_context.uc_stack.ss_size  = STACKSIZE;
  yield_context.uc_stack.ss_flags = 0;
  sigemptyset(&yield_context.uc_sigmask);
  makecontext(&yield_context, scheduler, 0);
  
  /* Save running thread, jump to scheduler */
  swapcontext(get_current_context(), &yield_context);
}

/******************************************************************************/
void configure_scheduler (scheduler_function s) {
	yield_stack = malloc(STACKSIZE);
	the_scheduler = s;
}

/******************************************************************************/
void delay_until(abs_time n_time) {
	
	abs_time c_time;

#ifdef FMU_SLAVE
	clock_gettime(CLOCK_MONOTONIC, &c_time);
#else
	clock_gettime(CLOCK_MONOTONIC, &c_time);
#endif

	waiting_list *insert, *prec, *aux;
	
	// Check if the n_time is positive and at least 1ms
	if (n_time.tv_sec < c_time.tv_sec || (n_time.tv_sec == c_time.tv_sec && n_time.tv_nsec < c_time.tv_nsec + 1000000L))
		return;
	
	// set the thread to WAITING
	threads[sched_current_context_id].state = WAITING;
	
	// Insertion of the thread in the sorted waiting list
	aux = malloc(sizeof(waiting_list));
	aux->t = n_time;
	aux->tid = sched_current_context_id;
	
	stop_timer();
	// head insertion
	if (w_list == NULL || (w_list->t).tv_sec > n_time.tv_sec || (((w_list->t).tv_sec == n_time.tv_sec && ((w_list->t).tv_nsec > n_time.tv_nsec)))) {
		aux->next = w_list;
		w_list = aux;
	} else {
		prec = w_list;
		insert = w_list;
		while (insert != NULL && ((insert->t).tv_sec < n_time.tv_sec || ((insert->t).tv_sec == n_time.tv_sec && (insert->t).tv_nsec < n_time.tv_nsec))) {
			prec = insert;
			insert = insert->next;
			//debug_printf("loop %d, \n", sched_current_context_id);
		}		
		
		prec->next = aux;
		aux->next = insert;
	}
	set_timer_next();

	// yield the thread
	um_thread_yield ();

}
