#ifndef N1GP_APP_SCREEN_H
#define N1GP_APP_SCREEN_H

#include "app_screen/base.hpp"

#include "app_screen/edit.hpp"
#include "app_screen/debug.hpp"
#include "app_screen/seq.hpp"

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

  void changeMode(auto&& mode) {
    state.mode = mode;
    state.init();
  }

  void draw(uint8_t* buffer) {
    state.draw(buffer);
  }

  template<typename MODE_TYPE>
  MODE_TYPE& getMode() {
    return std::get<MODE_TYPE>(state.mode);
  }

  template<typename MODE_TYPE>
  bool isMode() {
    return std::holds_alternative<MODE_TYPE>(state.mode);
  }
};

extern AppScreen app_screen;

#endif /* N1GP_APP_SCREEN_H */
