#include "main.h"
#include "led.h"
#include "oled.h"
#include "app_seq.h"
#include "input.h"
#include "systick_timer.h"
#include "debug.h"
#include "text.h"
#include "nts1_defs.h"
#include "screen.h"
#include "preset.h"
#include "preset_event.h"
#include "ram.h"
#include "app_seq.h"
#include "app_touch.hpp"
#include <igb_stm32/periph/tim.hpp>

using namespace igb::stm32;

extern "C" {
#ifndef USE_ARDUINO
  int main();
#endif
  void setup();
  void loop();

  void TIM_COMMON_HANDLER();
  void TIM_SPI_HANDLER();
  void TIM_SEQ_HANDLER();
}

void TIM_COMMON_HANDLER() {
  auto tim = Timer { TIM_COMMON };
  if (tim.isState(TimState::UPDATE)) {

    led_process();
    input_process();

    tim.clearState(TimState::UPDATE);
  }
}

void TIM_SPI_HANDLER() {
  auto tim = Timer { TIM_SPI };
  if (tim.isState(TimState::UPDATE)) {

    if (preset_event_is_empty() && !preset_is_processing()) {
      oled_process();
    } else {
      preset_process();
      ram_process();
    }

    tim.clearState(TimState::UPDATE);
  }
}

void TIM_SEQ_HANDLER() {
  auto tim = Timer { TIM_SEQ };
  if (tim.isState(TimState::UPDATE)) {

    seq.receiveClock();

    tim.clearState(TimState::UPDATE);
  }
}

#include "stm32f0xx_hal.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_utils.h"

void system_clock_config() {
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLL_MUL_6, LL_RCC_PREDIV_DIV_1);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
  LL_SetSystemCoreClock(48000000);

   /* Update the time base */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
    //Error_Handler();  
  }
}

void reset_gpio() {
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_DeInit(GPIOA);
  LL_GPIO_DeInit(GPIOB);
  LL_GPIO_DeInit(GPIOC);
}

void setup() {
  system_clock_config();
  reset_gpio();

#ifndef USE_ARDUINO
  systick_timer_setup();
#endif

  led_setup();
  oled_setup();
  input_setup();
  screen_setup();
  seq.init();

  //gpio_write(PIN_A12, 1);

  //delay_msec(1000);
  nts1_init();

  auto common_tim = Timer::newIntervalTimer(TIM_COMMON_TYPE, 255, 100, 2);
  common_tim.setCount(0);
  common_tim.enable();

  auto spi_tim = Timer::newIntervalTimer(TIM_SPI_TYPE, 255, 0xFFF, 5);
  spi_tim.setCount(0);
  spi_tim.enable();

  auto seq_tim = Timer::newIntervalTimer(TIM_SEQ_TYPE, 7000, 5000, 0);
  seq_tim.setCount(0);

  //nts1_note_on(100, 100);

  debug_text("LOADING", 7); 
  screen_set_mode(SCREEN_MODE_INPUT_DEBUG);

  if (true) {

  nts1_defs_req_load();
  nts1_idle();
  while (!nts1_defs_is_complete_loading()) {
    nts1_defs_process_loading();
    nts1_idle();
  }

  preset_setup();

  }

  screen_set_mode(SCREEN_MODE_EDIT);
  input_refresh();
}

void loop() {
  nts1_idle();
}

#ifndef USE_ARDUINO
int main() {
  setup();
  while(1) {
    loop();
  }
}
#endif
