#ifndef __STM_TIMER_H__
#define __STM_TIMER_H__

#ifdef USE_ARDUINO
#include "clock.h"
#endif

#include "main.h"
#include "common.h"

#include "timer_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// functions
void timer_simple_setup(uint8_t timer_idx, uint16_t prescale, uint32_t period, uint16_t priority);
void timer_start(uint8_t timer_idx);
#ifndef USE_ARDUINO
void systick_setup();
#endif

// variables
#ifndef USE_ARDUINO
extern volatile uint32_t _current_msec;
#endif
FORCE_INLINE uint32_t current_msec() {
#ifdef USE_ARDUINO
  return getCurrentMillis();
#else
  return _current_msec;
#endif
}

FORCE_INLINE void delay_msec(uint32_t msec) {
  __IO uint32_t base = current_msec();
  while((current_msec() - base) < msec) {
  }
}

#ifndef USE_ARDUINO
void SysTick_Handler(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM_TIMER_H__ */
