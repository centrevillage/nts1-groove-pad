#include "main.h"
#include "led.h"
#include "oled.h"
#include "app_seq.h"
#include "debug.h"
#include "text.h"
#include "nts1_defs.h"
#include "app_screen.hpp"
#include "preset.h"
#include "preset_event.h"
#include "ram.h"
#include "app_seq.h"
#include "app_touch.hpp"
#include "app_input.hpp"
#include "app_soft_timer.hpp"
#include <igb_stm32/periph/tim.hpp>
#include <igb_stm32/periph/flash.hpp>
#include <igb_stm32/periph/rcc.hpp>
#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/systick.hpp>

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
  auto tim = Tim { TIM_COMMON };
  if (tim.isState(TimState::UPDATE)) {

    led_process();
    app_input.process();
    //input_process();

    tim.clearState(TimState::UPDATE);
  }
}

void TIM_SPI_HANDLER() {
  auto tim = Tim { TIM_SPI };
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
  auto tim = Tim { TIM_SEQ };
  if (tim.isState(TimState::UPDATE)) {

    seq.receiveClock();

    tim.clearState(TimState::UPDATE);
  }
}

void system_clock_config() {
  FlashCtrl::setLatency(FlashLatency::one);

  RccCtrl::enableHSE();

   /* Wait till HSE is ready */
  while (!RccCtrl::isReadyHSE())
  RccCtrl::configPllSystemClockDomain(RccPllClockSrc::external, RccPllMul::mul6, RccPllDiv::div1);
  RccCtrl::enablePLL();

   /* Wait till PLL is ready */
  while(!RccCtrl::isReadyPLL());
  RccCtrl::setPrescalerAHB(RccClockPrescalerAHB::div1);
  RccCtrl::setPrescalerAPB1(RccClockPrescalerAPB1::div1);
  RccCtrl::setSystemClockSrc(RccClockSrc::pll);

   /* Wait till System clock is ready */
  while(RccCtrl::getSystemClockSrcStatus() != RccClockSrcStatus::pll);
  SystemCoreClock = 48000000;
}

void reset_gpio() {
  auto gpioa = GpioPort { GpioType::gpioa };
  auto gpiob = GpioPort { GpioType::gpiob };
  auto gpioc = GpioPort { GpioType::gpioc };
  gpioa.enable();
  gpiob.enable();
  gpioc.enable();
}

void setup() {
  system_clock_config();
  reset_gpio();

#ifndef USE_ARDUINO
  SystickCtrl::setTimerInterval(SystickTimerInterval::msec);
  NvicCtrl::setPriority(SysTick_IRQn, 0x0);
#endif

  led_setup();
  oled_setup();
  //input_setup();
  app_input.init();
  app_screen.init();
  //screen_setup();
  seq.init();

  //gpio_write(PIN_A12, 1);

  //delay_msec(1000);
  nts1_init();

  auto common_tim = Tim::newIntervalTimer(TIM_COMMON_TYPE, 255, 100, 2);
  common_tim.setCount(0);
  common_tim.enable();

  auto spi_tim = Tim::newIntervalTimer(TIM_SPI_TYPE, 255, 0xFFF, 5);
  spi_tim.setCount(0);
  spi_tim.enable();

  auto seq_tim = Tim::newIntervalTimer(TIM_SEQ_TYPE, 7000, 1000, 0);
  seq_tim.setCount(0);

  //nts1_note_on(100, 100);

  debug_text("LOADING", 7); 
  app_screen.changeMode(AppScreenDebug {});
  //screen_set_mode(SCREEN_MODE_INPUT_DEBUG);

  nts1_defs_req_load();
  nts1_idle();
  while (!nts1_defs_is_complete_loading()) {
    nts1_defs_process_loading();
    nts1_idle();
  }

  preset_setup();

  app_screen.changeMode(AppScreenEdit {});
  //screen_set_mode(SCREEN_MODE_EDIT);
  //input_refresh();
  app_input.refresh();
}

void loop() {
  nts1_idle();
  app_soft_timer.process(current_msec());
}

#ifndef USE_ARDUINO
int main() {
  setup();
  while(1) {
    loop();
  }
}
#endif
