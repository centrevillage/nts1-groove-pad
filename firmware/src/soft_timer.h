#ifndef __STM_SOFT_TIMER_H
#define __STM_SOFT_TIMER_H

#include "main.h"

#define MAX_TIMER_SIZE 2

typedef void (*TimerCallback)(void);

typedef struct {
  uint8_t active;
  TimerCallback callback;
  uint32_t msec;
  uint32_t interval;
  uint32_t interval_adjust_msec;
} TimerInfo;

extern volatile TimerInfo timer_infos[MAX_TIMER_SIZE];

void soft_timer_start(uint8_t timer_idx, uint32_t interval, TimerCallback callback);
void soft_timer_stop(uint8_t timer_idx);
void soft_timer_process();
void soft_timer_setup();

#endif /* __STM_SOFT_TIMER_H */
