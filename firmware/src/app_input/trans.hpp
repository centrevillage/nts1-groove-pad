#ifndef N1GP_APP_INPUT_TRANS_H
#define N1GP_APP_INPUT_TRANS_H

#include <app_input/base.hpp>

struct AppInputTrans {
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
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    screen_mode.setTitle("TRANSPOSE", 16);
  }
};

#endif /* N1GP_APP_INPUT_TRANS_H */
