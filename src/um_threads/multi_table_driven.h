#ifndef __MULTI_TABLE_DRIVEN_H__
#define __MULTI_TABLE_DRIVEN_H__

#include <stdint.h>

/******************************************************************************/
typedef struct {
  um_thread_id a_thread;
  uint32_t slot_time;
} table_entry;

typedef struct {
  uint32_t size;
  table_entry *table_entries;
} schedule_table;

void *launch_core (void *attr);

void configure_multi_table_driven_scheduler (schedule_table *table);

um_thread_id scheduler_multi_table_driven (void);

/******************************************************************************/
#endif /* __MULTI_TABLE_DRIVEN_H__ */
