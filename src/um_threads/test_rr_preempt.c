#include<stdlib.h>

#include "constants.h"
#include "debug.h"
#include "um_threads.h"
#include "rr.h"
#include "user_code.h"
#include "workload.h"

/******************************************************************************/
/* Main entry point: configure a preemptive round-robin scheduler             */

int main (int argc, char **argv) {
  int i;
  um_thread_id tid;

  initialize_period();               /* initialize workload simulator         */
  configure_rr_scheduler(500);       /* configure round robin scheduler       */

  for (i = 0 ; i < 10 ; ++i)
  	tid = um_thread_create(user_thread, STACKSIZE, 0);

  debug_printf("%d threads create\n", tid + 1);

  start_scheduler();                 /* force a swap to the first context     */
  
  return EXIT_SUCCESS; 
}
