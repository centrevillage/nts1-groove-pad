#include "main.h"
#include "led.h"

#include <igb_stm32/periph/gpio.hpp>
#include <igb_sdk/ui/led.hpp>

using namespace igb::stm32;
using namespace igb::sdk;

LedMatrix<GpioPin, 4, 4> led_matrix = {
  .a_pins = {
    GpioPin::newPin(GpioPinType::pc8),
    GpioPin::newPin(GpioPinType::pc9),
    GpioPin::newPin(GpioPinType::pc10),
    GpioPin::newPin(GpioPinType::pc11)
  },
  .k_pins = {
    GpioPin::newPin(GpioPinType::pc12),
    GpioPin::newPin(GpioPinType::pc13),
    GpioPin::newPin(GpioPinType::pc14),
    GpioPin::newPin(GpioPinType::pc15)
  }
};

//auto led_a_pin = GpioPin::newPin(GpioPinType::pc8);
//auto led_b_pin = GpioPin::newPin(GpioPinType::pc9);
//auto led_c_pin = GpioPin::newPin(GpioPinType::pc10);
//auto led_d_pin = GpioPin::newPin(GpioPinType::pc11);
//auto led_1_pin = GpioPin::newPin(GpioPinType::pc12);
//auto led_2_pin = GpioPin::newPin(GpioPinType::pc13);
//auto led_3_pin = GpioPin::newPin(GpioPinType::pc14);
//auto led_4_pin = GpioPin::newPin(GpioPinType::pc15);
auto led_run_pin = GpioPin::newPin(GpioPinType::pc0);
auto led_mode_pin = GpioPin::newPin(GpioPinType::pa12);

__IO uint32_t led_bits = 0;

void led_setup() {
  for (auto& pin : led_matrix.a_pins) {
    pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  }
  for (auto& pin : led_matrix.k_pins) {
    pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  }
  //led_a_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_b_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_c_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_d_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_1_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_2_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_3_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  //led_4_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  led_run_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
  led_mode_pin.initOutput(GpioOutputMode::PUSHPULL, GpioSpeedMode::HIGH);
}

//GpioPin led_row_pins[] = {
//  led_a_pin, led_b_pin, led_c_pin, led_d_pin
//};

//GpioPin led_col_pins[] = {
//  led_1_pin, led_2_pin, led_3_pin, led_4_pin
//};

void led_process() {
  led_matrix.process();

  //static uint8_t led_matrix_idx = 0;
  //led_row_pins[(led_matrix_idx+3)%4].low();

  led_mode_pin.write(!!(led_bits & (1UL<<16)));
  led_run_pin.write(!!(led_bits & (1UL<<17)));

  //for (uint8_t i=0;i<4;++i) {
  //  led_col_pins[i].write(!(led_bits & (1UL << (led_matrix_idx*4+i))));
  //}
  //led_row_pins[led_matrix_idx].high();

  //led_matrix_idx = (led_matrix_idx+1) % 4;
}

void led_set_run(uint8_t on) {
  led_set(17, on);
}

void led_set_mode(uint8_t on) {
  led_set(16, on);
}

void led_set(uint8_t index, uint8_t on) {
  if (index < 16) {
    led_matrix.set(index / 4, index % 4, on);
  } else {
    if (on) {
      led_bits |= (1UL<<index);
    } else {
      led_bits &= ~(1UL<<index);
    }
  }
};

void led_clear() {
  led_bits = 0;
  led_matrix.allOff();
}
