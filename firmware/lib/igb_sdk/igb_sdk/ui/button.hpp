#ifndef IGB_SDK_UI_BUTTON_H
#define IGB_SDK_UI_BUTTON_H

#include <igb_sdk/base.hpp>
#include <array>

namespace igb {
namespace sdk {

// チャタリングを防ぐために入力をバッファリング
struct DefaultButtonBuffer {
  uint8_t _data = 0;
  bool on = false;

  // return true if "on" state changed
  bool add(bool on_) {
    uint8_t new_data = (_data << 1) | (on_ ? 1 : 0);
    if (!isOnData(_data) && isOnData(new_data)) {
      on = true;
      _data = new_data;
      return true;
    }
    if (!isOffData(_data) && isOffData(new_data)) {
      on = false;
      _data = new_data;
      return true;
    }
    _data = new_data;
    return false;
  }

  bool isOn() {
    return on;
  }

  void reset() {
    _data = 0;
    on = false;
  }

  static bool isOnData(uint8_t data_) {
    return data_ == 0xFF;
  }

  static bool isOffData(uint8_t data_) {
    return data_ == 0;
  }
};

template<
  typename GPIO_PIN_TYPE,
  bool is_pull_up = true,
  typename BUTTON_BUFFER_TYPE = DefaultButtonBuffer
>
struct ButtonSingle {
  GPIO_PIN_TYPE pin;
  BUTTON_BUFFER_TYPE buf;

  void process() {
    buf.add(!!pin.read() != is_pull_up);
  };

  bool isOn() {
    return buf.isOn();
  }
};


template<
  typename GPIO_I_PIN_TYPE, uint8_t in_pin_size,
  typename GPIO_O_PIN_TYPE, uint8_t out_pin_size,
  bool is_pull_up = false,
  typename BUTTON_BUFFER_TYPE = DefaultButtonBuffer
>
struct ButtonMatrix {
  std::array<GPIO_I_PIN_TYPE, in_pin_size> in_pins;
  std::array<GPIO_O_PIN_TYPE, out_pin_size> out_pins;
  std::array<std::array<BUTTON_BUFFER_TYPE, out_pin_size>, in_pin_size> bufs;

  uint8_t _out_pin_idx = 0;

  void init() {
    for (const auto& out_pin : out_pins) {
      out_pin.write(is_pull_up);
    }
  }

  void process() {
    auto& prev_out_pin = out_pins[(_out_pin_idx + out_pin_size - 1) % out_pin_size];
    auto& out_pin = out_pins[_out_pin_idx];
    prev_out_pin.write(is_pull_up);
    out_pin.write(!is_pull_up);

    for (uint8_t i = 0; i < in_pin_size; ++i) {
      const auto& in_pin = in_pins[i];
      bufs[i][_out_pin_idx].add(!!in_pin.read() == !is_pull_up);
    }

    _out_pin_idx = (_out_pin_idx + 1) % out_pin_size;
  }

  bool isOn(size_t in_index, size_t out_index) {
    return bufs[in_index][out_index].isOn();
  }
};

// TODO: ButtonSerial

} // sdk
} // igb

#endif /* IGB_SDK_UI_BUTTON_H */
