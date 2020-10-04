#ifndef IGB_STM32_PERIPH_RCC_H
#define IGB_STM32_PERIPH_RCC_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_util/macro.hpp>

namespace igb {
namespace stm32 {

enum class RccClockSrc {
  internal = RCC_CFGR_SW_HSI,
  external = RCC_CFGR_SW_HSE,
  pll = RCC_CFGR_SW_PLL,
#if defined(RCC_HSI48_SUPPORT)
  hsi48 = RCC_CFGR_SW_HSI48
#endif
};

enum class RccClockSrcStatus {
  internal = RCC_CFGR_SWS_HSI,
  external = RCC_CFGR_SWS_HSE,
  pll = RCC_CFGR_SWS_PLL,
#if defined(RCC_HSI48_SUPPORT)
  hsi48 = RCC_CFGR_SWS_HSI48
#endif
};

#if defined(RCC_CFGR_HPRE)
enum class RccClockPrescalerAHB {
  div1 = RCC_CFGR_HPRE_DIV1,
  div2 = RCC_CFGR_HPRE_DIV2,
  div4 = RCC_CFGR_HPRE_DIV4,
  div8 = RCC_CFGR_HPRE_DIV8,
  div16 = RCC_CFGR_HPRE_DIV16,
  div64 = RCC_CFGR_HPRE_DIV64,
  div128 = RCC_CFGR_HPRE_DIV128,
  div256 = RCC_CFGR_HPRE_DIV256,
  div512 = RCC_CFGR_HPRE_DIV512,
};
#endif

#if defined(RCC_CFGR_PPRE)
enum class RccClockPrescalerAPB1 {
  div1 = RCC_CFGR_PPRE_DIV1,
  div2 = RCC_CFGR_PPRE_DIV2,
  div4 = RCC_CFGR_PPRE_DIV4,
  div8 = RCC_CFGR_PPRE_DIV8,
  div16 = RCC_CFGR_PPRE_DIV16
};
#endif

#if defined(RCC_PLLSRC_PREDIV1_SUPPORT)
enum class RccPllClockSrc : uint32_t {
  internal = RCC_CFGR_PLLSRC_HSI_PREDIV,
  external = RCC_CFGR_PLLSRC_HSE_PREDIV,
#if defined(RCC_CFGR_PLLSRC_HSI48_PREDIV)
  hsi48 = RCC_CFGR_PLLSRC_HSI48_PREDIV
#endif
};

enum class RccPllMul : uint32_t {
  mul2 = RCC_CFGR_PLLMUL2,
  mul3 = RCC_CFGR_PLLMUL3,
  mul4 = RCC_CFGR_PLLMUL4,
  mul5 = RCC_CFGR_PLLMUL5,
  mul6 = RCC_CFGR_PLLMUL6,
  mul7 = RCC_CFGR_PLLMUL7,
  mul8 = RCC_CFGR_PLLMUL8,
  mul9 = RCC_CFGR_PLLMUL9,
  mul10 = RCC_CFGR_PLLMUL10,
  mul11 = RCC_CFGR_PLLMUL11,
  mul12 = RCC_CFGR_PLLMUL12,
  mul13 = RCC_CFGR_PLLMUL13,
  mul14 = RCC_CFGR_PLLMUL14,
  mul15 = RCC_CFGR_PLLMUL15,
  mul16 = RCC_CFGR_PLLMUL16,
};

enum class RccPllDiv {
  div1 = RCC_CFGR2_PREDIV_DIV1,
  div2 = RCC_CFGR2_PREDIV_DIV2,
  div3 = RCC_CFGR2_PREDIV_DIV3,
  div4 = RCC_CFGR2_PREDIV_DIV4,
  div5 = RCC_CFGR2_PREDIV_DIV5,
  div6 = RCC_CFGR2_PREDIV_DIV6,
  div7 = RCC_CFGR2_PREDIV_DIV7,
  div8 = RCC_CFGR2_PREDIV_DIV8,
  div9 = RCC_CFGR2_PREDIV_DIV9,
  div10 = RCC_CFGR2_PREDIV_DIV10,
  div11 = RCC_CFGR2_PREDIV_DIV11,
  div12 = RCC_CFGR2_PREDIV_DIV12,
  div13 = RCC_CFGR2_PREDIV_DIV13,
  div14 = RCC_CFGR2_PREDIV_DIV14,
  div15 = RCC_CFGR2_PREDIV_DIV15,
  div16 = RCC_CFGR2_PREDIV_DIV16,
};
#endif

struct RccCtrl {
  static IGB_FAST_INLINE void enableBusClock(const auto& periph_bus_info) {
    periph_bus_info.enableBusClock();
  }

