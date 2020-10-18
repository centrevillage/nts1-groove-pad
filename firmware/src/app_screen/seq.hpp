#ifndef N1GP_APP_SCREEN_SEQ_H
#define N1GP_APP_SCREEN_SEQ_H

#include "app_screen/base.hpp"

struct AppScreenSeq {
  bool is_dirty = false;
  bool is_note_disp = true;
  char _title_text[16];
  uint8_t _title_text_size = 0;
  uint8_t _seq_step_values[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint16_t _seq_selected_steps = 0;

  void refreshLed() {
    for (uint8_t i = 0; i < 16; ++i) {
      if (seq.getStepTrig(seq.current_track_type, i)) {
        led_set(i, 1);
      } else {
        led_set(i, 0);
      }
    }
  }

  void init() {
    is_dirty = true;
    refreshLed();
  }

  void setSeqStepValue(uint8_t step_idx, uint8_t value) {
    _seq_step_values[step_idx] = value;
    is_dirty = true;
  }

  void selectOneStep(uint8_t step_idx) {
    seq.selected_steps = ((uint16_t)1 << step_idx);
  }

  void selectStep(uint8_t step_idx) {
    seq.selected_steps |= ((uint16_t)1 << step_idx);
  }

  void unselectStep(uint8_t step_idx) {
    seq.selected_steps &= ~((uint16_t)1 << step_idx);
  }

  void unselectAllSteps() {
    seq.selected_steps = 0;
  }

  void setTitle(const char* title_text, uint8_t len) {
    uint8_t i = 0;
    for (; i<16 && i<len && title_text[i]!=0; ++i) {
      _title_text[i] = title_text[i];
    }
    _title_text_size = i;
    is_dirty = true;
  }

  inline void textFromNote(char* str, uint8_t v) {
    if (is_note_disp) {
      text_12dec_from_note(str, v);
    } else {
      text_0x_from_uint8(str, v);
    }
  }

  void draw(uint8_t* buffer) {
    if (is_dirty) {
      draw_fill_bg(buffer);

      uint8_t title_offset = (SCREEN_WIDTH - _title_text_size * 5) / 2;
      draw_text_small(buffer, _title_text, _title_text_size, 0, title_offset);

      char str[3];
      for (uint8_t i = 0; i < 8; ++i) {
        textFromNote(str, _seq_step_values[i]);
        draw_text_medium(buffer, &(str[0]), 1, 2, i*16);
        draw_text_medium(buffer, &(str[1]), 1, 2, (i*16)+7);
        if (seq.selected_steps & ((uint16_t)1<<i)){
          draw_invert(buffer, 2, 15, 2, i*16);
        }
      }
      for (uint8_t i = 8; i < 16; ++i) {
        textFromNote(str, _seq_step_values[i]);
        draw_text_medium(buffer, &(str[0]), 1, 5, (i-8)*16);
        draw_text_medium(buffer, &(str[1]), 1, 5, ((i-8)*16)+7);
        if (seq.selected_steps & ((uint16_t)1<<i)){
          draw_invert(buffer, 2, 15, 5, i*16);
        }
      }

      refreshLed();

      is_dirty = 0;
    }
  }
};

#endif /* N1GP_APP_SCREEN_SEQ_H */
