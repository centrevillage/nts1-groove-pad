#ifndef __N1GP_MAIN_H__
#define __N1GP_MAIN_H__

#include "nts1_iface.h"

inline void delay(volatile uint32_t tick) {
  while (tick > 0) {
    --tick;
  }
}

#endif /* __N1GP_MAIN_H__ */
