#ifndef IGB_STM32_PERIPH_RCC_H
#define IGB_STM32_PERIPH_RCC_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>

namespace igb {
namespace stm32 {

enum class RccClockSrc {
  INTERNAL = 0,
  EXTERNAL,
  PLL,
  HSI48
};

struct RccCtrl {
  static inline void enableBusClock(const auto& periph_bus_info) {
    periph_bus_info.enableBusClock();
  }
};

}
}

#endif /* IGB_STM32_PERIPH_RCC_H */
