#ifndef N1GP_APP_INPUT_H
#define N1GP_APP_INPUT_H

#include <variant>
#include <type_traits>
#include <algorithm>
#include <optional>
#include <functional>

#include "preset.h"
#include "app_touch.hpp"
#include "app_button.hpp"
#include "screen.h"
#include "state.h"
#include "app_seq.h"
#include "led.h"


enum class AppInputMode : uint8_t {
  osc = 0,
  custom,
  filter,
  ampeg,
  modfx,
  delfx,
  revfx,
  arp,
  save,
  load,
  clear,
  global,
  scale,
  trans,
  stutter,
  lfo,

  seq_select,
  seq_note,
  seq_osc,
  seq_custom,
  seq_filter,
  seq_ampeg,
  seq_modfx,
  seq_delfx,
  seq_revfx,
  seq_arp,
  seq_scale,
  seq_trans,
  seq_stutter,
  seq_lfo,
};

enum class AppInputParamID : uint8_t {
  osc_shift_shape = 0,
  osc_shape,
  osc_type,
  custom_param_1,
  custom_param_2,
  custom_param_3,
  custom_param_4,
  custom_param_5,
  custom_param_6,
  custom_value_selected_page,
  filter_peak,
  filter_cutoff,
  filter_type,
  ampeg_attack,
  ampeg_release,
  ampeg_type,
  modfx_time,
  modfx_depth,
  modfx_type,
  delfx_time,
  delfx_depth,
  delfx_type,
  revfx_time,
  revfx_depth,
  revfx_type,
  arp_type,
  arp_intervals,
  arp_length,
  arp_state,
  arp_tempo
  // TODO:
};

enum class Nts1DefsSizeID : uint8_t {
  osc_defs_size = 0,
  filter_defs_size,
  ampeg_defs_size,
  modfx_defs_size,
  delfx_defs_size,
  revfx_defs_size,
  arppat_defs_size,
  arpint_defs_size
};

constexpr uint8_t app_input_get_defs_size(Nts1DefsSizeID id) {
  switch (id) {
    case Nts1DefsSizeID::osc_defs_size:
      return osc_defs_size;
    case Nts1DefsSizeID::filter_defs_size:
      return filter_defs_size;
    case Nts1DefsSizeID::ampeg_defs_size:
      return ampeg_defs_size;
    case Nts1DefsSizeID::modfx_defs_size:
      return modfx_defs_size;
    case Nts1DefsSizeID::delfx_defs_size:
      return delfx_defs_size;
    case Nts1DefsSizeID::revfx_defs_size:
      return revfx_defs_size;
    case Nts1DefsSizeID::arppat_defs_size:
      return arppat_defs_size;
    case Nts1DefsSizeID::arpint_defs_size:
      return arpint_defs_size;
    default:
      break;
  }
  return 0;
}

