#ifndef N1GP_APP_INPUT_BASE_H
#define N1GP_APP_INPUT_BASE_H

#include <variant>
#include <type_traits>
#include <algorithm>
#include <optional>
#include <functional>

#include "preset.h"
#include "preset_event.h"
#include "nts1_defs.h"
#include "nts1_iface.h"
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

static inline uint8_t app_input_get_defs_size(Nts1DefsSizeID id) {
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

static inline void app_input_set_param(AppInputParamID id, int16_t value) {
  switch (id) {
    case AppInputParamID::osc_shift_shape:
      preset_state.osc.shift_shape = value;
      break;
    case AppInputParamID::osc_shape:
      preset_state.osc.shape = value;
      break;
    case AppInputParamID::osc_type:
      preset_state.osc.index = value;
      break;
    case AppInputParamID::custom_param_1:
      preset_state.osc.custom_values[0] = value;
      break;
    case AppInputParamID::custom_param_2:
      preset_state.osc.custom_values[1] = value;
      break;
    case AppInputParamID::custom_param_3:
      preset_state.osc.custom_values[2] = value;
      break;
    case AppInputParamID::custom_param_4:
      preset_state.osc.custom_values[3] = value;
      break;
    case AppInputParamID::custom_param_5:
      preset_state.osc.custom_values[4] = value;
      break;
    case AppInputParamID::custom_param_6:
      preset_state.osc.custom_values[5] = value;
      break;
    case AppInputParamID::custom_value_selected_page:
      preset_state.osc.custom_value_selected_page = value;
      break;
    case AppInputParamID::filter_peak:
      preset_state.filter.peak = value;
      break;
    case AppInputParamID::filter_cutoff:
      preset_state.filter.cutoff = value;
      break;
    case AppInputParamID::filter_type:
      preset_state.filter.index = value;
      break;
    case AppInputParamID::ampeg_attack:
      preset_state.ampeg.attack = value;
      break;
    case AppInputParamID::ampeg_release:
      preset_state.ampeg.release = value;
      break;
    case AppInputParamID::ampeg_type:
      preset_state.ampeg.index = value;
      break;
    case AppInputParamID::modfx_time:
      preset_state.modfx.time = value;
      break;
    case AppInputParamID::modfx_depth:
      preset_state.modfx.depth = value;
      break;
    case AppInputParamID::modfx_type:
      preset_state.modfx.index = value;
      break;
    case AppInputParamID::delfx_time:
      preset_state.delfx.time = value;
      break;
    case AppInputParamID::delfx_depth:
      preset_state.delfx.depth = value;
      break;
    case AppInputParamID::delfx_type:
      preset_state.delfx.index = value;
      break;
    case AppInputParamID::revfx_time:
      preset_state.revfx.time = value;
      break;
    case AppInputParamID::revfx_depth:
      preset_state.revfx.depth = value;
      break;
    case AppInputParamID::revfx_type:
      preset_state.revfx.index = value;
      break;
    case AppInputParamID::arp_type:
      preset_state.arp.index = value;
      break;
    case AppInputParamID::arp_intervals:
      preset_state.arp.intervals = value;
      break;
    case AppInputParamID::arp_length:
      preset_state.arp.length = value;
      break;
    case AppInputParamID::arp_state:
      preset_state.arp.state = value;
      break;
    case AppInputParamID::arp_tempo:
      preset_state.arp.tempo = value;
      break;
    default:
      break;
  }
}

static inline int16_t app_input_get_param(AppInputParamID id) {
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

static inline bool app_input_is_seq_mode(AppInputMode mode) {
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

  inline void inc(const value_type v) {
    base.inc(v);
  }
  inline void set(const value_type v) {
    base.set(v);
    nts1_param_change(nts1_main_id, nts1_sub_id, get());
  }
  inline value_type get() {
    return base.get();
  }
};

template<typename VALUE_TYPE, uint8_t preset_event_command_id, uint8_t preset_event_target_id>
struct AppInputValueWithSave {
  using value_type = typename VALUE_TYPE::value_type;
  VALUE_TYPE base;

  inline void inc(const value_type v) {
    base.inc(v);
  }
  inline void set(const value_type v) {
    base.set(v);
    preset_event_create(preset_event_command_id, preset_event_target_id, get());
  }
  inline value_type get() {
    return base.get();
  }
};

template<typename VALUE_TYPE, uint8_t nts1_main_id, uint8_t nts1_sub_id, uint8_t preset_event_command_id, uint8_t preset_event_target_id>
struct AppInputValueWithNts1AndSave {
  using value_type = typename VALUE_TYPE::value_type;
  VALUE_TYPE base;

  inline void inc(const value_type v) {
    base.inc(v);
  }
  inline void set(const value_type v) {
    base.set(v);
    nts1_param_change(nts1_main_id, nts1_sub_id, get());
    preset_event_create(preset_event_command_id, preset_event_target_id, get());
  }
  inline value_type get() {
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
  inline void init() {
  }
  inline bool button(AppBtnID id, bool on) {
    return false;
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
  inline uint8_t defs_size() {
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
    return false;
  }
};


#endif /* N1GP_APP_INPUT_BASE_H */