  static IGB_FAST_INLINE void enableHSE() {
    SET_BIT(RCC->CR, RCC_CR_HSEON);
  }

  static IGB_FAST_INLINE void disableHSE() {
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
  }
  
  static IGB_FAST_INLINE bool isReadyHSE() {
    return (READ_BIT(RCC->CR, RCC_CR_HSERDY) == (RCC_CR_HSERDY));
  }

  static IGB_FAST_INLINE void enableHSI() {
    SET_BIT(RCC->CR, RCC_CR_HSION);
  }

  static IGB_FAST_INLINE void disableHSI() {
    CLEAR_BIT(RCC->CR, RCC_CR_HSION);
  }

  static IGB_FAST_INLINE bool isReadyHSI() {
    return (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY));
  }

#if defined(RCC_HSI48_SUPPORT)
  static IGB_FAST_INLINE void enableHSI48() {
    SET_BIT(RCC->CR2, RCC_CR2_HSI48ON);
  }

  static IGB_FAST_INLINE void disableHSI48() {
    CLEAR_BIT(RCC->CR2, RCC_CR2_HSI48ON);
  }
#endif

#if defined(RCC_CR2_HSI14ON)
  static IGB_FAST_INLINE void enableHSI14() {
    SET_BIT(RCC->CR2, RCC_CR2_HSI14ON);
  }

  static IGB_FAST_INLINE void disableHSI14() {
    CLEAR_BIT(RCC->CR2, RCC_CR2_HSI14ON);
  }
#endif

#if defined(RCC_BDCR_LSEON)
  static IGB_FAST_INLINE void enableLSE() {
    SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);
  }

  static IGB_FAST_INLINE void disableLSE() {
    CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);
  }
#endif

#if defined(RCC_BDCR_LSEBYP)
  static IGB_FAST_INLINE void enableLseBypass() {
    SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
  }

  static IGB_FAST_INLINE void disableLseBypass() {
    CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);
  }
#endif

#if defined(RCC_CSR_LSION)
  static IGB_FAST_INLINE void enableLSI() {
    SET_BIT(RCC->CSR, RCC_CSR_LSION);
  }

  static IGB_FAST_INLINE void disableLSI() {
    CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
  }
#endif

  static IGB_FAST_INLINE void setSystemClockSrc(RccClockSrc clock_src) {
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, static_cast<uint32_t>(clock_src));
  }

  static IGB_FAST_INLINE RccClockSrcStatus getSystemClockSrcStatus() {
    return static_cast<RccClockSrcStatus>(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
  }

#if defined(RCC_CFGR_HPRE)
  static IGB_FAST_INLINE void setPrescalerAHB(RccClockPrescalerAHB prescaler)  {
    MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, static_cast<uint32_t>(prescaler));
  }
#endif

#if defined(RCC_CFGR_PPRE)
  static IGB_FAST_INLINE void setPrescalerAPB1(RccClockPrescalerAPB1 prescaler) {
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE, static_cast<uint32_t>(prescaler));
  }
#endif

#if defined(RCC_CR_PLLON)
  static IGB_FAST_INLINE void enablePLL() {
    SET_BIT(RCC->CR, RCC_CR_PLLON);
  }

  static IGB_FAST_INLINE void disablePLL() {
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
  }

  static IGB_FAST_INLINE bool isReadyPLL() {
    return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY));
  }
#endif

  static IGB_FAST_INLINE void configPllSystemClockDomain(RccPllClockSrc clock_src, RccPllMul mul, RccPllDiv div) {
#if defined(RCC_PLLSRC_PREDIV1_SUPPORT)
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL, static_cast<uint32_t>(clock_src) | static_cast<uint32_t>(mul));
    MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, static_cast<uint32_t>(div));
#else
    MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL, (static_cast<uint32_t>(clock_src) & RCC_CFGR_PLLSRC) | static_cast<uint32_t>(mul));
    MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, (static_cast<uint32_t>(clock_src) & RCC_CFGR2_PREDIV));
#endif
  }

  //static IGB_FAST_INLINE void setPllMainSrc(RccPllSrc src) {
  //}
};

}
}

#endif /* IGB_STM32_PERIPH_RCC_H */