constexpr void app_input_set_param(AppInputParamID id, int16_t value) {
  switch (id) {
    case AppInputParamID::osc_shift_shape:
      preset_state.osc.shift_shape = value;
    case AppInputParamID::osc_shape:
      preset_state.osc.shape = value;
    case AppInputParamID::osc_type:
      preset_state.osc.index = value;
    case AppInputParamID::custom_param_1:
      preset_state.osc.custom_values[0] = value;
    case AppInputParamID::custom_param_2:
      preset_state.osc.custom_values[1] = value;
    case AppInputParamID::custom_param_3:
      preset_state.osc.custom_values[2] = value;
    case AppInputParamID::custom_param_4:
      preset_state.osc.custom_values[3] = value;
    case AppInputParamID::custom_param_5:
      preset_state.osc.custom_values[4] = value;
    case AppInputParamID::custom_param_6:
      preset_state.osc.custom_values[5] = value;
    case AppInputParamID::custom_value_selected_page:
      preset_state.osc.custom_value_selected_page = value;
    case AppInputParamID::filter_peak:
      preset_state.filter.peak = value;
    case AppInputParamID::filter_cutoff:
      preset_state.filter.cutoff = value;
    case AppInputParamID::filter_type:
      preset_state.filter.index = value;
    case AppInputParamID::ampeg_attack:
      preset_state.ampeg.attack = value;
    case AppInputParamID::ampeg_release:
      preset_state.ampeg.release = value;
    case AppInputParamID::ampeg_type:
      preset_state.ampeg.index = value;
    case AppInputParamID::modfx_time:
      preset_state.modfx.time = value;
    case AppInputParamID::modfx_depth:
      preset_state.modfx.depth = value;
    case AppInputParamID::modfx_type:
      preset_state.modfx.index = value;
    case AppInputParamID::delfx_time:
      preset_state.delfx.time = value;
    case AppInputParamID::delfx_depth:
      preset_state.delfx.depth = value;
    case AppInputParamID::delfx_type:
      preset_state.delfx.index = value;
    case AppInputParamID::revfx_time:
      preset_state.revfx.time = value;
    case AppInputParamID::revfx_depth:
      preset_state.revfx.depth = value;
    case AppInputParamID::revfx_type:
      preset_state.revfx.index = value;
    case AppInputParamID::arp_type:
      preset_state.arp.index = value;
    case AppInputParamID::arp_intervals:
      preset_state.arp.intervals = value;
    case AppInputParamID::arp_length:
      preset_state.arp.length = value;
    case AppInputParamID::arp_state:
      preset_state.arp.state = value;
    case AppInputParamID::arp_tempo:
      preset_state.arp.tempo = value;
    default:
      break;
  }
}

constexpr int16_t app_input_get_param(AppInputParamID id) {
  switch (id) {
    case AppInputParamID::osc_shift_shape:
      return preset_state.osc.shift_shape;
    case AppInputParamID::osc_shape:
      return preset_state.osc.shape;
    case AppInputParamID::osc_type:
      return preset_state.osc.index;
    case AppInputParamID::custom_param_1:
      return preset_state.osc.custom_values[0];
    case AppInputParamID::custom_param_2:
      return preset_state.osc.custom_values[1];
    case AppInputParamID::custom_param_3:
      return preset_state.osc.custom_values[2];
    case AppInputParamID::custom_param_4:
      return preset_state.osc.custom_values[3];
    case AppInputParamID::custom_param_5:
      return preset_state.osc.custom_values[4];
    case AppInputParamID::custom_param_6:
      return preset_state.osc.custom_values[5];
    case AppInputParamID::custom_value_selected_page:
      return preset_state.osc.custom_value_selected_page;
    case AppInputParamID::filter_peak:
      return preset_state.filter.peak;
    case AppInputParamID::filter_cutoff:
      return preset_state.filter.cutoff;
    case AppInputParamID::filter_type:
      return preset_state.filter.index;
    case AppInputParamID::ampeg_attack:
      return preset_state.ampeg.attack;
    case AppInputParamID::ampeg_release:
      return preset_state.ampeg.release;
    case AppInputParamID::ampeg_type:
      return preset_state.ampeg.index;
    case AppInputParamID::modfx_time:
      return preset_state.modfx.time;
    case AppInputParamID::modfx_depth:
      return preset_state.modfx.depth;
    case AppInputParamID::modfx_type:
      return preset_state.modfx.index;
    case AppInputParamID::delfx_time:
      return preset_state.delfx.time;
    case AppInputParamID::delfx_depth:
      return preset_state.delfx.depth;
    case AppInputParamID::delfx_type:
      return preset_state.delfx.index;
    case AppInputParamID::revfx_time:
      return preset_state.revfx.time;
    case AppInputParamID::revfx_depth:
      return preset_state.revfx.depth;
    case AppInputParamID::revfx_type:
      return preset_state.revfx.index;
    case AppInputParamID::arp_type:
      return preset_state.arp.index;
    case AppInputParamID::arp_intervals:
      return preset_state.arp.intervals;
    case AppInputParamID::arp_length:
      return preset_state.arp.length;
    case AppInputParamID::arp_state:
      return preset_state.arp.state;
    case AppInputParamID::arp_tempo:
      return preset_state.arp.tempo;
    default:
      break;
  }
  return 0;
}

