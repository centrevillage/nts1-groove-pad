#ifndef N1GP_APP_INPUT_SEQ_NOTE_H
#define N1GP_APP_INPUT_SEQ_NOTE_H

#include <app_input/base.hpp>
#include "app_seq.h"

struct AppInputSeqNote {
  enum class ParamMode : uint8_t {
    pitch = 0,
    velocity,
    gate_length
  };
  ParamMode param_mode = ParamMode::pitch;

  inline void init() {
    app_screen.changeMode(AppScreenSeq {});
    app_touch.setSteps(2, 2);
    seq.changeTrack(AppTrackType::note);
  }
  inline void setNoteStepValues() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    auto& track = seq.getTrack(AppTrackType::note);
    for (uint8_t i = 0; i < 16; ++i) {
      screen_mode.setSeqStepValue(i, (uint8_t)track.values[i].r_value);
    }
  }
  inline void setVelocityStepValues() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    auto& track = seq.getTrack(AppTrackType::note);
    for (uint8_t i = 0; i < 16; ++i) {
      screen_mode.setSeqStepValue(i, (uint8_t)track.values[i].l_value);
    }
  }
  inline void setGateLenStepValues() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    auto& track = seq.getTrack(AppTrackType::note);
    for (uint8_t i = 0; i < 16; ++i) {
      screen_mode.setSeqStepValue(i, (uint8_t)track.values[i].page);
    }
  }
  inline void setStepValues() {
    switch(param_mode) {
      case ParamMode::pitch:
        setNoteStepValues();
        break;
      case ParamMode::velocity:
        setVelocityStepValues();
        break;
      case ParamMode::gate_length:
        setGateLenStepValues();
        break;
      default:
        break;
    }
  }
  inline void touch(uint8_t touch_idx, bool on) {
    if (on) {
      if (AppTouch::is_left_bit(1 << touch_idx)) {
        if (param_mode != ParamMode::velocity) {
          param_mode = ParamMode::velocity;
          setVelocityStepValues();
        }
      } else {
        if (param_mode != ParamMode::pitch) {
          param_mode = ParamMode::pitch;
          setNoteStepValues();
        }
      }
    }
  }
  inline bool button(AppBtnID id, bool on) {
    auto& track = seq.getTrack(AppTrackType::note);
    uint8_t idx = static_cast<uint8_t>(id);
    if (idx < 16) {
      if (!on) {
        track.toggleActive(idx);
        seq.selected_steps = ((uint16_t)1 << idx);
        return true;
      }
    }
    if (on) {
      switch(id) {
        case AppBtnID::L:
          if (param_mode != ParamMode::gate_length) {
            param_mode = ParamMode::gate_length;
          }
          for (uint8_t i = 0; i < 16; ++i) {
            if (seq.selected_steps & (1 << i)) {
              track.values[i].page = std::clamp<int16_t>(track.values[i].page - 1, 0, 8);// gate length 
            }
          }
          setStepValues();
          return true;
        case AppBtnID::R:
          if (param_mode != ParamMode::gate_length) {
            param_mode = ParamMode::gate_length;
          }
          for (uint8_t i = 0; i < 16; ++i) {
            if (seq.selected_steps & (1 << i)) {
              track.values[i].page = std::clamp<int16_t>(track.values[i].page + 1, 0, 11);// gate length
            }
          }
          setStepValues();
          return true;
        default:
          break;
      }
    }
    return false;
  }
  inline void incValueL(int16_t inc_value) {
    auto& track = seq.getTrack(AppTrackType::note);
    for (uint8_t i = 0; i < 16; ++i) {
      if (seq.selected_steps & (1 << i)) {
        track.values[i].l_value = std::clamp<int16_t>(track.values[i].l_value + inc_value, 0, 127);// velocity
      }
    }
    setStepValues();
  }
  inline void incValueR(int16_t inc_value) {
    auto& track = seq.getTrack(AppTrackType::note);
    for (uint8_t i = 0; i < 16; ++i) {
      if (seq.selected_steps & (1 << i)) {
        track.values[i].r_value = std::clamp<int16_t>(track.values[i].r_value + inc_value, 0, 127);// pitch
      }
    }
    setStepValues();
  }
  inline void setScreenTitle(auto& screen_mode) {
    char title[16] = "SEQ:Note:";
    char* p = title + 9; 
    switch(param_mode) {
      case ParamMode::pitch:
        *(p++) = 'P';
        *(p++) = 'i';
        *(p++) = 't';
        *(p++) = 'c';
        *(p++) = 'h';
        break;
      case ParamMode::velocity:
        *(p++) = 'V';
        *(p++) = 'e';
        *(p++) = 'l';
        *(p++) = 'o';
        break;
      case ParamMode::gate_length:
        *(p++) = 'L';
        *(p++) = 'e';
        *(p++) = 'n';
        break;
      default:
        break;
    }
    screen_mode.setTitle(title, 16);
  };
  inline void refresh() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    setScreenTitle(screen_mode);
    setStepValues();
  }
};

#endif /* N1GP_APP_INPUT_SEQ_NOTE_H */
