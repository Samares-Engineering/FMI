#include <stdlib.h>

#include "debug.h"
#include "workload.h"
#include "constants.h"
#include "user_code.h"
#include "um_threads.h"


/******************************************************************************/
/* User code to be executed by each thread                                    */

void user_thread(void) {
  int i = 0;
  
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
    for (i = 0; i< 5; i++) {
      debug_printf ("* %d\n", my_id);
      compute_during_n_times_100ms (1);
    }
  }
}

void user_thread_no_preempt(void) {
  int i = 0;
  
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
    for (i = 0; i< 5; i++) {
      debug_printf ("* %d\n", my_id);
      compute_during_n_times_100ms (1);
    }
    um_thread_yield ();
  }
}
