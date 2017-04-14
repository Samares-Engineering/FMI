#include <stdlib.h>

#include "debug.h"
#include "workload.h"
#include "mutex.h"
#include "semaphore.h"
#include "user_code_mutex.h"

// Test mutex
mutex m;

// Test semaphore
mutex m_s;
semaphore s_full, s_free;
buffer buf;


/******************************************************************************/
/* User code to be executed by each thread                                    */

void init(int m_priority, int s_value, int m_s_priority) {
	mutex_init(&m, m_priority);
	
	semaphore_init(&s_free, s_value, 1000);
	semaphore_init(&s_full, 0, 2000);
	
	buf.i_p = 0;
	buf.i_c = 0;
	buf.shared_data = malloc(s_value * sizeof(int));
	buf.max = s_value;
}

void user_thread_delay_1_2(void) {
  int i = 0;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
  	mutex_lock(&m);
    for (i = 0; i< 5; i++) {
      compute_during_n_times_100ms (1);
      debug_printf ("* %d section critique\n", my_id);
    }
    mutex_unlock(&m);
    delay_until(shift(1, 200000000L));
  }
}

void user_thread_delay_4(void) {
  int i = 0;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
  	mutex_lock(&m);
    for (i = 0; i< 3; i++) {
      compute_during_n_times_100ms (1);
      debug_printf ("* %d section critique\n", my_id);
    }
    mutex_unlock(&m);
    
    compute_during_n_times_100ms (1);
    debug_printf ("* %d\n", my_id);
    compute_during_n_times_100ms (1);
    debug_printf ("* %d\n", my_id);
    
    delay_until(shift(4, 0L));
  }
}

void user_thread_delay_3_1(void) {
  int i = 0;
  int aux = -1;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
  	semaphore_wait(&s_full);
  	mutex_lock(&m_s);
  	aux = flush(&buf);
  	debug_printf ("* %d consumed %d\n", my_id, aux);
  	mutex_unlock(&m_s);
    semaphore_post(&s_free);
  	 	
    for (i = 0; i< 4; i++) {
      compute_during_n_times_100ms (1);
      debug_printf ("* %d\n", my_id);
    }
    aux = -1;
    delay_until(shift(3, 100000000L));
  }
}

void user_thread_idle(void) {
  int i = 0;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
    for (i = 0; i< 5; i++) {
      compute_during_n_times_100ms (1);
      debug_printf ("* %d\n", my_id);
    }
  }
}

void user_thread_delay_0_4(void) {
  int i = 0;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {
    for (i = 0; i< 2; i++) {
    	compute_during_n_times_100ms (1);
      debug_printf ("* %d\n", my_id);
    }
    delay_until(shift(0, 400000000L));
  }
}

void user_thread_delay_2(void) {
  int i = 0;
  int k = 0;
  um_thread_id my_id = get_current_context_id();

  debug_printf ("Starting thread %d\n", my_id);

  while (1) {  	
    for (i = 0; i< 2; i++) {
    	compute_during_n_times_100ms (1);
      debug_printf ("* %d\n", my_id);
    }

    semaphore_wait(&s_free);
    mutex_lock(&m_s);
  	push(&buf, k);
  	debug_printf ("* %d produced %d\n", my_id, k++);
  	mutex_unlock(&m_s);
  	semaphore_post(&s_full);
  	
    delay_until(shift(2, 0L));
  }
}

abs_time shift(int second, long nanosecond) {
	abs_time c_time;
	clock_gettime(CLOCK_MONOTONIC, &c_time);
	
	long aux = c_time.tv_nsec + nanosecond;
	
	c_time.tv_sec += second + aux/1000000000L;
	c_time.tv_nsec = aux % 1000000000L;
	
	return c_time;
}

void push(buffer* buf, int val) {
	(buf->shared_data)[buf->i_p] = val;
	buf->i_p = (buf->i_p + 1) % buf->max;
}

int flush(buffer* buf) {
	int aux;
	
	aux = (buf->shared_data)[buf->i_c];
	buf->i_c = (buf->i_c + 1) % buf->max;
	
	return aux;
}
