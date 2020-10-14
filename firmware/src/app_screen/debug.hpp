#ifndef N1GP_APP_SCREEN_DEBUG_H
#define N1GP_APP_SCREEN_DEBUG_H

#include "app_screen/base.hpp"
#include "app_input.hpp"
#include "debug.h"

struct AppScreenDebug {
  void init() {
  }
  void draw(uint8_t* buffer) {
    draw_fill_bg(buffer);
    if (app_input.touch_bits) {
      for (uint8_t i=0;i<8;++i) {
        if (app_input.touch_bits & (1<<i)) {
          draw_touch_pad(buffer, (DrawPadType)i);
        }
      }
    }
    draw_text_medium(buffer, debug_text_get(), 32, 0, 32);
  }
};

#endif /* N1GP_APP_SCREEN_DEBUG_H */
