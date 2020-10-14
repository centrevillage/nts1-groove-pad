#ifndef N1GP_APP_SCREEN_SEQ_H
#define N1GP_APP_SCREEN_SEQ_H

#include "app_screen/base.hpp"

struct AppScreenSeq {
  bool is_dirty = false;
  char _title_text[16];
  uint8_t _title_text_size = 0;
  volatile uint8_t _seq_step_values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  void init() {
    is_dirty = true;
  }

  void setSeqStepValue(uint8_t step_idx, uint8_t value) {
    _seq_step_values[step_idx] = value;
    is_dirty = true;
  }

  void draw(uint8_t* buffer) {
    if (is_dirty) {
      draw_fill_bg(buffer);

      uint8_t title_offset = (SCREEN_WIDTH - _title_text_size * 5) / 2;
      draw_text_small(buffer, _screen_edit_title_text, _screen_edit_title_text_size, 0, title_offset);

      draw_text_small(buffer, _screen_edit_title_text, _screen_edit_title_text_size, 0, title_offset);

      char str[3];
      for (uint8_t i = 0; i < 8; ++i) {
        text_12dec_from_note(str, _seq_step_values[i]);
        draw_text_medium(buffer, &(str[0]), 1, 2, i*16);
        draw_text_medium(buffer, &(str[1]), 1, 2, (i*16)+7);
        if (input_state.seq_selected_steps & ((uint16_t)1<<i)){
          draw_invert(buffer, 2, 15, 2, i*16);
        }
      }
      for (uint8_t i = 8; i < 16; ++i) {
        text_12dec_from_note(str, _seq_step_values[i]);
        draw_text_medium(buffer, &(str[0]), 1, 5, (i-8)*16);
        draw_text_medium(buffer, &(str[1]), 1, 5, ((i-8)*16)+7);
        if (input_state.seq_selected_steps & ((uint16_t)1<<i)){
          draw_invert(buffer, 2, 15, 5, i*16);
        }
      }

      is_dirty = 0;
    }
  }
};

#endif /* N1GP_APP_SCREEN_SEQ_H */
