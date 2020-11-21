#ifndef IGB_IDK_UI_LED_H
#define IGB_IDK_UI_LED_H

#include <igb_sdk/base.hpp>
#include <array>
#include <bitset>

namespace igb {
namespace sdk {

template<
  typename GPIO_PIN_TYPE,
  bool high_on = true
>
struct LedSingle {
  GPIO_PIN_TYPE pin;

  void write(bool is_on) {
    pin.write(is_on);
  }

  void on() {
    pin.on();
  }

  void off() {
    pin.off();
  }
};

template<
  typename GPIO_PIN_TYPE, uint8_t a_pin_size, uint8_t k_pin_size
>
struct LedMatrix {
  std::array<GPIO_PIN_TYPE, a_pin_size> a_pins;
  std::array<GPIO_PIN_TYPE, k_pin_size> k_pins;
  std::bitset<k_pin_size * a_pin_size> bits;

  uint8_t _idx = 0;

  void init() {
    allOff();
  }

  void allOff() {
    for (auto& pin : a_pins) {
      pin.off();
    }
    for (auto& pin : k_pins) {
      pin.off();
    }
  }

  void set(uint8_t a_idx, uint8_t k_idx, bool on) {
    if (on) {
      bits.set(a_idx * k_pin_size + k_idx);
    } else {
      bits.reset(a_idx * k_pin_size + k_idx);
    }
  }

  void process() {
    a_pins[(_idx + (a_pin_size-1)) % a_pin_size].low();
    for (uint8_t i=0;i<k_pin_size;++i) {
      k_pins[i].write(!(bits[_idx * k_pin_size + i]));
    }
    a_pins[_idx].high();
    _idx = (_idx+1) % a_pin_size;
  }
};

} // sdk
} // igb

#endif /* IGB_IDK_UI_LED_H */
