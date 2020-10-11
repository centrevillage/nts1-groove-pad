#ifndef N1GP_APP_INPUT_H
#define N1GP_APP_INPUT_H

#include <app_input/base.hpp>

#include <app_input/osc.hpp>
#include <app_input/custom.hpp>
#include <app_input/filter.hpp>
#include <app_input/ampeg.hpp>
#include <app_input/modfx.hpp>
#include <app_input/delfx.hpp>
#include <app_input/revfx.hpp>
#include <app_input/arp.hpp>
#include <app_input/seq_select.hpp>

// TODO:
struct AppInputSave : AppInputNullImpl { };
struct AppInputLoad : AppInputNullImpl { };
struct AppInputClear : AppInputNullImpl { };
struct AppInputGlobal : AppInputNullImpl { };
struct AppInputScale : AppInputNullImpl { };
struct AppInputTrans : AppInputNullImpl { };
struct AppInputStutter : AppInputNullImpl { };
struct AppInputLfo : AppInputNullImpl { };

struct AppInputSeqNote : AppInputNullImpl { };
struct AppInputSeqOsc : AppInputNullImpl { };
struct AppInputSeqCustom : AppInputNullImpl { };
struct AppInputSeqFilter : AppInputNullImpl { };
struct AppInputSeqAmpeg : AppInputNullImpl { };
struct AppInputSeqModfx : AppInputNullImpl { };
struct AppInputSeqDelfx : AppInputNullImpl { };
struct AppInputSeqRevfx : AppInputNullImpl { };
struct AppInputSeqArp : AppInputNullImpl { };
struct AppInputSeqScale : AppInputNullImpl { };
struct AppInputSeqTrans : AppInputNullImpl { };
struct AppInputSeqStutter : AppInputNullImpl { };
struct AppInputSeqLfo : AppInputNullImpl { };

struct AppInputModeState {
  std::variant<
    AppInputOsc,
    AppInputCustom,
    AppInputFilter,
    AppInputAmpeg,
    AppInputModfx,
    AppInputDelfx,
    AppInputRevfx,
    AppInputArp,
    AppInputSave,
    AppInputLoad,
    AppInputClear,
    AppInputGlobal,
    AppInputScale,
    AppInputTrans,
    AppInputStutter,
    AppInputLfo,

    AppInputSeqSelect,
    AppInputSeqNote,
    AppInputSeqOsc,
    AppInputSeqCustom,
    AppInputSeqFilter,
    AppInputSeqAmpeg,
    AppInputSeqModfx,
    AppInputSeqDelfx,
    AppInputSeqRevfx,
    AppInputSeqArp,
    AppInputSeqScale,
    AppInputSeqTrans,
    AppInputSeqStutter,
    AppInputSeqLfo
  > mode = AppInputOsc {};

