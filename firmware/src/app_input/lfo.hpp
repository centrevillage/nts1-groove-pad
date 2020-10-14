#ifndef N1GP_APP_INPUT_LFO_H
#define N1GP_APP_INPUT_LFO_H

#include <app_input/base.hpp>

struct AppInputLfo {
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
    screen_edit_set_title("LFO", 16);
  }
};

#endif /* N1GP_APP_INPUT_LFO_H */
