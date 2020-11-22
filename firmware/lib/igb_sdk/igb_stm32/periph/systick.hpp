#ifndef IGB_STM32_PERIPH_SYSTICK_H
#define IGB_STM32_PERIPH_SYSTICK_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_util/macro.hpp>

namespace igb {
namespace stm32 {

enum class SystickTimerInterval : uint32_t {
  msec = 1000UL,
  _100usec = 10000UL,
  _10usec = 100000UL,
  usec = 1000000UL,
};

struct SystickCtrl {
  struct State {
    uint32_t tick = 0;
    uint32_t interval = 0;
    uint32_t _msec_scaling = 1;
    uint32_t _usec_scaling = 1000;
  };

  static State state;

  static IGB_FAST_INLINE void setTimerInterval(uint32_t interval_) {
    state.interval = interval_;
    state._msec_scaling = (uint32_t)(((float)(SystemCoreClock) / 1000.0f) / (float)state.interval);
    state._usec_scaling = (uint32_t)(((float)(SystemCoreClock) / 1000000.0f) / (float)state.interval);
    if (SysTick_Config(state.interval)) {
      /* Capture error */ 
      while (1);
    }
  }
  static IGB_FAST_INLINE void setTimerInterval(SystickTimerInterval interval_) {
    setTimerInterval(SystemCoreClock / static_cast<uint32_t>(interval_));
  }
  static IGB_FAST_INLINE uint32_t getCurrentTick() {
    return state.tick;
  }
  static IGB_FAST_INLINE uint32_t getCurrentMilliSec() {
    return state.tick * state._msec_scaling;
  }
  static IGB_FAST_INLINE uint32_t getCurrentMicroSec() {
    return state.tick * state._usec_scaling;
  }
};

}
}

extern "C" {

// if you use systick callback, please define USER_SYSTICK_HANDLER_CALLBACK macro in "igb_stm32_user_conf.h"
#ifndef USER_SYSTICK_HANDLER_CALLBACK
#define USER_SYSTICK_HANDLER_CALLBACK while(0){}
#endif

#ifdef USE_ARDUINO

#include "clock.h"
static IGB_FAST_INLINE uint32_t current_msec() {
  return getCurrentMillis();
}

static IGB_FAST_INLINE uint32_t current_usec() {
  return getCurrentMicros();
}

#else

volatile uint32_t _systick = 0;
void SysTick_Handler(void) {
  _systick++;
  USER_SYSTICK_HANDLER_CALLBACK;
}

static IGB_FAST_INLINE uint32_t current_msec() {
  return igb::stm32::SystickCtrl::getCurrentMilliSec();
}

static IGB_FAST_INLINE uint32_t current_usec() {
  return igb::stm32::SystickCtrl::getCurrentMicroSec();
}

#endif /* USE_ARDUINO */

static IGB_FAST_INLINE void delay_msec(uint32_t msec) {
  __IO uint32_t base = current_msec();
  while((current_msec() - base) < msec) {
  }
}

}

#endif /* IGB_STM32_PERIPH_SYSTICK_H */
