#ifndef IGB_STM32_PERIPH_TIM_H
#define IGB_STM32_PERIPH_TIM_H

#include <igb_stm32/base.hpp>
#include <igb_stm32/periph/rcc.hpp>
#include <igb_stm32/periph/nvic.hpp>
#include <igb_util/cast.hpp>

namespace igb {
namespace stm32 {

enum class TimState : uint32_t {
  UPDATE    = TIM_SR_UIF,
  CC1       = TIM_SR_CC1IF,
  CC2       = TIM_SR_CC2IF,
  CC3       = TIM_SR_CC3IF,
  CC4       = TIM_SR_CC4IF,
  COM       = TIM_SR_COMIF,
  TRIG      = TIM_SR_TIF,
  BREAK     = TIM_SR_BIF,
  CC1_OVER  = TIM_SR_CC1OF,
  CC2_OVER  = TIM_SR_CC2OF,
  CC3_OVER  = TIM_SR_CC3OF,
  CC4_OVER  = TIM_SR_CC4OF,
};

enum class TimCcCh : uint32_t {
  CC1 = 0,
  CC2,
  CC3,
  CC4,
};

enum class TimCounterMode : uint32_t {
  UP             = 0,
  DOWN           = TIM_CR1_DIR,
  CENTER_UP      = TIM_CR1_CMS_0,
  CENTER_DOWN    = TIM_CR1_CMS_1,
  CENTER_UP_DOWN = TIM_CR1_CMS,
};

// 列挙値をbitでなく、indexで持った方が共通化しやすいか？
enum class TimInterruptType : uint32_t {
  UPDATE  = TIM_DIER_UIE,
  CC1     = TIM_DIER_CC1IE,
  CC2     = TIM_DIER_CC2IE,
  CC3     = TIM_DIER_CC3IE,
  CC4     = TIM_DIER_CC4IE,
  COM     = TIM_DIER_COMIE,
  TRIGGER = TIM_DIER_TIE,
  BREAK   = TIM_DIER_BIE,
};

enum class TimEventGen : uint32_t {
  UPDATE  = TIM_EGR_UG,
  CC1     = TIM_EGR_CC1G,
  CC2     = TIM_EGR_CC2G,
  CC3     = TIM_EGR_CC3G,
  CC4     = TIM_EGR_CC4G,
  COM     = TIM_EGR_COMG,
  TRIGGER = TIM_EGR_TG,
  BREAK   = TIM_EGR_BG,
};

enum class TimClockDiv : uint32_t {
  DIV1 = 0,
  DIV2 = TIM_CR1_CKD_0,
  DIV4 = TIM_CR1_CKD_1,
};

enum class TimCounterDir : uint32_t {
  UP   = 0,
  DOWN = TIM_CR1_DIR,
};

enum class TimClockSrc : uint32_t {
  INTERNAL  = 0,
  EXT_MODE1 = (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0),
  EXT_MODE2 = TIM_SMCR_ECE,
};

enum class TimTriggerOut : uint32_t {
  RESET  = 0,
  ENABLE = TIM_CR2_MMS_0,
  UPDATE = TIM_CR2_MMS_1,
  CC1IF  = (TIM_CR2_MMS_1 | TIM_CR2_MMS_0),
  OC1REF = TIM_CR2_MMS_2,
  OC2REF = (TIM_CR2_MMS_2 | TIM_CR2_MMS_0),
  OC3REF = (TIM_CR2_MMS_2 | TIM_CR2_MMS_1),
  OC4REF = (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0),
};

enum class TimEtrConfPolarity : uint32_t {
  NONINVERTED = 0,
  INVERTED = TIM_SMCR_ETP,
};

enum class TimEtrConfPrescaler : uint32_t {
  DIV1 = 0,
  DIV2 = TIM_SMCR_ETPS_0,
  DIV4 = TIM_SMCR_ETPS_1,
  DIV8 = TIM_SMCR_ETPS,
};

enum class TimEtrConfFilter : uint32_t {
  FDIV1     = 0,
  FDIV1_N2  = TIM_SMCR_ETF_0,
  FDIV1_N4  = TIM_SMCR_ETF_1,
  FDIV1_N8  = (TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0),
  FDIV2_N6  = TIM_SMCR_ETF_2,
  FDIV2_N8  = (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0),
  FDIV4_N6  = (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1),
  FDIV4_N8  = (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0),
  FDIV8_N6  = TIM_SMCR_ETF_3,
  FDIV8_N8  = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0),
  FDIV16_N5 = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1),
  FDIV16_N6 = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0),
  FDIV16_N8 = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2),
  FDIV32_N5 = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0),
  FDIV32_N6 = (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1),
  FDIV32_N8 = TIM_SMCR_ETF,
};

