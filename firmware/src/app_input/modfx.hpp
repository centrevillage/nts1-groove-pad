#ifndef N1GP_APP_INPUT_MODFX_H
#define N1GP_APP_INPUT_MODFX_H

#include <app_input/base.hpp>

using AppInputValueModfxTime =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::modfx_time, 0, 1023>,
    k_param_id_mod_time, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_MODFX_TIME // preset save
  >;
using AppInputValueModfxDepth =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::modfx_depth, 0, 1023>,
    k_param_id_mod_depth, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_MODFX_DEPTH // preset save
  >;
using AppInputValueModfxType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::modfx_type, 0, 15>,
    k_param_id_mod_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_MODFX_INDEX // preset save
  >;
struct AppInputModfx : AppInputIncTouchImpl<AppInputValueModfxTime, AppInputValueModfxDepth>, AppInputLrButtonImpl<AppInputValueModfxType, Nts1DefsSizeID::modfx_defs_size> {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("ModFX", 16);
    screen_mode.setType(modfx_defs[preset_state.modfx.index].name, PARAM_NAME_LEN);
    screen_mode.setParamName(0, "Time", 4);
    screen_mode.setParamName(1, "Depth", 5);
    screen_mode.setParamValue(0, preset_state.modfx.time);
    screen_mode.setParamValue(1, preset_state.modfx.depth);
  }
};


#endif /* N1GP_APP_INPUT_MODFX_H */
