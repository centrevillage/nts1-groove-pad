#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#ifdef USE_ARDUINO
#include "clock.h"
#endif

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void systick_timer_setup();

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

#endif /* SYSTICK_TIMER_H */
