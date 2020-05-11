#include "timer.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_tim.h"
#include "debug.h"

void timer_event_callback_null(void) {}
static TimerEventCallback timer_event_callback = timer_event_callback_null;
void timer_event_listen(TimerEventCallback cb) {
  timer_event_callback = cb;
}

void systick_timer_setup() {
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 1000)) { 
    /* Capture error */ 
    while (1);
  }
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void timer_2_setup() {
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  NVIC_SetPriority(TIM2_IRQn, 0);
  NVIC_EnableIRQ(TIM2_IRQn);

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
}

void timer_3_setup() {
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

  NVIC_SetPriority(TIM3_IRQn, 0);
  NVIC_EnableIRQ(TIM3_IRQn);
}

void timer_touch_setup() {
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);

  NVIC_SetPriority(TIM14_IRQn, 0);
  NVIC_EnableIRQ(TIM14_IRQn);
  LL_TIM_EnableIT_UPDATE(TIM14);

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  TIM_InitStruct.Prescaler = 255;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  //TIM_InitStruct.Autoreload = (2929*2) - 1; // 120 BPM = 2 Hz = 2 * 36MHz / 1(Prescale) / (36000000/12)(period);
  TIM_InitStruct.Autoreload = 100;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct.RepetitionCounter = 0;
  LL_TIM_Init(TIM14, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM14);
  LL_TIM_SetClockSource(TIM14, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_SetTriggerOutput(TIM14, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM14);
}

void timer_touch_start() {
  LL_TIM_SetCounter(TIM14, 0);
  LL_TIM_EnableCounter(TIM14);
}

void timer_setup() {
  //systick_timer_setup();

  timer_touch_setup();
  timer_touch_start();
}

//volatile uint32_t _current_msec;
//void SysTick_Handler() {
//  ++_current_msec;
//}

void TIM2_IRQHandler() {

}

void TIM3_IRQHandler() {
}

void TIM14_IRQHandler() {
  if (LL_TIM_IsActiveFlag_UPDATE(TIM14)) {
    timer_event_callback();
    LL_TIM_ClearFlag_UPDATE(TIM14);
  }
}
