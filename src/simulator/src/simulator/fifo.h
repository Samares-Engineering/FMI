/* This file defines a FIFO within priority scheduler to be integrated
 * to the um_threads library
 */

#ifndef __FIFO_H__
#define __FIFO_H__

#include "um_threads.h"

/******************************************************************************/
void configure_fifo_scheduler (void);
/* Configure the FIFO within priority scheduler, 
 * Only one thread by priority.
 */

um_thread_id scheduler_fifo (void);
/* FIFO within priority scheduling policy.
 */

/******************************************************************************/
#endif /* __FIFO_H__ */
