#ifndef N1GP_APP_INPUT_SEQ_STUTTER_H
#define N1GP_APP_INPUT_SEQ_STUTTER_H

#include <app_input/base.hpp>

struct AppInputSeqStutter {
  inline void init() {
    app_screen.changeMode(AppScreenSeq {});
    seq.changeTrack(AppTrackType::stutter);
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenSeq>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenSeq>();
    screen_mode.setTitle("SEQ:Stutter", 16);
  }
};

#endif /* N1GP_APP_INPUT_SEQ_STUTTER_H */
