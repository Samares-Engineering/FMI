#include "constants.h"
#include "rr.h"
#include "um_threads.h"
#include "timer_interrupt.h"
#include "debug.h"

/******************************************************************************/
um_thread_id scheduler_rr (void) {
  return (get_current_context_id() + 1) % MAX_THREADS;
}

/******************************************************************************/
void configure_rr_scheduler (uint32_t period) {
  configure_scheduler(scheduler_rr);  /* initialize the scheduler */
  init_timer();			/* initialize the timer */

  if (period > 0)
  	setup_timer(period, true);
  
  return;
}

void configure_rr_scheduler_2 (float ccp) {
  configure_scheduler(scheduler_rr);  /* initialize the scheduler */
  init_timer();			/* initialize the timer */

  if (ccp > 0)
  	setup_timer_2(ccp);

  return;
}

/******************************************************************************/
