#include "main.h"
#include "button.h"
#include "touch.h"
#include "led.h"
#include "oled.h"
#include "seq.h"
#include "input.h"
#include "timer.h"
#include "debug.h"
#include "button.h"
#include "clock.h"

extern "C" {
  void setup();
  void loop();
  void timer_2_event_handler();
}

void timer_2_event_handler() {
  if (timer_is_update(2)) {
    touch_process();
    button_process();

    timer_clear_update_flag(2);
  }
}

#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_bus.h"

void setup() {
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_DeInit(GPIOA);
  LL_GPIO_DeInit(GPIOB);
  LL_GPIO_DeInit(GPIOC);

  nts1_init();
  led_setup();
  oled_setup();
  input_setup();
  button_setup();

  //nts1_note_on(100, 100);
  
  //debug_text("SETUP", 5); 

  touch_setup();
  timer_simple_setup(2, 255, 100);
  timer_start(2);
}

void loop() {
  nts1_idle();
  led_process();
  oled_process();
}
