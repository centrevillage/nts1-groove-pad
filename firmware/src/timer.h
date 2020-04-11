#ifndef __STM_TIMER_H__
#define __STM_TIMER_H__

#include "stm32_def.h"
#include "clock.h"

#ifdef __cplusplus
extern "C" {
#endif

// functions
void timer_setup();

// event handlears
//void SysTick_Handler();

// variables
//extern volatile uint32_t _current_msec;
inline uint32_t current_msec() {
  //return _current_msec;
  return getCurrentMillis();
}

inline void delay_msec(uint32_t msec) {
  uint32_t base = current_msec();
  while((current_msec() - base) < msec) {
  }
}

#ifdef __cplusplus
}
#endif

#endif /* __STM_TIMER_H__ */
