#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "um_threads.h"

typedef struct _wait_list {
	um_thread_id tid;
	struct _wait_list *next;
} wait_list;

typedef struct _semaphore {
	int value;
	wait_list *h_list;
	wait_list *t_list;
	int name;
} semaphore;

void semaphore_init(semaphore *s, int value, int name);

void semaphore_wait(semaphore *s);

void semaphore_post(semaphore *s);

#endif /* __SEMAPHORE_H__ */