bool app_input_is_seq_mode(AppInputMode mode) {
  bool result = false;
  switch (mode) {
    //case seq_select:
    case AppInputMode::seq_note:
    case AppInputMode::seq_osc:
    case AppInputMode::seq_custom:
    case AppInputMode::seq_filter:
    case AppInputMode::seq_ampeg:
    case AppInputMode::seq_modfx:
    case AppInputMode::seq_delfx:
    case AppInputMode::seq_revfx:
    case AppInputMode::seq_arp:
    case AppInputMode::seq_scale:
    case AppInputMode::seq_trans:
    case AppInputMode::seq_stutter:
    case AppInputMode::seq_lfo:
      result = true;
      break;
      [[fallthrough]]
    default:
      break;
  }
  return result;
}

template<typename VALUE_TYPE, AppInputParamID id, VALUE_TYPE min, VALUE_TYPE max>
struct AppInputValue {
  using value_type = VALUE_TYPE;

  inline void inc(const VALUE_TYPE v) {
    set(app_input_get_param(id) + v);
  }
  inline void set(const VALUE_TYPE v) {
    app_input_set_param(id, std::clamp<VALUE_TYPE>(v, min, max));
  }
  inline VALUE_TYPE get() {
    return app_input_get_param(id);
  }
};

template<typename VALUE_TYPE, uint8_t nts1_main_id, uint8_t nts1_sub_id = 0>
struct AppInputValueWithNts1 {
  using value_type = typename VALUE_TYPE::value_type;
  VALUE_TYPE base;

  inline void inc(const typename VALUE_TYPE::value_type v) {
    base.inc(v);
  }
  inline void set(const typename VALUE_TYPE::value_type v) {
    base.set(v);
    nts1_param_change(nts1_main_id, nts1_sub_id, get());
  }
  inline typename VALUE_TYPE::value_type get() {
    return base.get();
  }
};

template<typename VALUE_TYPE, uint8_t preset_event_command_id, uint8_t preset_event_target_id>
struct AppInputValueWithSave {
  using value_type = typename VALUE_TYPE::value_type;
  VALUE_TYPE base;

  inline void inc(const typename VALUE_TYPE::value_type v) {
    base.inc(v);
  }
  inline void set(const typename VALUE_TYPE::value_type v) {
    base.set(v);
    preset_event_create(preset_event_command_id, preset_event_target_id, get());
  }
  inline typename VALUE_TYPE::value_type get() {
    return base.get();
  }
};

template<typename VALUE_TYPE, uint8_t nts1_main_id, uint8_t nts1_sub_id, uint8_t preset_event_command_id, uint8_t preset_event_target_id>
struct AppInputValueWithNts1AndSave {
  using value_type = typename VALUE_TYPE::value_type;
  VALUE_TYPE base;

  inline void inc(const typename VALUE_TYPE::value_type v) {
    base.inc(v);
  }
  inline void set(const typename VALUE_TYPE::value_type v) {
    base.set(v);
    nts1_param_change(nts1_main_id, nts1_sub_id, get());
    preset_event_create(preset_event_command_id, preset_event_target_id, get());
  }
  inline typename VALUE_TYPE::value_type get() {
    return base.get();
  }
};

template<typename L_VALUE_TYPE, typename R_VALUE_TYPE>
struct AppInputIncTouchImpl {
  L_VALUE_TYPE l_value;
  R_VALUE_TYPE r_value;

  inline void incValueL(const int16_t inc_value) {
    l_value.inc(inc_value);
  }
  inline void incValueR(const int16_t inc_value) {
    r_value.inc(inc_value);
  }
};

// 未実装のモード用のダミー実装
struct AppInputNullImpl {
  inline bool button(AppBtnID id, bool on) {
  }
  inline void incValueL(int16_t inc_value) {
  }
  inline void incValueR(int16_t inc_value) {
  }
  inline void refresh() {
  }
};

