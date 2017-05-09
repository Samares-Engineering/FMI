#ifndef __TIMER_INTERRUPT_H__
#define __TIMER_INTERRUPT_H__

#include<stdbool.h>
#include<stdint.h>

/******************************************************************************/
void setup_timer(uint32_t period, bool periodic);
/* activate a periodic timer of "period" ms */

void setup_timer_2(float ccp);

void init_timer();

void stop_timer();

void stop_scheduler();

/******************************************************************************/
#endif /* __TIMER_INTERRUPT_H__ */
