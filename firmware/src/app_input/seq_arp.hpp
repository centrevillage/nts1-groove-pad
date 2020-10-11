#ifndef N1GP_APP_INPUT_SEQ_ARP_H
#define N1GP_APP_INPUT_SEQ_ARP_H

#include <app_input/base.hpp>

struct AppInputSeqArp {
  inline void init() {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
    screen_edit_set_title("SEQ:ARP", 16);
  }
};

#endif /* N1GP_APP_INPUT_SEQ_ARP_H */
