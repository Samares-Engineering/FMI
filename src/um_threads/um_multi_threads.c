#include<signal.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/time.h>

#include "constants.h"
#include "debug.h"
#include "um_multi_threads.h"
#include "workload.h"
#include "multi_timer_interrupt.h"

/******************************************************************************/
um_thread_t threads[MAX_THREADS];

uint32_t um_thread_index = 0;   

int sched_current_context_id[MAX_CORE];   /* Current thread executing               */
ucontext_t *sched_context[MAX_CORE];      /* a pointer to the running thread        */

scheduler_function the_scheduler;

core_function the_core_function;
pthread_mutex_t m_scheduler;
pthread_t core_thread[MAX_CORE];

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
  makecontext(&threads[um_thread_index].um_context, function, 1, &(threads[um_thread_index].tid));
  
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
ucontext_t *get_current_context (core_id c) {
  return sched_context[c];
}

/******************************************************************************/
um_thread_id get_current_context_id (core_id c) {
  return sched_current_context_id[c];
}

/******************************************************************************/
void start_multi_scheduler (void) {

	int i;
	param_core aux[MAX_CORE];
	
	for (i = 0 ; i < MAX_CORE ; ++i) {
  	sched_current_context_id[i] = i;
  	sched_context[i] = get_context(sched_current_context_id[i]);
  	debug_printf("Starting scheduler @ %p\n", sched_context);
  	aux[i].id = i;
  	aux[i].mask = 1 << i;
  	pthread_create(core_thread + i, NULL, the_core_function, aux + i);
  }  
  
  for (i = 0 ; i < MAX_CORE ; i++)
  	pthread_join(core_thread[i], NULL);
}

/******************************************************************************/
/* The scheduling algorithm; selects the next context to run, then starts it. */

void scheduler(core_id c) {

  um_thread_id previous = sched_current_context_id[c];
  
	threads[previous].state = READY;
	
	pthread_mutex_lock(&m_scheduler);
  sched_current_context_id[c] = the_scheduler ();
  pthread_mutex_unlock(&m_scheduler);
  
  
  sched_context[c] = get_context (sched_current_context_id[c]);
  threads[sched_current_context_id[c]].state = RUNNING;
	
  print_timestamp();
  debug_printf("Core %d : Swithching from %d to %d\n", 
	       c, previous, sched_current_context_id[c]);
  
  setcontext(sched_context[c]); /* go */
}

/******************************************************************************/
void um_thread_yield (void) {
}

/******************************************************************************/
void configure_scheduler (scheduler_function s, core_function c) {

	pthread_mutex_init(&m_scheduler, NULL);

  the_scheduler = s;
  the_core_function = c;
}
