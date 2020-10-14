/*
 * レイアウト描画ユーティリティ
 */
#ifndef __N1GP_SCREEN_H__
#define __N1GP_SCREEN_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SCREEN_MODE_EDIT = 0,
  SCREEN_MODE_INPUT_DEBUG,
  SCREEN_MODE_SEQ_NOTE,

  SCREEN_MODE_SIZE
} ScreenMode;

void screen_setup();
void screen_set_mode(ScreenMode screen_mode);
void screen_set_default(ScreenMode screen_mode);
void screen_back_to_default();
void screen_draw(uint8_t* buffer);
void screen_set_dirty();

// SCREEN_MODE_EDIT の時の表示コマンド
// parameter 表示は1ページあたり2
void screen_edit_set_title(const char* title_text, uint8_t len);
void screen_edit_set_type(const char* type_text, uint8_t len);
void screen_edit_set_page(uint8_t current_page, uint8_t page_size);
void screen_edit_set_param_name(uint8_t is_right, const char* param_name, uint8_t len);
// TODO: value_type の扱い
void screen_edit_set_param_value(uint8_t is_right, uint16_t value);
void screen_edit_set_param_value_text(uint8_t is_right, const char* text, uint8_t len);
void screen_edit_set_hint(const char* hint_text, uint8_t len);
void screen_edit_clear();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_SCREEN_H__ */

