#ifndef __N1GP_MAIN_H__
#define __N1GP_MAIN_H__

#include <string.h>
#include "nts1_iface.h"
//#include "stm32_def.h"
#include "stm32f0xx.h"
#include "stm32_pinconfig.h"
#include "debug.h"
#include "common.h"

inline void delay(volatile uint32_t tick) {
  while (tick > 0) {
    --tick;
  }
}

#define FORCE_INLINE static inline __attribute__((always_inline, optimize("Ofast"))) 

#endif /* __N1GP_MAIN_H__ */
