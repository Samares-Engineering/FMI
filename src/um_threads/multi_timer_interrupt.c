#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<ucontext.h>
#include<stdio.h>

#include "constants.h"
#include "um_multi_threads.h"
#include "multi_timer_interrupt.h"

/******************************************************************************/
ucontext_t signal_context;         /* the interrupt context                   */
void *signal_stack;                /* global interrupt stack                  */

/******************************************************************************/
/* Timer interrupt handler:
 * Creates a new context to run the scheduler in, masks signals, then
 * swaps contexts saving the previously executing thread and jumping
 * to the scheduler.
 */

void multi_timer_interrupt(int j, siginfo_t *si, void *old_context)
{
	printf("%d, %p, %p\n", j, si, old_context);

  /* Create new scheduler context */
  getcontext(&signal_context);
  signal_context.uc_stack.ss_sp    = signal_stack;
  signal_context.uc_stack.ss_size  = STACKSIZE;
  signal_context.uc_stack.ss_flags = 0;
  sigemptyset(&signal_context.uc_sigmask);
  makecontext(&signal_context, scheduler, 0);
  
  /* Save running thread, jump to scheduler */
  swapcontext(get_current_context(0), &signal_context);
}

void multi_init_timer(void) {

	struct sigaction act;

	signal_stack = malloc(STACKSIZE); /* allocate the signal/interrupt stack   */
  if (signal_stack == NULL) {
    perror("malloc");
    exit(1);
  }
  
  act.sa_sigaction = multi_timer_interrupt; /* bind function to the timer           */  

  sigemptyset(&act.sa_mask); /* reset set of signals                          */
  act.sa_flags = SA_RESTART  /* interruptible functions do not raise [EINTR]  */
    | SA_SIGINFO;            /* to select particular signature signal handler */
  
  if(sigaction(SIGALRM, &act, NULL) != 0)
    perror("Signal handler");
}

/******************************************************************************/
/* Set up SIGALRM signal handler:
 * We use the SIGALRM signal to emulate a timer-based interrupt for
 * quantum-based scheduling policies.
 */

void multi_setup_timer(uint32_t period, bool periodic)
{
  struct itimerval it;

  /* setup our timer */
  it.it_value.tv_sec = period/1000;
  it.it_value.tv_usec = (period % 1000) * 1000;

  if (periodic)
    it.it_interval = it.it_value;
  else {
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;
  }

  if (setitimer(ITIMER_REAL, &it, NULL)) 
    perror("setitiimer");
}

/******************************************************************************/

void multi_stop_timer() {
	if (setitimer(ITIMER_REAL, NULL, NULL)) 
    perror("setitiimer");
}
