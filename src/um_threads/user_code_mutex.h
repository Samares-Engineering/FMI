#ifndef __USER_CODE_MUTEX_H__
#define __USER_CODE_MUTEX_H__

// Buffer type and functions
typedef struct _buffer {
	int i_p;
	int i_c;
	int *shared_data;
	int max;
} buffer;


void push(buffer* buf, int val);
int flush(buffer* buf);

// Init semaphore and mutex
void init(int m_priority, int s_value, int m_s_priority);

// Threads
void user_thread_idle(void);
void user_thread_delay_0_4(void);
void user_thread_delay_1_2(void);
void user_thread_delay_2(void);
void user_thread_delay_3_1(void);
void user_thread_delay_4(void);

// Auxiliary functions
abs_time shift(int second, long nanosecond);

/******************************************************************************/
#endif /* __USER_CODE_MUTEX_H__ */
