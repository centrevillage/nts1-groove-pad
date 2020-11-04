#ifndef N1GP_APP_INPUT_CLEAR_H
#define N1GP_APP_INPUT_CLEAR_H

#include <app_input/base.hpp>

struct AppInputClear {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("CLEAR", 16);
  }
};

#endif /* N1GP_APP_INPUT_CLEAR_H */
