#ifndef IGB_STM32_PERIPH_RCC_H
#define IGB_STM32_PERIPH_RCC_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>

using igb_util::as;;

namespace igb_stm32 {

enum class RccClockSrc {
  INTERNAL = 0,
  EXTERNAL,
  PLL,
  HSI48
};

struct RccCtrl {
  static inline void enablePeriphBus(const auto& periph_bus_info) {
    auto p_enr = STM32_BUS_TO_ENR_ADDRESS[ as<uint32_t>(periph_bus_info.bus_type) ];
    (*p_enr) |= periph_bus_info.periph_bit;
    __IO auto tmp = (*p_enr); // delay until clock enabled
  }
};

}

#endif /* IGB_STM32_PERIPH_RCC_H */
