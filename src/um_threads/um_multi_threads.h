#ifndef __UM_MULTI_THREADS_H__
#define __UM_MULTI_THREADS_H__

#define MAX(a,b) (((a)>(b))?(a):(b))

#include "constants.h"
#include <ucontext.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

/******************************************************************************/
/* Thread entities                                                            */

typedef uint32_t um_thread_id;  /* id of a thread         */
typedef uint32_t stack_size_t;  /* stack size of a thread */
typedef uint32_t priority_t;    /* priority               */
typedef uint32_t core_id;

typedef enum { WAITING, READY, RUNNING } thread_state_t;

typedef struct {                /* thread control block   */
  ucontext_t     um_context;
  um_thread_id   tid;
  stack_size_t   stack_size;
  priority_t     priority;
  thread_state_t state;
  core_id				 core;
} um_thread_t;


typedef struct {
	int id;
	long mask;
} param_core;

extern um_thread_t threads[MAX_THREADS];
/* Array of threads currently configured in the program */
extern uint32_t um_thread_index;

um_thread_id um_thread_create
(void (*function)(void),  
 stack_size_t stack_size,
 priority_t priority);
/* um_thread_create: helper function to create a thread context
 * - initialize the context, 
 * - setup the new stack, 
 * - signal mask,
 * - function to execute
 */

void um_thread_yield (void);
/* um_thread_yield: relinquish CPU */

ucontext_t *get_context (um_thread_id tid);

ucontext_t *get_current_context (core_id c);
um_thread_id get_current_context_id (core_id c);

/******************************************************************************/
/* Scheduler                                                                  */

typedef um_thread_id (* scheduler_function) (void);
typedef void *(* core_function) (void *pc);

void configure_scheduler (scheduler_function s, core_function c);
void start_multi_scheduler (void);
void scheduler(core_id c);

typedef struct timespec abs_time;
void delay_until(abs_time c);
void set_timer_next();

/******************************************************************************/

#endif /* __TABLE_DRIVEN_H__ */
