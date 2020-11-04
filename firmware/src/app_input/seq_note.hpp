#ifndef N1GP_APP_INPUT_SEQ_NOTE_H
#define N1GP_APP_INPUT_SEQ_NOTE_H

#include <app_input/base.hpp>
#include "app_seq.h"

struct AppInputSeqNote {
  uint16_t _selected_steps = 0;

  inline void init() {
    app_screen.changeMode(AppScreenSeq {});
    seq.changeTrack(AppTrackType::note);
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }
  inline bool button(AppBtnID id, bool on) {
    uint8_t idx = static_cast<uint8_t>(id);
    if (idx < 16) {
      if (!on) {
        auto& track = seq.getTrack(AppTrackType::note);
        track.toggleActive(idx);
        seq.selected_steps = ((uint16_t)1 << idx);
        return true;
      }
    }
    switch(id) {
      default:
        break;
    }
    return false;
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    screen_mode.setTitle("SEQ:Note", 16);
  }
};

#endif /* N1GP_APP_INPUT_SEQ_NOTE_H */
