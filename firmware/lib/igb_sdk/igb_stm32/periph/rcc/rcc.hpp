#ifndef IGB_STM32_PERIPH_RCC_RCC_H
#define IGB_STM32_PERIPH_RCC_RCC_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>

using igb_util::enum_cast;

namespace igb_stm32 {

enum class RccClockSrc {
  INTERNAL = 0,
  EXTERNAL,
  PLL,
  HSI48
};

struct RccCtrl {
  static void enablePeriphBus(PeriphBusInfo periph_bus_info) {
    auto p_enr = STM32_BUS_TO_ENR_ADDRESS[ enum_cast(periph_bus_info.bus_type) ];
    (*p_enr) |= periph_bus_info.periph_bit;
    __IO tmp = (*p_enr); // delay until clock enabled
  }
};

}

#endif /* IGB_STM32_PERIPH_RCC_RCC_H */
