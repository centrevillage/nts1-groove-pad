#ifndef N1GP_APP_INPUT_DELFX_H
#define N1GP_APP_INPUT_DELFX_H

#include <app_input/base.hpp>

using AppInputValueDelfxTime =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::delfx_time, 0, 1023>,
    k_param_id_del_time, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_DELFX_TIME // preset save
  >;
using AppInputValueDelfxDepth =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::delfx_depth, 0, 1023>,
    k_param_id_del_depth, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_DELFX_DEPTH // preset save
  >;
using AppInputValueDelfxType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::delfx_type, 0, 15>,
    k_param_id_del_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_DELFX_INDEX // preset save
  >;
struct AppInputDelfx : AppInputIncTouchImpl<AppInputValueDelfxTime, AppInputValueDelfxDepth>, AppInputLrButtonImpl<AppInputValueDelfxType, Nts1DefsSizeID::delfx_defs_size> {
  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }
  inline void refresh() {
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("DelFX", 16);
    screen_mode.setType(delfx_defs[preset_state.delfx.index].name, PARAM_NAME_LEN);
    screen_mode.setParamName(0, "Time", 4);
    screen_mode.setParamName(1, "Depth", 5);
    screen_mode.setParamValue(0, preset_state.delfx.time);
    screen_mode.setParamValue(1, preset_state.delfx.depth);
  }
};

#endif /* N1GP_APP_INPUT_DELFX_H */