  void change(AppInputMode m) {
    switch (m) {
      case AppInputMode::osc:
        mode = AppInputOsc {};
        break;
      case AppInputMode::custom:
        mode = AppInputCustom {};
        break;
      case AppInputMode::filter:
        mode = AppInputFilter {};
        break;
      case AppInputMode::ampeg:
        mode = AppInputAmpeg {};
        break;
      case AppInputMode::modfx:
        mode = AppInputModfx {};
        break;
      case AppInputMode::delfx:
        mode = AppInputDelfx {};
        break;
      case AppInputMode::revfx:
        mode = AppInputRevfx {};
        break;
      case AppInputMode::arp:
        mode = AppInputArp {};
        break;
      case AppInputMode::save:
        mode = AppInputSave {};
        break;
      case AppInputMode::load:
        mode = AppInputLoad {};
        break;
      case AppInputMode::clear:
        mode = AppInputClear {};
        break;
      case AppInputMode::global:
        mode = AppInputGlobal {};
        break;
      case AppInputMode::scale:
        mode = AppInputScale {};
        break;
      case AppInputMode::trans:
        mode = AppInputTrans {};
        break;
      case AppInputMode::stutter:
        mode = AppInputStutter {};
        break;
      case AppInputMode::lfo:
        mode = AppInputLfo {};
        break;
      case AppInputMode::seq_select:
        mode = AppInputSeqSelect {};
        break;
      case AppInputMode::seq_note:
        mode = AppInputSeqNote {};
        break;
      case AppInputMode::seq_osc:
        mode = AppInputSeqOsc {};
        break;
      case AppInputMode::seq_custom:
        mode = AppInputSeqCustom {};
        break;
      case AppInputMode::seq_filter:
        mode = AppInputSeqFilter {};
        break;
      case AppInputMode::seq_ampeg:
        mode = AppInputSeqAmpeg {};
        break;
      case AppInputMode::seq_modfx:
        mode = AppInputSeqModfx {};
        break;
      case AppInputMode::seq_delfx:
        mode = AppInputSeqDelfx {};
        break;
      case AppInputMode::seq_revfx:
        mode = AppInputSeqRevfx {};
        break;
      case AppInputMode::seq_arp:
        mode = AppInputSeqArp {};
        break;
      case AppInputMode::seq_scale:
        mode = AppInputSeqScale {};
        break;
      case AppInputMode::seq_trans:
        mode = AppInputSeqTrans {};
        break;
      case AppInputMode::seq_stutter:
        mode = AppInputSeqStutter {};
        break;
      case AppInputMode::seq_lfo:
        mode = AppInputSeqLfo {};
        break;
      default:
        break;
    }
    init();
  }

  void init() {
    std::visit([](auto& m) {
      m.init();
    }, mode);
  }

  void refresh() {
    std::visit([](auto& m) {
      m.refresh();
    }, mode);
  }

  void touchOnChange(AppTouchPadID id, int16_t inc_value) {
    std::visit([=](auto& m) {
      if (id == AppTouchPadID::L) {
        m.incValueL(inc_value);
      } else {
        m.incValueR(inc_value);
      }
    }, mode);
  }

  bool button(AppBtnID id, bool on) {
    return std::visit([=](auto& m) {
      return m.button(id, on);
    }, mode);
  }
};

struct AppInput {
  AppButtons buttons;
  AppTouch touch;
  uint8_t touch_bits = 0;
  AppInputMode current_mode = AppInputMode::osc;
  AppInputMode next_mode = AppInputMode::seq_note;

  AppInputModeState state;

  void init() {
    state.init();
    buttons.init();
    buttons.on_change = [this](AppBtnID id, bool on){
      button(id, on);
    };

    touch.init();
    touch.on_acquisition_end = [this](uint8_t bits) {
      touch_bits = bits;
    };
    touch.on_change = [this](AppTouchPadID id, int16_t inc_value) {
      state.touchOnChange(id, inc_value);
    };
  }

  void process() {
    buttons.process();
    touch.process();
  }

  inline bool isSeqPressed(uint32_t state_bits) {
    return state_bits & (1<<static_cast<uint32_t>(AppBtnID::SEQ));
  }

  inline void backToEditMode() {
    refresh();
  }

  void refresh() {
    screen_edit_clear();
    state.refresh();
  }

  void changeMode(AppInputMode mode) {
    current_mode = mode;
    state.change(mode);
    refresh();
  }

