#ifndef __N1GP_TIMER_DEF_H__
#define __N1GP_TIMER_DEF_H__

#include "main.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
 TIM_TypeDef *p_tim;
 IRQn_Type irqn_type;
 uint8_t bit_size;
} TimerDef;

// TODO: other stm config
#include "timer_def_stm32f072.h"

static inline TimerDef timer_def_get(uint8_t idx) {
  return timer_defs[idx]; 
}

static inline uint8_t timer_is_update(uint8_t timer_idx) {
  return LL_TIM_IsActiveFlag_UPDATE(timer_defs[timer_idx].p_tim);
}

static inline void timer_clear_update_flag(uint8_t timer_idx) {
  LL_TIM_ClearFlag_UPDATE(timer_defs[timer_idx].p_tim);
}

static inline uint8_t timer_get_count(uint8_t timer_idx) {
  return LL_TIM_GetCounter(timer_defs[timer_idx].p_tim);
}

static inline void timer_set_count(uint8_t timer_idx, uint32_t count) {
  LL_TIM_SetCounter(timer_defs[timer_idx].p_tim, count);
}

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_TIMER_DEF_H__ */
