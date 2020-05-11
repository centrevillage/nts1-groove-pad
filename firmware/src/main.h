#ifndef __N1GP_MAIN_H__
#define __N1GP_MAIN_H__

#include "nts1_iface.h"
//#include "stm32_def.h"
#include "stm32f0xx.h"
#include "debug.h"

inline void delay(volatile uint32_t tick) {
  while (tick > 0) {
    --tick;
  }
}

#endif /* __N1GP_MAIN_H__ */