enum class TimBreakPolarity : uint32_t {
  LOW = 0,
  HIGH = TIM_BDTR_BKP,
};

enum class TimDmaBurstBaseAddr : uint32_t {
  CR1   = 0,
  CR2   = TIM_DCR_DBA_0,
  SMCR  = TIM_DCR_DBA_1,
  DIER  = (TIM_DCR_DBA_1 |  TIM_DCR_DBA_0),
  SR    = TIM_DCR_DBA_2,
  EGR   = (TIM_DCR_DBA_2 | TIM_DCR_DBA_0),
  CCMR1 = (TIM_DCR_DBA_2 | TIM_DCR_DBA_1),
  CCMR2 = (TIM_DCR_DBA_2 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0),
  CCER  = TIM_DCR_DBA_3,
  CNT   = (TIM_DCR_DBA_3 | TIM_DCR_DBA_0),
  PSC   = (TIM_DCR_DBA_3 | TIM_DCR_DBA_1),
  ARR   = (TIM_DCR_DBA_3 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0),
  RCR   = (TIM_DCR_DBA_3 | TIM_DCR_DBA_2),
  CCR1  = (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_0),
  CCR2  = (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1),
  CCR3  = (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0),
  CCR4  = TIM_DCR_DBA_4,
  BDTR  = (TIM_DCR_DBA_4 | TIM_DCR_DBA_0),
};

enum class TimDmaBurstLen : uint32_t {
  L1 = 0,
  L2  = TIM_DCR_DBL_0,
  L3  = TIM_DCR_DBL_1,
  L4  = (TIM_DCR_DBL_1 |  TIM_DCR_DBL_0),
  L5  = TIM_DCR_DBL_2,
  L6  = (TIM_DCR_DBL_2 | TIM_DCR_DBL_0),
  L7  = (TIM_DCR_DBL_2 | TIM_DCR_DBL_1),
  L8  = (TIM_DCR_DBL_2 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0),
  L9  = TIM_DCR_DBL_3,
  L10 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_0),
  L11 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_1),
  L12 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0),
  L13 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_2),
  L14 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_0),
  L15 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1),
  L16 = (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0),
  L17 = TIM_DCR_DBL_4,
  L18 = (TIM_DCR_DBL_4 |  TIM_DCR_DBL_0),
};

// TODO: デバイス依存の記述になっているので一旦機能削除
//enum class TimRemapInput : uint32_t { 
//  TO_GPIO = TIM14_OR_RMP_MASK,
//  TO_RTC_CLK = (TIM14_OR_TI1_RMP_0  | TIM14_OR_RMP_MASK),
//  TO_HSE = (TIM14_OR_TI1_RMP_1  | TIM14_OR_RMP_MASK),
//  TO_MCO = (TIM14_OR_TI1_RMP_0  | TIM14_OR_TI1_RMP_1  | TIM14_OR_RMP_MASK),
//};

struct Tim {
  TIM_TypeDef* p_tim;

  void setPrescaler(uint32_t prescale) {
    p_tim->PSC = prescale;
  }

  void setCounterMode(TimCounterMode mode) {
    MODIFY_REG(p_tim->CR1, (TIM_CR1_DIR | TIM_CR1_CMS), as<uint32_t>(mode));
  }

  void setClockDiv(TimClockDiv div) {
    MODIFY_REG(p_tim->CR1, TIM_CR1_CKD, as<uint32_t>(div));
  }

  void enableArrPreload() {
    SET_BIT(p_tim->CR1, TIM_CR1_ARPE);
  }

  void disableArrPreload() {
    CLEAR_BIT(p_tim->CR1, TIM_CR1_ARPE);
  }

  void setCcValue(TimCcCh ch, uint32_t value) {
    __IO uint32_t* ptr = &(p_tim->CCR1) + as<uint32_t>(ch);
    (*ptr) = value;
  }

  uint32_t getCcValue(TimCcCh ch) {
    __IO uint32_t* ptr = &(p_tim->CCR1) + as<uint32_t>(ch);
    return *ptr;
  }

  void setAutoreload(uint32_t value) {
    p_tim->ARR = value;
  }

  void setRepetitionCounter(uint8_t value) {
    p_tim->RCR = value;
  }

  void setClockSrc(TimClockSrc src) {
    MODIFY_REG(p_tim->SMCR, TIM_SMCR_SMS | TIM_SMCR_ECE, as<uint32_t>(src));
  }

  void setTriggerOutput(TimTriggerOut out) {
    MODIFY_REG(p_tim->CR2, TIM_CR2_MMS, as<uint32_t>(out));
  }

