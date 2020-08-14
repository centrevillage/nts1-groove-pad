#ifndef APP_BUTTON_H
#define APP_BUTTON_H

#include <igb_stm32/gpio.hpp>
#include <igb_sdk/ui/button.hpp>
#include <functional>

// 危険は承知の上・・・
using namespace igb_stm32;
using namespace igb_sdk;

enum class AppBtnID : uint8_t {
  OSC = 0, PARAM, FILTER, EG, MOD, DELAY, REVERB, ARP,
  SAVE, LOAD, CLEAR, GLOBAL, SCALE, TRANS, STUTTER, LFO,
  SEQ, RUN, L, R,

  SIZE
};

struct AppButtons {
  // こう書けたらいいのに！
  //using namespace igb_stm32;
  //using namespace igb_sdk;

  const GPIOPort port_a { GPIOA };
  const GPIOPort port_b { GPIOB };
  const GPIOPort port_c { GPIOC };

  volatile ButtonSingle<GPIOPin> seq_btn { GPIOPin::newPin(port_a, 11) };
  volatile ButtonSingle<GPIOPin> run_btn { GPIOPin::newPin(port_c,  1) };
  volatile ButtonSingle<GPIOPin> l_btn   { GPIOPin::newPin(port_a,  8) };
  volatile ButtonSingle<GPIOPin> r_btn   { GPIOPin::newPin(port_a, 15) };

  volatile ButtonMatrix<GPIOPin, 4, GPIOPin, 4> btn_matrix {
    .in_pins = {
      GPIOPin::newPin(port_a,  4),
      GPIOPin::newPin(port_c,  4),
      GPIOPin::newPin(port_c,  6),
      GPIOPin::newPin(port_c,  7)
    },
    .out_pins = {
      GPIOPin::newPin(port_b, 11),
      GPIOPin::newPin(port_b, 10),
      GPIOPin::newPin(port_c,  2),
      GPIOPin::newPin(port_c,  3)
    }
  };

  volatile uint32_t state_bits = 0;
  std::function<void(AppBtnID, bool)> on_change;

  void init() {
    port_a.enable();
    port_b.enable();
    port_c.enable();

    seq_btn.pin.initInput(GPIOPullMode::UP, GPIOSpeedMode::HIGH);
    run_btn.pin.initInput(GPIOPullMode::UP, GPIOSpeedMode::HIGH);
    l_btn.pin.initInput(GPIOPullMode::UP, GPIOSpeedMode::HIGH);
    r_btn.pin.initInput(GPIOPullMode::UP, GPIOSpeedMode::HIGH);

    for (auto& in_pin : btn_matrix.in_pins) {
      in_pin.initInput(GPIOPullMode::NO, GPIOSpeedMode::HIGH);
    }
    for (auto& out_pin : btn_matrix.out_pins) {
      out_pin.initOutput(GPIOOutputMode::PUSHPULL, GPIOSpeedMode::HIGH);
    }

    btn_matrix.init();
  }

  // TODO: ボタンと対応するインデックスの関連づけ、もっとシンプルに定義できる様にしたい
  bool isOn(AppBtnID btn_id) {
    bool on = false;

    switch (btn_id) {
      case AppBtnID::OSC:
        on = btn_matrix.isOn(0, 0); break;
      case AppBtnID::PARAM:
        on = btn_matrix.isOn(1, 0); break;
      case AppBtnID::FILTER:
        on = btn_matrix.isOn(2, 0); break;
      case AppBtnID::EG:
        on = btn_matrix.isOn(3, 0); break;
      case AppBtnID::MOD:
        on = btn_matrix.isOn(0, 1); break;
      case AppBtnID::DELAY:
        on = btn_matrix.isOn(1, 1); break;
      case AppBtnID::REVERB:
        on = btn_matrix.isOn(2, 1); break;
      case AppBtnID::ARP:
        on = btn_matrix.isOn(3, 1); break;
      case AppBtnID::SAVE:
        on = btn_matrix.isOn(0, 2); break;
      case AppBtnID::LOAD:
        on = btn_matrix.isOn(1, 2); break;
      case AppBtnID::CLEAR:
        on = btn_matrix.isOn(2, 2); break;
      case AppBtnID::GLOBAL:
        on = btn_matrix.isOn(3, 2); break;
      case AppBtnID::SCALE:
        on = btn_matrix.isOn(0, 3); break;
      case AppBtnID::TRANS:
        on = btn_matrix.isOn(1, 3); break;
      case AppBtnID::STUTTER:
        on = btn_matrix.isOn(2, 3); break;
      case AppBtnID::LFO:
        on = btn_matrix.isOn(3, 3); break;
      case AppBtnID::SEQ:
        on = seq_btn.isOn(); break;
      case AppBtnID::RUN:
        on = run_btn.isOn(); break;
      case AppBtnID::L:
        on = l_btn.isOn(); break;
      case AppBtnID::R:
        on = r_btn.isOn(); break;
      default:
        break;
    }

    return on;
  }

  void process() {
    seq_btn.process();
    run_btn.process();
    l_btn.process();
    r_btn.process();
    btn_matrix.process();
    uint32_t new_bits = 0;
    for (uint8_t i = 0; i < static_cast<uint8_t>(AppBtnID::SIZE); ++i) {
      if (isOn(static_cast<AppBtnID>(i))) {
        new_bits |= (uint32_t)1 << i;
      }
    }
    if (state_bits != new_bits) {
      if (on_change) {
        uint32_t diff_bits = state_bits ^ new_bits;
        for (uint8_t i = 0; i < static_cast<uint8_t>(AppBtnID::SIZE); ++i) {
          if (diff_bits & ((uint32_t)1 << i)) {
            on_change(static_cast<AppBtnID>(i), !!(new_bits & ((uint32_t)1 << i)));
          }
        }
      }
      state_bits = new_bits;
    }
  }
};

#endif /* APP_BUTTON_H */
