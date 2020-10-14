#ifndef N1GP_APP_INPUT_CLEAR_H
#define N1GP_APP_INPUT_CLEAR_H

#include <app_input/base.hpp>

struct AppInputClear {
  inline void init() {
    screen_set_mode(SCREEN_MODE_EDIT);
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void refresh() {
    screen_edit_set_title("CLEAR", 16);
  }
};

#endif /* N1GP_APP_INPUT_CLEAR_H */
