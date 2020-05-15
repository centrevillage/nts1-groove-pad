#ifndef __STM_TIMER_H__
#define __STM_TIMER_H__

#include "stm32_def.h"
#include "clock.h"
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TimerEventCallback)(void);

// functions
void timer_setup();

// TODO: multi-channel timer
void timer_event_listen(TimerEventCallback cb);

// event handlears
//void SysTick_Handler();

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

void TIM2_IRQHandler();
void TIM3_IRQHandler();
void TIM14_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif /* __STM_TIMER_H__ */
