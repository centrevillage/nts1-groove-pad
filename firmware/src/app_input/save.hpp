#ifndef N1GP_APP_INPUT_SAVE_H
#define N1GP_APP_INPUT_SAVE_H

#include <app_input/base.hpp>

struct AppInputSave {
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
    screen_edit_set_title("SAVE", 16);
  }
};

#endif /* N1GP_APP_INPUT_SAVE_H */
