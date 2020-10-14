#ifndef N1GP_APP_INPUT_STUTTER_H
#define N1GP_APP_INPUT_STUTTER_H

#include <app_input/base.hpp>

struct AppInputStutter {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("STUTTER", 16);
  }
};

#endif /* N1GP_APP_INPUT_STUTTER_H */
