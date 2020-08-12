#include "timer.h"
#include "stm32f0xx_ll_tim.h"
#include "timer_def.h"
#include "debug.h"

void timer_simple_setup(uint8_t timer_idx, uint16_t prescale, uint32_t period, uint16_t priority) {
  timer_clock_enable(timer_idx);
  TimerDef timer_def = timer_def_get(timer_idx);

  NVIC_SetPriority(timer_def.irqn_type, priority);
  NVIC_EnableIRQ(timer_def.irqn_type);
  LL_TIM_EnableIT_UPDATE(timer_def.p_tim);

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  TIM_InitStruct.Prescaler = prescale;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = (period == 0 ? 0 : (period - 1));
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(timer_def.p_tim, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(timer_def.p_tim);
  LL_TIM_SetClockSource(timer_def.p_tim, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(timer_def.p_tim, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(timer_def.p_tim);
}

void timer_start(uint8_t timer_idx) {
  TimerDef timer_def = timer_def_get(timer_idx);
  LL_TIM_SetCounter(timer_def.p_tim, 0);
  LL_TIM_EnableCounter(timer_def.p_tim);
}

void timer_stop(uint8_t timer_idx) {
  TimerDef timer_def = timer_def_get(timer_idx);
  LL_TIM_DisableCounter(timer_def.p_tim);
}

