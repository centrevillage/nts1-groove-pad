#ifndef N1GP_APP_INPUT_GLOBAL_H
#define N1GP_APP_INPUT_GLOBAL_H

#include <app_input/base.hpp>

struct AppInputGlobal {
  inline void init() {
    screen_set_mode(SCREEN_MODE_EDIT);
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
    screen_edit_set_title("GLOBAL", 16);
  }
};

#endif /* N1GP_APP_INPUT_GLOBAL_H */
