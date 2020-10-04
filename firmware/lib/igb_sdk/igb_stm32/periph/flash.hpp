#ifndef IGB_STM32_PERIPH_FLASH_H
#define IGB_STM32_PERIPH_FLASH_H

#include <igb_stm32/base.hpp>
#include <igb_util/macro.hpp>

namespace igb {
namespace stm32 {

enum class FlashLatency {
  zero = 0,
  one = FLASH_ACR_LATENCY,
};

struct FlashCtrl {
  static IGB_FAST_INLINE void setLatency(FlashLatency latency) {
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, static_cast<uint32_t>(latency));
  }

  static IGB_FAST_INLINE FlashLatency getLatency() {
    return static_cast<FlashLatency>(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
  }

  static IGB_FAST_INLINE void enablePrefetch() {
    SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
  }

  static IGB_FAST_INLINE void disablePrefetch() {
    CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
  }

  static IGB_FAST_INLINE bool isPrefetchEnabled() {
    return (READ_BIT(FLASH->ACR, FLASH_ACR_PRFTBS) == (FLASH_ACR_PRFTBS));
  }
};

}
}

#endif /* IGB_STM32_PERIPH_FLASH_H */
