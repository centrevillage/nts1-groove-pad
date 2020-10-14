#ifndef N1GP_APP_INPUT_OSC_H
#define N1GP_APP_INPUT_OSC_H

#include "app_input/base.hpp"

using AppInputValueOscShiftShape =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_shift_shape, 0, 1023>,
    k_param_id_osc_shift_shape, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_SHIFT_SHAPE // preset save
  >;
using AppInputValueOscShape =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_shape, 0, 1023>,
    k_param_id_osc_shape, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_SHAPE // preset save
  >;
using AppInputValueOscType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_type, 0, 15>,
    k_param_id_osc_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_INDEX // preset save
  >;
struct AppInputOsc : AppInputIncTouchImpl<AppInputValueOscShiftShape, AppInputValueOscShape>, AppInputLrButtonImpl<AppInputValueOscType, Nts1DefsSizeID::osc_defs_size> {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("OSC", 16);
    screen_mode.setType(osc_defs[preset_state.osc.index].name, PARAM_NAME_LEN);
    screen_mode.setParamName(0, "ShiftSh", 7);
    screen_mode.setParamName(1, "Shape", 5);
    screen_mode.setParamValue(0, preset_state.osc.shift_shape);
    screen_mode.setParamValue(1, preset_state.osc.shape);
  };
};


#endif /* N1GP_APP_INPUT_OSC_H */
