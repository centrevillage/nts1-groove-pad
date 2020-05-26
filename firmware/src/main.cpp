#include "main.h"
#include "button.h"
#include "touch.h"
#include "led.h"
#include "oled.h"
#include "seq.h"
#include "input.h"
#include "timer.h"
#include "debug.h"
#include "text.h"
#include "button.h"
#include "nts1_defs.h"
#include "screen.h"

extern "C" {
#ifndef USE_ARDUINO
  int main();
#endif
  void setup();
  void loop();
  void timer_2_event_handler();
  void timer_4_event_handler();
  void timer_5_event_handler();
}

void timer_2_event_handler() {
  if (timer_is_update(2)) {
    touch_process();
    button_process();
    led_process();

    timer_clear_update_flag(2);
  }
}

void timer_4_event_handler() {
  if (timer_is_update(4)) {
    oled_process();
    //nts1_req_sys_version();
    timer_clear_update_flag(4);
  }
}

void timer_5_event_handler() {
  if (timer_is_update(5)) {
    nts1_idle();
    timer_clear_update_flag(5);
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
  systick_setup();
#endif

  led_setup();
  oled_setup();
  input_setup();
  button_setup();
  screen_setup();

  //gpio_write(PIN_A12, 1);


  touch_setup();

  //delay_msec(1000);
  nts1_init();

  timer_simple_setup(2, 255, 100, 2);
  timer_start(2);
  timer_simple_setup(4, 255, 0xFFF, 5);
  timer_start(4);
  timer_simple_setup(5, 16, 100, 0);
  timer_start(5);

  //char buf[9];
  //text_0x_from_uint32(buf, SystemCoreClock);
  //debug_text(buf, 8);

  //nts1_note_on(100, 100);

  debug_text("LOADING", 7); 
  screen_set_mode(SCREEN_MODE_INPUT_DEBUG);

  nts1_defs_req_load();
  while (!nts1_defs_is_complete_loading()) {
    nts1_defs_process_loading();
  }

  screen_set_mode(SCREEN_MODE_EDIT);
}

void loop() {
}

#ifndef USE_ARDUINO
int main() {
  setup();
  while(1) {
    loop();
  }
}
#endif
