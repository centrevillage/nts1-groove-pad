#include "oled.h"
#include "screen_conf.h"
#include "draw.h"
#include "debug.h"
#include "app_screen.hpp"
#include "app_input.hpp"

#include <igb_stm32/periph/systick.hpp>
#include <igb_stm32/periph/rcc.hpp>
#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/spi.hpp>
#include <igb_sdk/device/oled_ssd1306.hpp>
#include <igb_sdk/util/text.h>

using namespace igb::stm32;
using namespace igb::sdk;

OledSsd1306<GpioPin, Spi, 128, 64> ssd1306 = {
  .cs_pin = GpioPin::newPin(GpioPinType::pb9),
  .dc_pin = GpioPin::newPin(GpioPinType::pb5),
  .reset_pin = GpioPin::newPin(GpioPinType::pb8),
  .spi = Spi::newSpi(SpiType::spi1)
};

void oled_setup() {
  ssd1306.spi.prepareSpiMaster(GpioPinType::pa7, GpioPinType::pa6, GpioPinType::pa5, SpiBaudratePrescaler::DIV2);
  ssd1306.init();
}

void oled_process() {
  app_screen.draw(ssd1306.screen_buffer);
  for (uint8_t i = 0; i < 8; ++i) {
    if (app_input.touch_bits & (1 << i)) {
      draw_touch_pad_small(ssd1306.screen_buffer, (DrawPadType)i);
    }
  }
  ssd1306.process();
}