  inline void button(AppBtnID id, bool on) {
    if (state.button(id, on)) {
      refresh();
      return;
    }
    if (app_input_is_seq_mode(current_mode)) {
      if (id == AppBtnID::SEQ) {
        backToEditMode();
      }
    } else if (isSeqPressed(buttons.state_bits)) {
      next_mode = AppInputMode::seq_note;
      switch(id) {
        case AppBtnID::OSC:
          if (on) {
            next_mode = AppInputMode::seq_osc;
          }
          break;
        case AppBtnID::PARAM:
          if (on) {
            next_mode = AppInputMode::seq_custom;
          }
          break;
        case AppBtnID::FILTER:
          if (on) {
            next_mode = AppInputMode::seq_filter;
          }
          break;
        case AppBtnID::EG:
          if (on) {
            next_mode = AppInputMode::seq_ampeg;
          }
          break;
        case AppBtnID::MOD:
          if (on) {
            next_mode = AppInputMode::seq_modfx;
          }
          break;
        case AppBtnID::DELAY:
          if (on) {
            next_mode = AppInputMode::seq_delfx;
          }
          break;
        case AppBtnID::REVERB:
          if (on) {
            next_mode = AppInputMode::seq_revfx;
          }
          break;
        case AppBtnID::ARP:
          if (on) {
            next_mode = AppInputMode::seq_arp;
          }
          break;
        case AppBtnID::SAVE: // save
          break;
        case AppBtnID::LOAD: // load
          break;
        case AppBtnID::CLEAR: // clear
          break;
        case AppBtnID::GLOBAL: // global
          break;
        case AppBtnID::SCALE:
          break;
        case AppBtnID::TRANS:
          break;
        case AppBtnID::STUTTER:
          if (on) {
            next_mode = AppInputMode::seq_stutter;
          }
          break;
        case AppBtnID::LFO:
          if (on) {
            next_mode = AppInputMode::seq_lfo;
          }
          break;
        case AppBtnID::SEQ:
          if (on) {
            changeMode(AppInputMode::seq_select);
          }
          break;
        case AppBtnID::RUN:
          break;
        case AppBtnID::L:
          break;
        case AppBtnID::R:
          break;
        default:
          break;
      }
    } else {
      switch(id) {
        case AppBtnID::OSC:
          if (on) {
            changeMode(AppInputMode::osc);
          }
          break;
        case AppBtnID::PARAM:
          if (on) {
            changeMode(AppInputMode::custom);
          }
          break;
        case AppBtnID::FILTER:
          if (on) {
            changeMode(AppInputMode::filter);
          }
          break;
        case AppBtnID::EG:
          if (on) {
            changeMode(AppInputMode::ampeg);
          }
          break;
        case AppBtnID::MOD:
          if (on) {
            changeMode(AppInputMode::modfx);
          }
          break;
        case AppBtnID::DELAY:
          if (on) {
            changeMode(AppInputMode::delfx);
          }
          break;
        case AppBtnID::REVERB:
          if (on) {
            changeMode(AppInputMode::revfx);
          }
          break;
        case AppBtnID::ARP:
          if (on) {
            changeMode(AppInputMode::arp);
          }
          break;
        case AppBtnID::SAVE:
          if (on) {
            changeMode(AppInputMode::save);
          }
          break;
        case AppBtnID::LOAD:
          if (on) {
            changeMode(AppInputMode::load);
          }
          break;
        case AppBtnID::CLEAR:
          if (on) {
            changeMode(AppInputMode::clear);
          }
          break;
        case AppBtnID::GLOBAL:
          if (on) {
            changeMode(AppInputMode::global);
          }
          break;
        case AppBtnID::SCALE:
          if (on) {
            changeMode(AppInputMode::scale);
          }
          break;
        case AppBtnID::TRANS:
          if (on) {
            changeMode(AppInputMode::trans);
          }
          break;
        case AppBtnID::STUTTER:
          if (on) {
            changeMode(AppInputMode::stutter);
          }
          break;
        case AppBtnID::LFO:
          if (on) {
            changeMode(AppInputMode::lfo);
          }
          break;
        case AppBtnID::SEQ:
          if (!on) {
            if (app_input_is_seq_mode(next_mode)) {
              changeMode(next_mode);
            }
          }
          break;
        case AppBtnID::RUN:
          if (seq.run_state) {
            seq.stop();
            led_set_run(0);
          } else {
            seq.start();
            led_set_run(1);
          }
          break;
        case AppBtnID::L:
          break;
        case AppBtnID::R:
          break;
        default:
          break;
      }
    }
  }
};

extern AppInput app_input;

#endif /* N1GP_APP_INPUT_H */
