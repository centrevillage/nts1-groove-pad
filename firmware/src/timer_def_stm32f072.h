#ifndef __N1GP_TIMER_DEF_STM32F072_H__
#define __N1GP_TIMER_DEF_STM32F072_H__

#define TIMER_DEF_STM32F072_SIZE 6
// TIM6/7 はDAC用、TIM1は特殊なタイマーなのでひとまず対象外
static const TimerDef timer_defs[TIMER_DEF_STM32F072_SIZE] = {
  {TIM2, TIM2_IRQn, 32},
  {TIM3, TIM3_IRQn, 32},
  {TIM14, TIM14_IRQn, 16},
  {TIM15, TIM15_IRQn, 16},
  {TIM16, TIM16_IRQn, 16},
  {TIM17, TIM17_IRQn, 16},
};

static inline void timer_clock_enable(uint8_t idx) {
  switch (idx) {
    case 0:
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
      break;
    case 1:
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
      break;
    case 2:
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
      break;
    case 3:
      LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM15);
      break;
    case 4:
      LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM16);
      break;
    case 5:
      LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM17);
      break;
    default:
      break;
  }
}

#define TIM2_DEF_IDX 0
#define TIM3_DEF_IDX 1
#define TIM14_DEF_IDX 2
#define TIM15_DEF_IDX 3
#define TIM16_DEF_IDX 4
#define TIM17_DEF_IDX 5

#define timer_0_event_handler TIM2_IRQHandler
#define timer_1_event_handler TIM3_IRQHandler
#define timer_2_event_handler TIM14_IRQHandler
#define timer_3_event_handler TIM15_IRQHandler
#define timer_4_event_handler TIM16_IRQHandler
#define timer_5_event_handler TIM17_IRQHandler

#endif /* __N1GP_TIMER_DEF_STM32F072_H__ */
