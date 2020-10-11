#ifndef N1GP_APP_INPUT_LOAD_H
#define N1GP_APP_INPUT_LOAD_H

#include <app_input/base.hpp>

struct AppInputLoad {
  inline void init() {
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void refresh() {
    screen_edit_set_title("LOAD", 16);
  }
};

#endif /* N1GP_APP_INPUT_LOAD_H */
