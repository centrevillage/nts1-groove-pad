#include "screen.h"
#include "input.h"
#include "draw.h"
#include "text.h"

volatile ScreenMode _screen_mode = SCREEN_MODE_INPUT_DEBUG;
volatile ScreenMode _screen_mode_default = SCREEN_MODE_INPUT_DEBUG;
volatile ScreenMode _screen_is_dirty = 1;

volatile char _screen_edit_title_text[16];
volatile uint8_t _screen_edit_title_text_size = 0;
volatile char _screen_edit_type_text[16];
volatile uint8_t _screen_edit_type_text_size = 0;
volatile char _screen_edit_hint_text[32];
volatile uint8_t _screen_edit_hint_text_size = 0;
volatile char _screen_edit_page_text[3];
volatile uint8_t _screen_edit_page_text_size = 0;
volatile char _screen_edit_param_name_text[2][8];
volatile uint8_t _screen_edit_param_name_text_size[2] = {0, 0};
volatile char _screen_edit_param_value_text[2][8];
volatile uint8_t _screen_edit_param_value_text_size[2] = {0, 0};

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

void screen_draw_edit(uint8_t* buffer) {
  if (_screen_is_dirty) {
    draw_fill_bg(buffer);
    uint8_t title_offset = (SCREEN_WIDTH - _screen_edit_title_text_size * 5) / 2;
    draw_text_small(buffer, _screen_edit_title_text, _screen_edit_title_text_size, 0, title_offset);
    //uint8_t page_text_offset = (SCREEN_WIDTH - _screen_edit_page_text_size * 5) / 2;
    //draw_text_small(buffer, _screen_edit_page_text, _screen_edit_page_text_size, 7, page_text_offset);

    uint8_t type_text_offset  = (SCREEN_WIDTH - _screen_edit_type_text_size * 8) / 2;
    draw_text_medium(buffer, _screen_edit_type_text, _screen_edit_type_text_size, 1, type_text_offset);

    uint8_t param_name_l_text_offset = ((SCREEN_WIDTH / 2) - (_screen_edit_param_name_text_size[0]*8))/2;
    uint8_t param_name_r_text_offset = ((SCREEN_WIDTH / 2) - (_screen_edit_param_name_text_size[1]*8))/2 + SCREEN_WIDTH/2;
    draw_text_medium(buffer, _screen_edit_param_name_text[0], _screen_edit_param_name_text_size[0], 3, param_name_l_text_offset);
    draw_text_medium(buffer, _screen_edit_param_name_text[1], _screen_edit_param_name_text_size[1], 3, param_name_r_text_offset);
    draw_text_medium(buffer, _screen_edit_param_value_text[0], _screen_edit_param_value_text_size[0], 5, 0);
    draw_text_medium(buffer, _screen_edit_param_value_text[1], _screen_edit_param_value_text_size[1], 5, SCREEN_WIDTH/2);

    _screen_is_dirty = 0;
  }
}

void screen_draw_input_debug(uint8_t* buffer) {
  draw_fill_bg(buffer);
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
  screen_draw_edit,
  screen_draw_input_debug,
};

void screen_draw(uint8_t* buffer) {
  _screen_mode_to_function[_screen_mode](buffer);
}

void screen_edit_clear() {
  _screen_edit_title_text_size = 0;
  _screen_edit_type_text_size = 0;
  _screen_edit_hint_text_size = 0;
  _screen_edit_page_text_size = 0;
  _screen_edit_param_name_text_size[0] = 0;
  _screen_edit_param_name_text_size[1] = 0;
  _screen_edit_param_value_text_size[0] = 0;
  _screen_edit_param_value_text_size[1] = 0;
}

void screen_edit_set_title(const char* title_text, uint8_t len) {
  uint8_t i = 0;
  for (; i<16 && i<len && title_text[i]!=0; ++i) {
    _screen_edit_title_text[i] = title_text[i];
  }
  _screen_edit_title_text_size = i;
  _screen_is_dirty = 1;
}

void screen_edit_set_type(const char* type_text, uint8_t len) {
  uint8_t i = 0;
  for (; i<16 && i<len && type_text[i]!=0; ++i) {
    _screen_edit_type_text[i] = type_text[i];
  }
  _screen_edit_type_text_size = i;
  _screen_is_dirty = 1;
}

void screen_edit_set_hint(const char* hint_text, uint8_t len) {
  uint8_t i = 0;
  for (;i<32&&i<len&&hint_text[i]!=0;++i) {
    _screen_edit_hint_text[i] = hint_text[i];
  }
  _screen_edit_hint_text_size = i;
  _screen_is_dirty = 1;
}

void screen_edit_set_page(uint8_t current_page, uint8_t page_size) {
  _screen_edit_page_text[0] = (char)((current_page % 10) + 48);
  _screen_edit_page_text[1] = '/';
  _screen_edit_page_text[2] = (char)((page_size % 10) + 48);
  _screen_edit_page_text_size = 3;
  _screen_is_dirty = 1;
}

void screen_edit_set_param_name(uint8_t is_right, const char* param_name, uint8_t len) {
  uint8_t i = 0;
  for (;i<8&&i<len&&param_name[i]!=0;++i) {
    _screen_edit_param_name_text[is_right][i] = param_name[i];
  }
  _screen_edit_param_name_text_size[is_right] = i;
  _screen_is_dirty = 1;
}

void screen_edit_set_param_value(uint8_t is_right, uint16_t value) {
  char tmp[8];
  uint8_t size = text_from_uint16(tmp, value);
  uint8_t is_zero = 1;
  uint8_t i=0;
  for (;i<size;++i) {
    if (is_zero && tmp[i] == '0') {
      _screen_edit_param_value_text[is_right][i] = ' ';
    } else {
      _screen_edit_param_value_text[is_right][i] = tmp[i];
      is_zero = 0;
    }
  }
  if (is_zero) {
    _screen_edit_param_value_text[is_right][i-1] = '0';
  }
  _screen_edit_param_value_text_size[is_right] = i;
  _screen_is_dirty = 1;
}


