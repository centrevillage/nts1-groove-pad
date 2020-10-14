#ifndef N1GP_APP_INPUT_FILTER_H
#define N1GP_APP_INPUT_FILTER_H

#include <app_input/base.hpp>

using AppInputValueFilterPeak =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::filter_peak, 0, 1023>,
    k_param_id_filt_peak, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_FILTER_PEAK // preset save
  >;
using AppInputValueFilterCutoff =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::filter_cutoff, 0, 1023>,
    k_param_id_filt_cutoff, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_FILTER_CUTOFF // preset save
  >;
using AppInputValueFilterType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::filter_type, 0, 15>,
    k_param_id_filt_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_FILTER_INDEX // preset save
  >;
struct AppInputFilter : AppInputIncTouchImpl<AppInputValueFilterPeak, AppInputValueFilterCutoff>, AppInputLrButtonImpl<AppInputValueFilterType, Nts1DefsSizeID::filter_defs_size> {
  inline void init() {
    screen_set_mode(SCREEN_MODE_EDIT);
  }
  inline void refresh() {
    screen_edit_set_title("Filter", 16);
    screen_edit_set_type(filter_defs[preset_state.filter.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Peak", 4);
    screen_edit_set_param_name(1, "Cutoff", 6);
    screen_edit_set_param_value(0, preset_state.filter.peak);
    screen_edit_set_param_value(1, preset_state.filter.cutoff);
  }
};


#endif /* N1GP_APP_INPUT_FILTER_H */
