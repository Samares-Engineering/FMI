#include<stdlib.h>

#include "constants.h"
#include "debug.h"
#include "um_threads.h"
#include "table_driven.h"
#include "user_code.h"
#include "user_code_mutex.h"
#include "workload.h"

/******************************************************************************/
/* Main entry point: configure a Table driven scheduler                       */

table_entry schedule_array[]  = { {0, 100}, {1, 500}, {2, 300}, {3, 700}, {4, 800}};
schedule_table my_schedule = {5, &schedule_array};

/******************************************************************************/
int main (int argc, char **argv) {
  int i;
  um_thread_id tid;

  initialize_period();                /* initialize workload simulator        */

  configure_table_driven_scheduler(&my_schedule);
  
  for (i = 0 ; i < 5 ; ++i)
  	tid = um_thread_create(user_thread, STACKSIZE, 0);

  debug_printf("%d threads create\n", tid + 1);

  start_scheduler();                 /* force a swap to the first context     */
  
  return EXIT_SUCCESS; 
}
