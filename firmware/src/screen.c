#include "screen.h"
#include "input.h"
#include "draw.h"

static volatile ScreenMode _screen_mode = SCREEN_MODE_INPUT_DEBUG;
static volatile ScreenMode _screen_mode_default = SCREEN_MODE_INPUT_DEBUG;
static volatile ScreenMode _screen_is_dirty = 1;

void screen_setup() {
  _screen_mode = SCREEN_MODE_INPUT_DEBUG;
  _screen_mode_default = SCREEN_MODE_INPUT_DEBUG;
  _screen_is_dirty = 1;
}

void screen_set_mode(ScreenMode screen_mode) {
  _screen_mode = screen_mode;
}

void screen_set_default(ScreenMode screen_mode) {
  _screen_mode_default = screen_mode;
}

void screen_back_to_default() {
  _screen_mode = _screen_mode_default;
}

void screen_set_dirty() {
  _screen_is_dirty = 1;
}

void screen_draw_osc(uint8_t* buffer) {
  if (_screen_is_dirty) {

    _screen_is_dirty = 0;
  }
}

void screen_draw_filter(uint8_t* buffer) {
}

void screen_draw_eg(uint8_t* buffer) {
}

void screen_draw_mod(uint8_t* buffer) {
}

void screen_draw_delay(uint8_t* buffer) {
}

void screen_draw_reverb(uint8_t* buffer) {
}

void screen_draw_lfo(uint8_t* buffer) {
}

void screen_draw_seq(uint8_t* buffer) {
}

void screen_draw_save(uint8_t* buffer) {
}

void screen_draw_load(uint8_t* buffer) {
}

void screen_draw_clear(uint8_t* buffer) {
}

void screen_draw_scale(uint8_t* buffer) {
}

void screen_draw_trans(uint8_t* buffer) {
}

void screen_draw_stutter(uint8_t* buffer) {
}

void screen_draw_slide(uint8_t* buffer) {
}

void screen_draw_rand(uint8_t* buffer) {
}

void screen_draw_input_debug(uint8_t* buffer) {
  oled_draw_fill_bg();
  if (input_state.touch_bits) {
    for (uint8_t i=0;i<8;++i) {
      if (input_state.touch_bits & (1<<i)) {
        draw_touch_pad(buffer, (DrawPadType)i);
      }
    }
  }
  draw_text_medium(buffer, debug_text_get(), 32, 0, 32);
}

typedef void (*ScreenModeFunction)(uint8_t* buffer);
static const ScreenModeFunction _screen_mode_to_function[SCREEN_MODE_SIZE] = {
  screen_draw_osc,
  screen_draw_filter,
  screen_draw_eg,
  screen_draw_mod,
  screen_draw_delay,
  screen_draw_reverb,
  screen_draw_lfo,
  screen_draw_seq,
  screen_draw_save,
  screen_draw_load,
  screen_draw_clear,
  screen_draw_scale,
  screen_draw_trans,
  screen_draw_stutter,
  screen_draw_slide,
  screen_draw_rand,
  screen_draw_input_debug,
};

void screen_draw(uint8_t* buffer) {
  _screen_mode_to_function[_screen_mode](buffer);
}