template<typename VALUE_TYPE, Nts1DefsSizeID defs_id>
struct AppInputLrButtonImpl {
  constexpr uint8_t defs_size() {
    return app_input_get_defs_size(defs_id);
  }
  inline bool button(AppBtnID id, bool on) {
    VALUE_TYPE _value {};
    switch(id) {
      case AppBtnID::L:
        if (defs_size() > 1 && on) {
          _value.set((_value.get() + defs_size() - 1) % defs_size());
        }
        return true;
      case AppBtnID::R:
        if (defs_size() > 1 && on) {
          _value.set((_value.get() + 1) % defs_size());
        }
        return true;
      default:
        break;
    }
  }
};

using AppInputValueOscShiftShape =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_shift_shape, 0, 1023>,
    k_param_id_osc_shift_shape, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_SHIFT_SHAPE // preset save
  >;
using AppInputValueOscShape =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_shape, 0, 1023>,
    k_param_id_osc_shift_shape, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_SHAPE // preset save
  >;
using AppInputValueOscType =
  AppInputValueWithNts1AndSave<
    AppInputValue<int16_t, AppInputParamID::osc_type, 0, 15>,
    k_param_id_osc_type, 0, // NTS1 params
    PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_INDEX // preset save
  >;
struct AppInputOsc : AppInputIncTouchImpl<AppInputValueOscShiftShape, AppInputValueOscShape>, AppInputLrButtonImpl<AppInputValueOscType, Nts1DefsSizeID::osc_defs_size> {
  inline void refresh() {
    screen_edit_set_type(osc_defs[preset_state.osc.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "ShiftSh", 7);
    screen_edit_set_param_name(1, "Shape", 5);
    screen_edit_set_param_value(0, preset_state.osc.shift_shape);
    screen_edit_set_param_value(1, preset_state.osc.shape);
  };
};

struct AppInputCustom {
  uint8_t current_page = 0;

  inline void init() {
    current_page = 0;
  }

  inline void _incValue(uint8_t param_idx, int16_t value) {
    value = std::clamp<int16_t>(value, 0, 1023);
    preset_state.osc.custom_values[param_idx] = value;
    nts1_param_change(k_param_id_osc_edit, param_idx, value);
    preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_CUSTOM_VALUES, param_idx);
  }

