#ifndef IGB_STM32_PERIPH_NVIC_H
#define IGB_STM32_PERIPH_NVIC_H

#include <igb_stm32/base.hpp>

namespace igb {
namespace stm32 {

struct NvicCtrl {
#ifdef NVIC_SetPriorityGrouping
  static inline void setPriorityGrouping(uint32_t group) {
    NVIC_SetPriorityGrouping(group);
  }
#endif
#ifdef NVIC_GetPriorityGrouping
  static inline uint32_t getPriorityGrouping() {
    return NVIC_GetPriorityGrouping();
  }
#endif
#ifdef NVIC_EnableIRQ
  static inline void enable(IRQn_Type irqn) {
    NVIC_EnableIRQ(irqn);
  }
#endif
#ifdef NVIC_GetEnableIRQ
  static inline bool isEnabled(IRQn_Type irqn) {
    return NVIC_GetEnableIRQ(irqn);
  }
#endif
#ifdef NVIC_DisableIRQ
  static inline void disable(IRQn_Type irqn) {
    NVIC_DisableIRQ(irqn);
  }
#endif
#ifdef NVIC_GetPendingIRQ
  static inline bool isPending(IRQn_Type irqn) {
    return NVIC_GetPendingIRQ(irqn);
  }
#endif
#ifdef NVIC_SetPendingIRQ
  static inline void pend(IRQn_Type irqn) {
    NVIC_SetPendingIRQ(irqn);
  }
#endif
#ifdef NVIC_ClearPendingIRQ
  static inline void clearPending(IRQn_Type irqn) {
    NVIC_ClearPendingIRQ(irqn);
  }
#endif
#ifdef NVIC_GetActive
  static inline bool isActive(IRQn_Type irqn) {
    return NVIC_GetActive(irqn);
  }
#endif
#ifdef NVIC_SetPriority
  static inline void setPriority(IRQn_Type irqn, uint32_t priority) {
    NVIC_SetPriority(irqn, priority);
  }
#endif
#ifdef NVIC_GetPriority
  static inline uint32_t getPriority(IRQn_Type irqn) {
    return NVIC_GetPriority(irqn);
  }
#endif
#ifdef NVIC_SystemReset
  static inline void systemReset() {
    NVIC_SystemReset();
  }
#endif
};

template <typename CtrlType = NvicCtrl>
struct NvicIrqn {
  IRQn_Type irqn;

#ifdef NVIC_EnableIRQ
  inline void enable() {
    CtrlType::enable(irqn);
  }
#endif
#ifdef NVIC_GetEnableIRQ
  inline bool isEnabled() {
    return CtrlType::isEnabled(irqn);
  }
#endif
#ifdef NVIC_DisableIRQ
  inline void disable() {
    CtrlType::disable(irqn);
  }
#endif
#ifdef NVIC_GetPendingIRQ
  inline bool isPending() {
    return CtrlType::isPending(irqn);
  }
#endif
#ifdef NVIC_SetPendingIRQ
  inline void pend() {
    CtrlType::pend(irqn);
  }
#endif
#ifdef NVIC_ClearPendingIRQ
  inline void clearPending() {
    CtrlType::clearPending(irqn);
  }
#endif
#ifdef NVIC_GetActive
  inline bool isActive() {
    return CtrlType::isActive(irqn);
  }
#endif
#ifdef NVIC_SetPriority
  inline void setPriority(uint32_t priority) {
    CtrlType::setPriority(irqn, priority);
  }
#endif
#ifdef NVIC_GetPriority
  inline uint32_t getPriority() {
    return CtrlType::getPriority(irqn);
  }
#endif
};

}
}

#endif /* IGB_STM32_PERIPH_NVIC_H */
