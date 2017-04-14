#ifndef __MUTEX_H__
#define __MUTEX_H__

#include<stdbool.h>

typedef struct _mutex {
	int priority;
	int previous_priority;
	bool lock; // useless in the case of iCPP
} mutex;

void mutex_init(mutex* m, int priority);

void mutex_lock(mutex* m);

void mutex_unlock(mutex* m);

#endif /* __MUTEX_H__ */