  inline void incValueL(int16_t inc_value) {
    uint8_t param_id = current_page * 2;
    _incValue(param_id, inc_value);
  }
  inline void incValueR(int16_t inc_value) {
    uint8_t param_id = current_page * 2 + 1;
    _incValue(param_id, inc_value);
  }
  inline bool button(AppBtnID id, bool on) {
    switch(id) {
      case AppBtnID::L:
        if (osc_defs[preset_state.osc.index].param_count > 2) {
          uint8_t last_page = (osc_defs[preset_state.osc.index].param_count-1) / 2;
          if (on) {
            current_page = (current_page+last_page) % (last_page+1);
            preset_state.osc.custom_value_selected_page = current_page;
          }
        }
        return true;
      case AppBtnID::R:
        uint8_t last_page = (osc_defs[preset_state.osc.index].param_count-1) / 2;
        if (on) {
          current_page = (current_page+1) % (last_page+1);
          preset_state.osc.custom_value_selected_page = current_page;
        }
        return true;
      default:
        break;
    }
  }
  inline void refresh() {
    if (osc_defs[preset_state.osc.index].param_count > 0) {
      char page_text[8] = {
        'P', 'a', 'g', 'e', ' ',
        current_page+1+48,
        '/',
        (((osc_defs[preset_state.osc.index].param_count+1) / 2) % 10)+48
      };
      screen_edit_set_type(page_text, 8);
      char* param_name = osc_defs[preset_state.osc.index].params[current_page*2].name;
      screen_edit_set_param_name(0, param_name, PARAM_NAME_LEN);
      screen_edit_set_param_value(0, preset_state.osc.custom_values[current_page*2]);

      uint8_t is_last_page = current_page == (osc_defs[preset_state.osc.index].param_count / 2);
      if (!is_last_page || (osc_defs[preset_state.osc.index].param_count % 2) == 0) {
        char* param_name2 = osc_defs[preset_state.osc.index].params[current_page*2+1].name;
        screen_edit_set_param_name(1, param_name2, PARAM_NAME_LEN);
        screen_edit_set_param_value(1, preset_state.osc.custom_values[current_page*2+1]);
      }
    } else {
      screen_edit_set_type("No Param", PARAM_NAME_LEN);
    }
  }
};

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
  inline void refresh() {
    screen_edit_set_type(filter_defs[preset_state.filter.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Peak", 4);
    screen_edit_set_param_name(1, "Cutoff", 6);
    screen_edit_set_param_value(0, preset_state.filter.peak);
    screen_edit_set_param_value(1, preset_state.filter.cutoff);
  }
};

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
  inline void refresh() {
    screen_edit_set_type(ampeg_defs[preset_state.ampeg.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Attack", 6);
    screen_edit_set_param_name(1, "Release", 7);
    screen_edit_set_param_value(0, preset_state.ampeg.attack);
    screen_edit_set_param_value(1, preset_state.ampeg.release);
  }
};

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
  inline void refresh() {
    screen_edit_set_type(modfx_defs[preset_state.modfx.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Time", 4);
    screen_edit_set_param_name(1, "Depth", 5);
    screen_edit_set_param_value(0, preset_state.modfx.time);
    screen_edit_set_param_value(1, preset_state.modfx.depth);
  }
};

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
  inline void refresh() {
    screen_edit_set_type(delfx_defs[preset_state.delfx.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Time", 4);
    screen_edit_set_param_name(1, "Depth", 5);
    screen_edit_set_param_value(0, preset_state.delfx.time);
    screen_edit_set_param_value(1, preset_state.delfx.depth);
  }
};

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
  inline void refresh() {
    screen_edit_set_type(revfx_defs[preset_state.revfx.index].name, PARAM_NAME_LEN);
    screen_edit_set_param_name(0, "Time", 4);
    screen_edit_set_param_name(1, "Depth", 5);
    screen_edit_set_param_value(0, preset_state.revfx.time);
    screen_edit_set_param_value(1, preset_state.revfx.depth);
  }
};

struct AppInputArp {
  uint8_t current_page = 0;

  inline void init() {
    current_page = 0;
  }

  inline void incValueL(int16_t inc_value) {
    if (current_page = 0) {
      int16_t value = preset_state.arp.index + inc_value;
      preset_state.arp.index = std::clamp<int16_t>(value, 0, arppat_defs_size);
      nts1_param_change(k_param_id_arp_pattern, 0, preset_state.arp.index);
      preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_ARP_INDEX, 0);
    } else if (current_page = 1) {
      int16_t value = preset_state.arp.length + inc_value;
      preset_state.arp.length = std::clamp<int16_t>(value, 1, 16);
      nts1_param_change(k_param_id_arp_length, 0, preset_state.arp.length);
      preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_ARP_LENGTH, 0);
    } else {
      int16_t value = preset_state.arp.tempo + inc_value;
      preset_state.arp.tempo = std::clamp<int16_t>(value, 60, 120);
      nts1_param_change(k_param_id_arp_tempo, 0, preset_state.arp.tempo);
      preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_ARP_TEMPO, 0);
    }
  }
  inline void incValueR(int16_t inc_value) {
    if (current_page = 0) {
      int16_t value = preset_state.arp.intervals + inc_value;
      preset_state.arp.intervals = std::clamp<int16_t>(value, 0, arpint_defs_size);
      nts1_param_change(k_param_id_arp_intervals, 0, preset_state.arp.intervals);
      preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_ARP_INTERVALS, 0);
    } else if (current_page = 1) {
      int16_t value = preset_state.arp.state + inc_value;
      preset_state.arp.state = std::clamp<int16_t>(value, 0, 1);
      nts1_param_change(k_param_id_arp_state, 0, preset_state.arp.state);
      preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_ARP_STATE, 0);
    }
  }
  inline bool button(AppBtnID id, bool on) {
    const uint8_t last_page = 2;
    switch(id) {
      case AppBtnID::L:
        if (on) {
          current_page = (current_page+last_page) % (last_page+1);
        }
        return true;
      case AppBtnID::R:
        if (on) {
          current_page = (current_page+1) % (last_page+1);
        }
        return true;
      default:
        break;
    }
  }
  inline void refresh() {
    char page_text[8] = {
      'P', 'a', 'g', 'e', ' ',
      current_page+1+48,
      '/', '3'
    };
    screen_edit_set_type(page_text, 8);
    if (current_page == 0) {
      screen_edit_set_param_name(0, "Type", 4);
      screen_edit_set_param_name(1, "Interval", 8);
      // TODO: defs からパラメータ名を拾ってくる
      screen_edit_set_param_value_text(0, arppat_defs[preset_state.arp.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_value_text(1, arpint_defs[preset_state.arp.intervals].name, PARAM_NAME_LEN);
    } else if (current_page == 1) {
      screen_edit_set_param_name(0, "Length", 6);
      screen_edit_set_param_name(1, "State", 5);
      screen_edit_set_param_value(0, preset_state.arp.length);
      screen_edit_set_param_value(1, preset_state.arp.state);
    } else {
      screen_edit_set_param_name(0, "Tempo", 5);
      screen_edit_set_param_value(0, preset_state.arp.tempo);
    }
  }
};

// TODO:
struct AppInputSave : AppInputNullImpl { };
struct AppInputLoad : AppInputNullImpl { };
struct AppInputClear : AppInputNullImpl { };
struct AppInputGlobal : AppInputNullImpl { };
struct AppInputScale : AppInputNullImpl { };
struct AppInputTrans : AppInputNullImpl { };
struct AppInputStutter : AppInputNullImpl { };
struct AppInputLfo : AppInputNullImpl { };

struct AppInputSeqSelect : AppInputNullImpl { };
struct AppInputSeqNote : AppInputNullImpl { };
struct AppInputSeqOsc : AppInputNullImpl { };
struct AppInputSeqCustom : AppInputNullImpl { };
struct AppInputSeqFilter : AppInputNullImpl { };
struct AppInputSeqAmpeg : AppInputNullImpl { };
struct AppInputSeqModfx : AppInputNullImpl { };
struct AppInputSeqDelfx : AppInputNullImpl { };
struct AppInputSeqRevfx : AppInputNullImpl { };
struct AppInputSeqArp : AppInputNullImpl { };
struct AppInputSeqScale : AppInputNullImpl { };
struct AppInputSeqTrans : AppInputNullImpl { };
struct AppInputSeqStutter : AppInputNullImpl { };
struct AppInputSeqLfo : AppInputNullImpl { };

struct AppInputModeState {
  std::variant<
    AppInputOsc,
    AppInputCustom,
    AppInputFilter,
    AppInputAmpeg,
    AppInputModfx,
    AppInputDelfx,
    AppInputRevfx,
    AppInputArp,
    AppInputSave,
    AppInputLoad,
    AppInputClear,
    AppInputGlobal,
    AppInputScale,
    AppInputTrans,
    AppInputStutter,
    AppInputLfo,

    AppInputSeqSelect,
    AppInputSeqNote,
    AppInputSeqOsc,
    AppInputSeqCustom,
    AppInputSeqFilter,
    AppInputSeqAmpeg,
    AppInputSeqModfx,
    AppInputSeqDelfx,
    AppInputSeqRevfx,
    AppInputSeqArp,
    AppInputSeqScale,
    AppInputSeqTrans,
    AppInputSeqStutter,
    AppInputSeqLfo
  > mode = AppInputOsc {};

  void change(AppInputMode m) {
    switch (m) {
      case AppInputMode::osc:
        mode = AppInputOsc {};
        break;
      case AppInputMode::custom:
        mode = AppInputCustom {};
        break;
      case AppInputMode::filter:
        mode = AppInputFilter {};
        break;
      case AppInputMode::ampeg:
        mode = AppInputAmpeg {};
        break;
      case AppInputMode::modfx:
        mode = AppInputModfx {};
        break;
      case AppInputMode::delfx:
        mode = AppInputDelfx {};
        break;
      case AppInputMode::revfx:
        mode = AppInputRevfx {};
        break;
      case AppInputMode::arp:
        mode = AppInputArp {};
        break;
      case AppInputMode::save:
        mode = AppInputSave {};
        break;
      case AppInputMode::load:
        mode = AppInputLoad {};
        break;
      case AppInputMode::clear:
        mode = AppInputClear {};
        break;
      case AppInputMode::global:
        mode = AppInputGlobal {};
        break;
      case AppInputMode::scale:
        mode = AppInputScale {};
        break;
      case AppInputMode::trans:
        mode = AppInputTrans {};
        break;
      case AppInputMode::stutter:
        mode = AppInputStutter {};
        break;
      case AppInputMode::lfo:
        mode = AppInputLfo {};
        break;
      case AppInputMode::seq_select:
        mode = AppInputSeqSelect {};
        break;
      case AppInputMode::seq_note:
        mode = AppInputSeqNote {};
        break;
      case AppInputMode::seq_osc:
        mode = AppInputSeqOsc {};
        break;
      case AppInputMode::seq_custom:
        mode = AppInputSeqCustom {};
        break;
      case AppInputMode::seq_filter:
        mode = AppInputSeqFilter {};
        break;
      case AppInputMode::seq_ampeg:
        mode = AppInputSeqAmpeg {};
        break;
      case AppInputMode::seq_modfx:
        mode = AppInputSeqModfx {};
        break;
      case AppInputMode::seq_delfx:
        mode = AppInputSeqDelfx {};
        break;
      case AppInputMode::seq_revfx:
        mode = AppInputSeqRevfx {};
        break;
      case AppInputMode::seq_arp:
        mode = AppInputSeqArp {};
        break;
      case AppInputMode::seq_scale:
        mode = AppInputSeqScale {};
        break;
      case AppInputMode::seq_trans:
        mode = AppInputSeqTrans {};
        break;
      case AppInputMode::seq_stutter:
        mode = AppInputSeqStutter {};
        break;
      case AppInputMode::seq_lfo:
        mode = AppInputSeqLfo {};
        break;
      default:
        break;
    }
  }

  void refresh() {
    std::visit([](auto& m) {
      m.refresh();
    }, mode);
  }

  void touchOnChange(AppTouchPadID id, int16_t inc_value) {
    std::visit([=](auto& m) {
      if (id == AppTouchPadID::L) {
        m.incValueL(inc_value);
      } else {
        m.incValueR(inc_value);
      }
    }, mode);
  }

  bool button(AppBtnID id, bool on) {
    return std::visit([=](auto& m) {
      return m.button(id, on);
    }, mode);
  }
};

struct AppInput {
  AppButtons buttons;
  AppTouch touch;
  uint8_t touch_bits = 0;
  AppInputMode current_mode = AppInputMode::osc;
  AppInputMode next_mode = AppInputMode::seq_note;

  AppInputModeState state;

  void init() {
    buttons.init();
    buttons.on_change = [this](AppBtnID id, bool on){
      state.button(id, on);
    };

    touch.init();
    touch.on_acquisition_end = [this](uint8_t bits) {
      touch_bits = bits;
    };
    touch.on_change = [this](AppTouchPadID id, int16_t inc_value) {
      state.touchOnChange(id, inc_value);
    };
  }

  void process() {
    buttons.process();
    touch.process();
  }

  inline bool isSeqPressed(uint32_t state_bits) {
    return state_bits & (1<<static_cast<uint32_t>(AppBtnID::SEQ));
  }

  inline void backToEditMode() {
  }

  void refresh() {
    state.refresh();
  }

  void changeMode(AppInputMode mode) {
    current_mode = mode;
    state.change(mode);
    state.refresh();
  }

  inline void button(AppBtnID id, bool on) {
    if (state.button(id, on)) {
      refresh();
      return;
    }
    if (app_input_is_seq_mode(current_mode)) {
      if (id == AppBtnID::SEQ) {
        backToEditMode();
      } else {
        state.button(id, on);
      }
    } else if (isSeqPressed(buttons.state_bits)) {
      next_mode = AppInputMode::seq_note;
      switch(id) {
        case AppBtnID::OSC:
          next_mode = AppInputMode::seq_osc;
          break;
        case AppBtnID::PARAM:
          next_mode = AppInputMode::seq_custom;
          break;
        case AppBtnID::FILTER:
          next_mode = AppInputMode::seq_filter;
          break;
        case AppBtnID::EG:
          next_mode = AppInputMode::seq_ampeg;
          break;
        case AppBtnID::MOD:
          next_mode = AppInputMode::seq_modfx;
          break;
        case AppBtnID::DELAY:
          next_mode = AppInputMode::seq_delfx;
          break;
        case AppBtnID::REVERB:
          next_mode = AppInputMode::seq_revfx;
          break;
        case AppBtnID::ARP:
          next_mode = AppInputMode::seq_arp;
          break;
        case AppBtnID::SAVE: // save
          break;
        case AppBtnID::LOAD: // load
          break;
        case AppBtnID::CLEAR: // clear
          break;
        case AppBtnID::GLOBAL: // global
          break;
        case AppBtnID::SCALE:
          break;
        case AppBtnID::TRANS:
          break;
        case AppBtnID::STUTTER:
          next_mode = AppInputMode::seq_stutter;
          break;
        case AppBtnID::LFO:
          next_mode = AppInputMode::seq_lfo;
          break;
        case AppBtnID::SEQ:
          if (on) {
            changeMode(AppInputMode::seq_select);
          }
          break;
        case AppBtnID::RUN:
          break;
        case AppBtnID::L:
          break;
        case AppBtnID::R:
          break;
        default:
          break;
      }
    } else {
      switch(id) {
        case AppBtnID::OSC:
          if (on) {
            changeMode(AppInputMode::osc);
          }
          break;
        case AppBtnID::PARAM:
          if (on) {
            changeMode(AppInputMode::custom);
          }
          break;
        case AppBtnID::FILTER:
          if (on) {
            changeMode(AppInputMode::filter);
          }
          break;
        case AppBtnID::EG:
          if (on) {
            changeMode(AppInputMode::ampeg);
          }
          break;
        case AppBtnID::MOD:
          if (on) {
            changeMode(AppInputMode::modfx);
          }
          break;
        case AppBtnID::DELAY:
          if (on) {
            changeMode(AppInputMode::delfx);
          }
          break;
        case AppBtnID::REVERB:
          if (on) {
            changeMode(AppInputMode::revfx);
          }
          break;
        case AppBtnID::ARP:
          if (on) {
            changeMode(AppInputMode::arp);
          }
          break;
        case AppBtnID::SAVE:
          if (on) {
            changeMode(AppInputMode::save);
          }
          break;
        case AppBtnID::LOAD:
          if (on) {
            changeMode(AppInputMode::load);
          }
          break;
        case AppBtnID::CLEAR:
          if (on) {
            changeMode(AppInputMode::clear);
          }
          break;
        case AppBtnID::GLOBAL:
          if (on) {
            changeMode(AppInputMode::global);
          }
          break;
        case AppBtnID::SCALE:
          if (on) {
            changeMode(AppInputMode::scale);
          }
          break;
        case AppBtnID::TRANS:
          if (on) {
            changeMode(AppInputMode::trans);
          }
          break;
        case AppBtnID::STUTTER:
          if (on) {
            changeMode(AppInputMode::stutter);
          }
          break;
        case AppBtnID::LFO:
          if (on) {
            changeMode(AppInputMode::lfo);
          }
          break;
        case AppBtnID::SEQ:
          if (!on) {
            if (app_input_is_seq_mode(next_mode)) {
              changeMode(next_mode);
            }
          }
          break;
        case AppBtnID::RUN:
          if (seq.run_state) {
            seq.stop();
            led_set_run(0);
          } else {
            seq.start();
            led_set_run(1);
          }
          break;
        case AppBtnID::L:
          break;
        case AppBtnID::R:
          break;
        default:
          break;
      }
    }
  }
};

AppInput app_input;

#endif /* N1GP_APP_INPUT_H */
