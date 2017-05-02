#ifndef __TIMER_INTERRUPT_H__
#define __TIMER_INTERRUPT_H__

#include<stdbool.h>
#include<stdint.h>

/******************************************************************************/
void setup_timer(uint32_t period, bool periodic);
/* activate a periodic timer of "period" ms */

void init_timer();

void stop_timer();

void pause();
/******************************************************************************/
#endif /* __TIMER_INTERRUPT_H__ */
