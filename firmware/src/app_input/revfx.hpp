#ifndef N1GP_APP_INPUT_REVFX_H
#define N1GP_APP_INPUT_REVFX_H

#include <app_input/base.hpp>

using AppInputValueRevfxTime =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::revfx_time, 0, 1023>,
    k_param_id_rev_time, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_REVFX_TIME // preset save
  >;
using AppInputValueRevfxDepth =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::revfx_depth, 0, 1023>,
    k_param_id_rev_depth, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_REVFX_DEPTH // preset save
  >;
using AppInputValueRevfxType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::revfx_type, 0, 15>,
    k_param_id_rev_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_REVFX_INDEX // preset save
  >;
struct AppInputRevfx : AppInputIncTouchImpl<AppInputValueRevfxTime, AppInputValueRevfxDepth>, AppInputLrButtonImpl<AppInputValueRevfxType, Nts1DefsSizeID::revfx_defs_size> {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("RevFX", 16);
    screen_mode.setType(revfx_defs[preset_state.revfx.index].name, PARAM_NAME_LEN);
    screen_mode.setParamName(0, "Time", 4);
    screen_mode.setParamName(1, "Depth", 5);
    screen_mode.setParamValue(0, preset_state.revfx.time);
    screen_mode.setParamValue(1, preset_state.revfx.depth);
  }
};


#endif /* N1GP_APP_INPUT_REVFX_H */
