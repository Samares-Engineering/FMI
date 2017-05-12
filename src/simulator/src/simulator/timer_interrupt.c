#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<ucontext.h>
#include<stdio.h>

#include "constants.h"
#include "um_threads.h"
#include "debug.h"
#include "timer_interrupt.h"
#include "external_clock.h"

/******************************************************************************/
ucontext_t signal_context;         /* the interrupt context                   */
void *signal_stack;                /* global interrupt stack                  */
struct sigaction act;

#ifdef FMU_SLAVE
struct sigaction act2;
struct sigaction act3;
#endif

/******************************************************************************/
/* Timer interrupt handler:
 * Creates a new context to run the scheduler in, masks signals, then
 * swaps contexts saving the previously executing thread and jumping
 * to the scheduler.
 */

void timer_interrupt(int j, siginfo_t *si, void *old_context)
{
	abs_time c_time;

	clock_gettime(CLOCK_MONOTONIC, &c_time);
	debug_printf("Timer tilt : %d.%ld\n", (int)c_time.tv_sec % 1000, (long)c_time.tv_nsec/CLOCKS_PER_SEC);
	/* Create new scheduler context */
	getcontext(&signal_context);
	signal_context.uc_stack.ss_sp    = signal_stack;
	signal_context.uc_stack.ss_size  = STACKSIZE;
    signal_context.uc_stack.ss_flags = 0;
    sigemptyset(&signal_context.uc_sigmask);
    makecontext(&signal_context, scheduler, 0);
  
    /* Save running thread, jump to scheduler */
    swapcontext(get_current_context(), &signal_context);
}

#ifdef FMU_SLAVE
void set_sclockTime(){

	/*this simulates real time but is not simulated time*/
	abs_time c_time;
	clock_gettime(CLOCK_MONOTONIC, &c_time);

	getSClock()->currentTime += c_time.tv_sec - getSClock()->c_time.tv_sec + (float)(c_time.tv_nsec - getSClock()->c_time.tv_nsec) / 1000000000L;
	set_sclock_absolute_time();
}

void launch_scheduler(){
	scheduler();
}
#endif

void init_timer(void) {

	signal_stack = malloc(STACKSIZE); /* allocate the signal/interrupt stack   */
	if (signal_stack == NULL) {
		perror("malloc");
		exit(1);
	}
  
 	act.sa_sigaction = timer_interrupt; /* bind function to the timer           */
#ifdef FMU_SLAVE
 	act2.sa_sigaction = set_sclockTime;
 	act3.sa_sigaction = launch_scheduler;
#endif
}

/******************************************************************************/
/* Set up SIGALRM signal handler:
 * We use the SIGALRM signal to emulate a timer-based interrupt for
 * quantum-based scheduling policies.
 */

void setup_timer(uint32_t period, bool periodic)
{
  
  sigemptyset(&act.sa_mask); /* reset set of signals                          */
  act.sa_flags = SA_RESTART  /* interruptible functions do not raise [EINTR]  */
    | SA_SIGINFO;            /* to select particular signature signal handler */

#ifdef FMU_SLAVE
  if(sigaction(SIGUSR1, &act2, NULL) != 0)
        perror("Signal handler");
  if(sigaction(SIGUSR2, &act3, NULL) != 0)
          perror("Signal handler");

#else
  struct itimerval it;
  if(sigaction(SIGALRM, &act, NULL) != 0)
          perror("Signal handler");
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
#endif

}

/******************************************************************************/

void stop_timer() {

	if (setitimer(ITIMER_REAL, NULL, NULL)) 
		perror("setitiimer");
}
