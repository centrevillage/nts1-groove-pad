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
    screen_set_mode(SCREEN_MODE_EDIT);
  }
  inline void refresh() {
    screen_edit_set_title("ModFX", 16);
    screen_edit_set_type(modfx_defs[preset_state.modfx.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Time", 4);
    screen_edit_set_param_name(1, "Depth", 5);
    screen_edit_set_param_value(0, preset_state.modfx.time);
    screen_edit_set_param_value(1, preset_state.modfx.depth);
  }
};


#endif /* N1GP_APP_INPUT_MODFX_H */