  void setMasterSlaveMode(bool is_master_slave) {
    if (is_master_slave) {
      p_tim->SMCR |= TIM_SMCR_MSM;
    } else {
      p_tim->SMCR &= ~TIM_SMCR_MSM;
    }
  }

  void setEtrConf(TimEtrConfPolarity polarity, TimEtrConfPrescaler prescaler, TimEtrConfFilter filter) {
    MODIFY_REG(p_tim->SMCR,
        TIM_SMCR_ETP | TIM_SMCR_ETPS | TIM_SMCR_ETF,
        as<uint32_t>(polarity) | as<uint32_t>(prescaler) | as<uint32_t>(filter));
  }

  bool isState(TimState state) {
    return !!(p_tim->SR & as<uint32_t>(state));
  }

  void clearState(TimState state) {
    p_tim->SR &= ~(as<uint32_t>(state));
  }

  void setCount(uint32_t count) {
    p_tim->CNT = count;
  }

  uint32_t getCount() {
    return p_tim->CNT;
  }

  void generateEvent(TimEventGen event) {
    p_tim->EGR |= as<uint32_t>(event);
  }

  void enableInterrupt(TimInterruptType interrupt) {
    p_tim->DIER |= as<uint32_t>(interrupt);
  }

  void disableInterrupt(TimInterruptType interrupt) {
    p_tim->DIER &= ~(as<uint32_t>(interrupt));
  }

  void setDeadtime(uint8_t dead_time) {
    MODIFY_REG(p_tim->BDTR, TIM_BDTR_DTG, as<uint32_t>(dead_time));
  }

  void enableBreak() {
    p_tim->BDTR |= TIM_BDTR_BKE;
    __IO uint32_t tmp = p_tim->BDTR;
  }

  void disableBreak() {
    p_tim->BDTR &= ~TIM_BDTR_BKE;
    __IO uint32_t tmp = p_tim->BDTR;
  }

  void configBreak(TimBreakPolarity polarity) {
    MODIFY_REG(p_tim->BDTR, TIM_BDTR_BKP, as<uint32_t>(polarity));
    __IO uint32_t tmp = p_tim->BDTR;
  }

  void setOffStates(bool off_state_idle, bool off_state_run) {
    MODIFY_REG(p_tim->BDTR, TIM_BDTR_OSSI | TIM_BDTR_OSSR, (off_state_idle ? TIM_BDTR_OSSI : 0) | (off_state_run ? TIM_BDTR_OSSR : 0));
  }

  void enableAutoOut() {
    p_tim->BDTR |= TIM_BDTR_AOE;
  }
  void disableAutoOut() {
    p_tim->BDTR &= ~TIM_BDTR_AOE;
  }

  void enableAllOut() {
    p_tim->BDTR |= TIM_BDTR_MOE;
  }
  void disableAllOut() {
    p_tim->BDTR &= ~TIM_BDTR_MOE;
  }

  void configDmaBurst(TimDmaBurstBaseAddr addr, TimDmaBurstLen len) {
    MODIFY_REG(p_tim->DCR, (TIM_DCR_DBL | TIM_DCR_DBA), (as<uint32_t>(addr) | as<uint32_t>(len)));
  }

//  void setRemap(TimRemapInput remap) {
//    MODIFY_REG(p_tim->OR, (as<uint32_t>(remap) >> 16U), (as<uint32_t>(remap) & 0x0000FFFFU));
//  }

  void enable() {
    p_tim->CR1 |= TIM_CR1_CEN;
  }
  void disable() {
    p_tim->CR1 &= ~TIM_CR1_CEN;
  }

  // TODO: コンパイル時の依存を減らすため、外部関数化＆外部ファイル化すべき？
  static Tim newIntervalTimer(TimType type, uint16_t prescale, uint32_t period, uint16_t priority) {
    const auto& info = STM32_PERIPH_INFO.tim[as<uint32_t>(type)];
    info.bus.enableBusClock();

    NvicCtrl::setPriority(info.irqn, priority);
    NvicCtrl::enable(info.irqn);

    auto timer = Tim { info.p_tim };
    timer.enableInterrupt(TimInterruptType::UPDATE);
    timer.setPrescaler(prescale);
    timer.setCounterMode(TimCounterMode::UP);
    timer.setAutoreload((period == 0 ? 0 : (period - 1)));
    timer.setClockDiv(TimClockDiv::DIV1);
    timer.setRepetitionCounter(0);
    timer.disableArrPreload();
    timer.setClockSrc(TimClockSrc::INTERNAL);
    timer.setTriggerOutput(TimTriggerOut::RESET);
    timer.setMasterSlaveMode(false);

    return timer;
  }
};

} // namespace stm32
} // namespace igb

#endif /* IGB_STM32_PERIPH_TIM_H */
