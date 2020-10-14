#ifndef N1GP_APP_SCREEN_EDIT_H
#define N1GP_APP_SCREEN_EDIT_H

#include "app_screen/base.hpp"

struct AppScreenEdit {
  bool is_dirty = false;

  char _title_text[16];
  uint8_t _title_text_size = 0;
  char _type_text[16];
  uint8_t _type_text_size = 0;
  char _hint_text[32];
  uint8_t _hint_text_size = 0;
  char _page_text[3];
  uint8_t _page_text_size = 0;
  char _param_name_text[2][8];
  uint8_t _param_name_text_size[2] = {0, 0};
  char _param_value_text[2][8];
  uint8_t _param_value_text_size[2] = {0, 0};

  void init() {
    clear();
  }
  void setTitle(const char* title_text, uint8_t len) {
    uint8_t i = 0;
    for (; i<16 && i<len && title_text[i]!=0; ++i) {
      _title_text[i] = title_text[i];
    }
    _title_text_size = i;
    is_dirty = true;
  }
  void setType(const char* type_text, uint8_t len) {
    uint8_t i = 0;
    for (; i<16 && i<len && type_text[i]!=0; ++i) {
      _type_text[i] = type_text[i];
    }
    _type_text_size = i;
    is_dirty = true;
  }
  void setPage(uint8_t current_page, uint8_t page_size) {
    _page_text[0] = (char)((current_page % 10) + 48);
    _page_text[1] = '/';
    _page_text[2] = (char)((page_size % 10) + 48);
    _page_text_size = 3;
    is_dirty = true;
  }
  void setParamName(uint8_t is_right, const char* param_name, uint8_t len) {
    uint8_t i = 0;
    for (;i<8&&i<len&&param_name[i]!=0;++i) {
      _param_name_text[is_right][i] = param_name[i];
    }
    _param_name_text_size[is_right] = i;
    is_dirty = true;
  }
  void setParamValue(uint8_t is_right, uint16_t value) {
    char tmp[8];
    uint8_t size = text_from_uint16(tmp, value);
    uint8_t is_zero = 1;
    uint8_t i=0;
    for (;i<size;++i) {
      if (is_zero && tmp[i] == '0') {
        _param_value_text[is_right][i] = ' ';
      } else {
        _param_value_text[is_right][i] = tmp[i];
        is_zero = 0;
      }
    }
    if (is_zero) {
      _param_value_text[is_right][i-1] = '0';
    }
    _param_value_text_size[is_right] = i;
    is_dirty = true;
  }
  void setParamValueText(uint8_t is_right, const char* text, uint8_t len) {
    uint8_t i = 0;
    for (; i < 8 && i < len && text[i] != 0; ++i) {
      _param_value_text[is_right][i] = text[i];
    }
    _param_value_text_size[is_right] = i;
    is_dirty = true;
  }
  void setHint(const char* hint_text, uint8_t len) {
    uint8_t i = 0;
    for (;i<32&&i<len&&hint_text[i]!=0;++i) {
      _hint_text[i] = hint_text[i];
    }
    _hint_text_size = i;
    is_dirty = true;
  }
  void clear() {
    _title_text_size = 0;
    _type_text_size = 0;
    _hint_text_size = 0;
    _page_text_size = 0;
    _param_name_text_size[0] = 0;
    _param_name_text_size[1] = 0;
    _param_value_text_size[0] = 0;
    _param_value_text_size[1] = 0;
  }

  void draw(uint8_t* buffer) {
    if (is_dirty) {
      draw_fill_bg(buffer);
    }
  }
};

#endif /* N1GP_APP_SCREEN_EDIT_H */
