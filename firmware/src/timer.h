#ifndef __STM_TIMER_H__
#define __STM_TIMER_H__

#include "stm32_def.h"
#include "clock.h"
#include "common.h"
#include "timer_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// functions
void timer_simple_setup(uint8_t timer_idx, uint16_t prescale, uint32_t period);
void timer_start(uint8_t timer_idx);

// variables
//extern volatile uint32_t _current_msec;
FORCE_INLINE uint32_t current_msec() {
  //return _current_msec;
  return getCurrentMillis();
}

FORCE_INLINE void delay_msec(uint32_t msec) {
  __IO uint32_t base = current_msec();
  while((current_msec() - base) < msec) {
  }
}

#ifdef __cplusplus
}
#endif

#endif /* __STM_TIMER_H__ */
