#ifndef __TIMER_INTERRUPT_H__
#define __TIMER_INTERRUPT_H__

#include<stdbool.h>
#include<stdint.h>

/******************************************************************************/
void multi_setup_timer(uint32_t period, bool periodic);
/* activate a periodic timer of "period" ms */

void multi_init_timer();

void multi_stop_timer();
/******************************************************************************/
#endif /* __TIMER_INTERRUPT_H__ */
