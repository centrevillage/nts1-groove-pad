#ifndef N1GP_APP_INPUT_AMPEG_H
#define N1GP_APP_INPUT_AMPEG_H

#include <app_input/base.hpp>

using AppInputValueAmpegAttack =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::ampeg_attack, 0, 1023>,
    k_param_id_ampeg_attack, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_AMPEG_ATTACK // preset save
  >;
using AppInputValueAmpegRelease =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::ampeg_release, 0, 1023>,
    k_param_id_ampeg_release, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_AMPEG_RELEASE // preset save
  >;
using AppInputValueAmpegType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::ampeg_type, 0, 15>,
    k_param_id_ampeg_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_AMPEG_INDEX // preset save
  >;
struct AppInputAmpeg : AppInputIncTouchImpl<AppInputValueAmpegAttack, AppInputValueAmpegRelease>, AppInputLrButtonImpl<AppInputValueAmpegType, Nts1DefsSizeID::ampeg_defs_size> {
  inline void init() {
  }
  inline void refresh() {
    screen_edit_set_title("AmpEG", 16);
    screen_edit_set_type(ampeg_defs[preset_state.ampeg.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Attack", 6);
    screen_edit_set_param_name(1, "Release", 7);
    screen_edit_set_param_value(0, preset_state.ampeg.attack);
    screen_edit_set_param_value(1, preset_state.ampeg.release);
  }
};

#endif /* N1GP_APP_INPUT_AMPEG_H */
