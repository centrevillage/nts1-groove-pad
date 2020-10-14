#ifndef N1GP_APP_SCREEN_H
#define N1GP_APP_SCREEN_H

#include <app_screen/base.hpp>

#include <app_screen/edit.hpp>
#include <app_screen/debug.hpp>
#include <app_screen/seq.hpp>

struct AppScreenState {
  std::variant<
    AppScreenEdit,
    AppScreenDebug,
    AppScreenSeq
  > mode = AppScreenEdit {};

  AppScreenMode currentMode() {
    return static_cast<AppScreenMode>(mode.index());
  }

  void init() {
    std::visit([=](auto& m) {
      m.init();
    }, mode);
  }

  void draw(uint8_t* buffer) {
    std::visit([=](auto& m) {
      m.draw(buffer);
    }, mode);
  }
};


struct AppScreen {
  AppScreenState state;

  void init() {
    state.mode = AppScreenDebug {};
    state.init();
  };

  void changeMode(AppScreenMode m) {
    state.changeMode(m);
  }

  void draw(uint8_t* buffer) {
    state.draw(buffer);
  }

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
};

#endif /* N1GP_APP_SCREEN_H */
