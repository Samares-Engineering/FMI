#include <stdlib.h>

#include "constants.h"
#include "timer_interrupt.h"
#include "debug.h"
#include "semaphore.h"

void semaphore_init(semaphore *s, int value_, int name_) {
	s->value = value_;
	s->h_list = malloc(sizeof(wait_list));
	s->t_list = s->h_list;
	(s->t_list)->tid = MAX_THREADS;
	(s->t_list)->next = NULL;
	(s->name) = name_;
}

void semaphore_wait(semaphore *s) {
	stop_timer();

	if (s->value == 0) {
		(s->t_list)->tid = get_current_context_id();
		threads[(s->t_list)->tid].state = WAITING;
		debug_printf("<--- %d waits semaphore %d\n", (s->t_list)->tid, s->name);
		(s->t_list)->next = malloc(sizeof(wait_list));
		s->t_list = (s->t_list)->next;
		(s->t_list)->tid = MAX_THREADS;
		(s->t_list)->next = NULL;
		
		set_timer_next();
		um_thread_yield();
	} else {
		s->value--;
		set_timer_next();
	}
}

void semaphore_post(semaphore *s) {
	wait_list *aux;
	
	stop_timer();
	
	if (((s->h_list)->tid) < MAX_THREADS) {
		threads[(s->h_list)->tid].state = READY;
		debug_printf("---> %d gets semaphore %d\n", (s->h_list)->tid, s->name);
		aux = (s->h_list)->next;
		free(s->h_list);
		s->h_list = aux;
		
		set_timer_next();
		um_thread_yield();
	} else {
		s->value++;
		set_timer_next();
	}
}

void print_list(semaphore *s) {
	wait_list *aux = s->h_list;
	
	
	debug_printf("%d waiting list : ", s->name);
	while (aux != NULL) {
	 debug_printf("%d ", aux->tid);
	 aux = aux->next;
	}
	debug_printf("\n");
}
