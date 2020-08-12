#include "input.h"
#include "touch.h"
#include "oled.h"
#include "button.h"
#include "led.h"
#include "nts1_iface.h"
#include "state.h"
#include "preset.h"
#include "preset_event.h"
#include "nts1_defs.h"
#include "screen.h"
#include "util.h"
#include "app_seq.h"

#define BTN_SEQ_IDX 16
#define BTN_RUN_IDX  17
#define BTN_L_IDX    18
#define BTN_R_IDX    19

#define BTN_SEQ_PIN  PIN_A11
#define BTN_RUN_PIN  PIN_C1
#define BTN_L_PIN    PIN_A8
#define BTN_R_PIN    PIN_A15

volatile InputState input_state = {0};

void input_osc_update_shift_shape(int16_t value) {
  preset_state.osc.shift_shape = value;
  nts1_param_change(k_param_id_osc_shift_shape, 0, value);
  // TODO: temporary save
}

void input_osc_update_shape(int16_t value) {
  preset_state.osc.shape = value;
  nts1_param_change(k_param_id_osc_shape, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_SHAPE, 0);
}

void input_osc_update_param(uint8_t param_idx, int16_t value) {
  preset_state.osc.custom_values[param_idx] = value;
  nts1_param_change(k_param_id_osc_edit, param_idx, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_OSC_CUSTOM_VALUES, param_idx);
}

void input_filter_update_cutoff(int16_t value) {
  preset_state.filter.cutoff = value;
  nts1_param_change(k_param_id_filt_cutoff, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_FILTER_CUTOFF, 0);
}

void input_filter_update_peak(int16_t value) {
  preset_state.filter.peak = value;
  nts1_param_change(k_param_id_filt_peak, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_FILTER_PEAK, 0);
}

void input_ampeg_update_attack(int16_t value) {
  preset_state.ampeg.attack = value;
  nts1_param_change(k_param_id_ampeg_attack, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_AMPEG_ATTACK, 0);
}

void input_ampeg_update_release(int16_t value) {
  preset_state.ampeg.release = value;
  nts1_param_change(k_param_id_ampeg_release, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_AMPEG_RELEASE, 0);
}

void input_modfx_update_time(int16_t value) {
  preset_state.modfx.time = value;
  nts1_param_change(k_param_id_mod_time, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_MODFX_TIME, 0);
}

void input_modfx_update_depth(int16_t value) {
  preset_state.modfx.depth = value;
  nts1_param_change(k_param_id_mod_depth, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_MODFX_DEPTH, 0);
}

void input_delfx_update_time(int16_t value) {
  preset_state.delfx.time = value;
  nts1_param_change(k_param_id_del_time, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_DELFX_TIME, 0);
}

void input_delfx_update_depth(int16_t value) {
  preset_state.delfx.depth = value;
  nts1_param_change(k_param_id_del_depth, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_DELFX_DEPTH, 0);
}

void input_revfx_update_time(int16_t value) {
  preset_state.revfx.time = value;
  nts1_param_change(k_param_id_rev_time, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_REVFX_TIME, 0);
}

void input_revfx_update_depth(int16_t value) {
  preset_state.revfx.depth = value;
  nts1_param_change(k_param_id_rev_depth, 0, value);
  preset_event_create(PST_EVT_REALTIME_TMP_SAVE, PST_EVT_TARGET_REVFX_DEPTH, 0);
}

void input_arp_update_pattern(int16_t value) {
  preset_state.arp.index = value;
  nts1_param_change(k_param_id_arp_pattern, 0, value);
  // TODO: temporary save
}

void input_arp_update_intervals(int16_t value) {
  preset_state.arp.intervals = value;
  nts1_param_change(k_param_id_arp_intervals, 0, value);
  // TODO: temporary save
}

void input_arp_update_length(int16_t value) {
  preset_state.arp.length = value;
  nts1_param_change(k_param_id_arp_length, 0, value);
  // TODO: temporary save
}

void input_arp_update_state(int16_t value) {
  preset_state.arp.state = value;
  nts1_param_change(k_param_id_arp_state, 0, value);
  // TODO: temporary save
}

void input_arp_update_tempo(int16_t value) {
  preset_state.arp.tempo = value;
  nts1_param_change(k_param_id_arp_tempo, 0, value);
  // TODO: temporary save
}

void input_update_pad_value(uint8_t is_right, int16_t value) {
  switch(input_state.mode) {
    case INPUT_MODE_OSC:
      if (!is_right) {
        input_osc_update_shift_shape(value);
      } else {
        input_osc_update_shape(value);
      }
      break;
    case INPUT_MODE_CUSTOM:
      if (!is_right) {
        input_osc_update_param(input_state.current_page * 2, value);
      } else {
        input_osc_update_param(input_state.current_page * 2 + 1, value);
      }
      break;
    case INPUT_MODE_FILTER:
      if (!is_right) {
        input_filter_update_peak(value);
      } else {
        input_filter_update_cutoff(value);
      }
      break;
    case INPUT_MODE_AMPEG:
      if (!is_right) {
        input_ampeg_update_attack(value);
      } else {
        input_ampeg_update_release(value);
      }
      break;
    case INPUT_MODE_MODFX:
      if (!is_right) {
        input_modfx_update_time(value);
      } else {
        input_modfx_update_depth(value);
      }
      break;
    case INPUT_MODE_DELFX:
      if (!is_right) {
        input_delfx_update_time(value);
      } else {
        input_delfx_update_depth(value);
      }
      break;
    case INPUT_MODE_REVFX:
      if (!is_right) {
        input_revfx_update_time(value);
      } else {
        input_revfx_update_depth(value);
      }
      break;
    case INPUT_MODE_ARP:
      if (!is_right) {
        if (input_state.current_page = 0) {
          input_arp_update_pattern(value);
        } else if (input_state.current_page = 1) {
          input_arp_update_length(value);
        } else {
          input_arp_update_tempo(value);
        }
      } else {
        if (input_state.current_page = 0) {
          input_arp_update_intervals(value);
        } else if (input_state.current_page = 1) {
          input_arp_update_state(value);
        }
      }
      break;
    case INPUT_MODE_SAVE:
      break;
    case INPUT_MODE_LOAD:
      break;
    case INPUT_MODE_CLEAR:
      break;
    case INPUT_MODE_GLOBAL:
      break;
    case INPUT_MODE_SCALE:
      break;
    case INPUT_MODE_TRANS:
      break;
    case INPUT_MODE_STUTTER:
      break;
    case INPUT_MODE_LFO:
      break;
    case INPUT_MODE_SEQ_SELECT:
      break;
    case INPUT_MODE_SEQ_NOTE:
      if (is_right) {
        for (uint8_t i = 0; i < SEQ_STEP_SIZE; ++i) {
          if (input_state.seq_selected_steps & ((uint16_t)1<<i)) {
            seq_state.steps[i].note = (uint8_t)clipping_int16((int16_t)seq_state.steps[i].note + value, 0, 127);
          }
        }
      }
      break;
    case INPUT_MODE_SEQ_OSC:
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      break;
    case INPUT_MODE_SEQ_FILTER:
      break;
    case INPUT_MODE_SEQ_AMPEG:
      break;
    case INPUT_MODE_SEQ_MODFX:
      break;
    case INPUT_MODE_SEQ_DELFX:
      break;
    case INPUT_MODE_SEQ_REVFX:
      break;
    case INPUT_MODE_SEQ_ARP:
      break;
    case INPUT_MODE_SEQ_SCALE:
      break;
    case INPUT_MODE_SEQ_TRANS:
      break;
    case INPUT_MODE_SEQ_STUTTER:
      break;
    case INPUT_MODE_SEQ_LFO:
      break;
    case INPUT_MODE_SIZE:
      break;
  }
  input_refresh();
}

void input_release_pad(uint8_t is_right) {
  switch(input_state.mode) {
    case INPUT_MODE_OSC:
      break;
    case INPUT_MODE_CUSTOM:
      break;
    case INPUT_MODE_FILTER:
      break;
    case INPUT_MODE_AMPEG:
      break;
    case INPUT_MODE_MODFX:
      break;
    case INPUT_MODE_DELFX:
      break;
    case INPUT_MODE_REVFX:
      break;
    case INPUT_MODE_ARP:
      break;
    case INPUT_MODE_SAVE:
      break;
    case INPUT_MODE_LOAD:
      break;
    case INPUT_MODE_CLEAR:
      break;
    case INPUT_MODE_GLOBAL:
      break;
    case INPUT_MODE_SCALE:
      break;
    case INPUT_MODE_TRANS:
      break;
    case INPUT_MODE_STUTTER:
      break;
    case INPUT_MODE_LFO:
      break;
    case INPUT_MODE_SEQ_SELECT:
      break;
    case INPUT_MODE_SEQ_NOTE:
      break;
    case INPUT_MODE_SEQ_OSC:
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      break;
    case INPUT_MODE_SEQ_FILTER:
      break;
    case INPUT_MODE_SEQ_AMPEG:
      break;
    case INPUT_MODE_SEQ_MODFX:
      break;
    case INPUT_MODE_SEQ_DELFX:
      break;
    case INPUT_MODE_SEQ_REVFX:
      break;
    case INPUT_MODE_SEQ_ARP:
      break;
    case INPUT_MODE_SEQ_SCALE:
      break;
    case INPUT_MODE_SEQ_TRANS:
      break;
    case INPUT_MODE_SEQ_STUTTER:
      break;
    case INPUT_MODE_SEQ_LFO:
      break;
    case INPUT_MODE_SIZE:
      break;
  }
}

void input_touch_handler(uint8_t touch_bits) {
  input_state.touch_bits = touch_bits;

  // L
  uint8_t state_bits = (touch_bits & 0b0111) | ((touch_bits & 0b01000000) >> 3);
  uint8_t is_changed = touch_util_process(state_bits, &(input_state.touch_states[0]));
  int16_t value = input_state.touch_states[0].value;
  if (is_changed && value != TOUCH_NO_VALUE && value != TOUCH_HOLD_VALUE) {
    input_update_pad_value(0, value);
  }
  if (value == TOUCH_NO_VALUE) {
    input_release_pad(0);
  }

  // R
  state_bits = ((touch_bits >> 3) & 0b0111) | ((touch_bits & 0b10000000) >> 4);
  is_changed = touch_util_process(state_bits, &(input_state.touch_states[1]));
  value = input_state.touch_states[1].value;
  if (is_changed && value != TOUCH_NO_VALUE && value != TOUCH_HOLD_VALUE) {
    input_update_pad_value(1, value);
  }
  if (value == TOUCH_NO_VALUE) {
    input_release_pad(1);
  }
}

void input_button_debug_handler(uint8_t button_idx, uint8_t on) {
  if (button_idx < 18) {
    led_set(button_idx, on);
  }
  //static char buf[16] = "BTN:";
  //if (on) {
  //  text_0x_from_uint8(&(buf[4]), button_idx);
  //  debug_text(buf, 6); 
  //} else {
  //  debug_text("", 0); 
  //}

  if (on) {
    switch(button_idx) {
      case 0:
        nts1_req_sys_version(); // value: k_nts1_tx_event_id_req_value, k_param_id_sys_version, 0, value=120
        break;
      case 1:
        nts1_req_param_value(0, 0); // value: k_nts1_tx_event_id_req_value, 0, 0, value=4
        break;
      case 2:
        nts1_req_osc_count(); // value: k_nts1_tx_event_id_req_unit_count, 0, 127, value=20
        break;
      case 3:
        //nts1_req_osc_desc(0); // unit desc: k_param_id_osc_type, 0, 0, "SAW"
        nts1_req_osc_desc(4); // unit desc: k_param_id_osc_type, 4, 6, "waves"
        break;
      case 4:
        nts1_param_change(k_param_id_osc_type, 0, 4);
        //nts1_req_osc_edit_param_desc(4); // edit param desc: k_param_id_osc_edit, sub_id=4, value_type=0, min=0, max=64, "Ring Mix" 
        nts1_req_osc_edit_param_desc(0); // edit param desc: k_param_id_osc_edit, sub_id=0, value_type=2, min=0, max=45, "Wave A" 
        break;
      case 5:
        nts1_req_filt_count(); // value: k_nts1_tx_event_id_req_unit_count, k_param_id_filt_type, 127, value=7
        break;
      case 6:
        nts1_req_filt_desc(0); // unit desc: k_param_id_filt_type, 0, 0, "LP 2"
        break;
      case 7:
        nts1_req_ampeg_count(); // k_nts1_tx_event_id_req_unit_count, k_param_id_ampeg_type, 127, value=5
        break;
      case 8:
        nts1_req_ampeg_desc(0); // unit desc: k_param_id_ampeg_type, 0, 0, "ADSR"
        break;
      case 9:
        nts1_req_mod_count(); // value: k_nts1_tx_event_id_req_unit_count, k_param_id_mod_type, sub_id=127, value=5
        break;
      case 10:
        nts1_req_mod_desc(0); // unit desc: k_param_id_mod_type, 0, 0, "OFF"
        break;
      case 11:
        nts1_req_del_count(); // value: k_nts1_tx_event_id_req_unit_count, k_param_id_del_type, sub_id=127, value=6
        break;
      case 12:
        nts1_req_del_desc(0); // unit desc: k_param_id_del_type, 0, 0, "OFF"
        break;
      case 13:
        nts1_req_rev_count(); //value: k_nts1_tx_event_id_req_unit_count, k_param_id_del_type, sub_id=127, value=6
        break;
      case 14:
        nts1_req_rev_desc(0); // unit desc: k_param_id_rev_type, 0, 0, "OFF"
        break;
      case 15:
        break;
      default:
        break;
    }
  }
}

static inline void input_set_touch(uint8_t touch_state_idx, TouchType type, int16_t value, int16_t min, int16_t max, uint8_t steps) {
  input_state.touch_states[touch_state_idx].touch_type = type;
  input_state.touch_states[touch_state_idx].value = value;
  input_state.touch_states[touch_state_idx].min_value = min;
  input_state.touch_states[touch_state_idx].max_value = max;
  input_state.touch_states[touch_state_idx].state_bits = 0;
  input_state.touch_states[touch_state_idx].state_bits_history = 0;
  input_state.touch_states[touch_state_idx].steps = steps;
}

void input_touch_init() {
  switch(input_state.mode) {
    case INPUT_MODE_OSC:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.osc.shift_shape, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.osc.shape, 0, 1023, 16);
      break;
    case INPUT_MODE_CUSTOM:
      {
        uint8_t left_idx = input_state.current_page*2;
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.osc.custom_values[left_idx],
            osc_defs[preset_state.osc.index].params[left_idx].min,
            osc_defs[preset_state.osc.index].params[left_idx].max,
            2);
        uint8_t right_idx = input_state.current_page*2+1;
        input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.osc.custom_values[right_idx],
            osc_defs[preset_state.osc.index].params[right_idx].min,
            osc_defs[preset_state.osc.index].params[right_idx].max,
            2);
      }
      break;
    case INPUT_MODE_FILTER:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.filter.peak, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.filter.cutoff, 0, 1023, 16);
      break;
    case INPUT_MODE_AMPEG:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.ampeg.attack, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.ampeg.release, 0, 1023, 16);
      break;
    case INPUT_MODE_MODFX:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.modfx.time, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.modfx.depth, 0, 1023, 16);
      break;
    case INPUT_MODE_DELFX:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.delfx.time, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.delfx.depth, 0, 1023, 16);
      break;
    case INPUT_MODE_REVFX:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.revfx.time, 0, 1023, 16);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE, preset_state.revfx.depth, 0, 1023, 16);
      break;
    case INPUT_MODE_ARP:
      if (input_state.current_page == 0) {
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.arp.index, 0, arppat_defs_size, 1);
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.arp.intervals, 0, arpint_defs_size, 1);
      } else if (input_state.current_page == 1) {
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.arp.length, 1, 16, 1); // TODO: 範囲正しい？
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.arp.state, 0, 1, 1); // TODO: 範囲正しい？
      } else {
        input_set_touch(0, TOUCH_TYPE_ROT_VALUE, preset_state.arp.tempo, 60, 120, 1); // TODO: 範囲見直し
      }
      break;
    case INPUT_MODE_SAVE:
      break;
    case INPUT_MODE_LOAD:
      break;
    case INPUT_MODE_CLEAR:
      break;
    case INPUT_MODE_GLOBAL:
      break;
    case INPUT_MODE_SCALE:
      break;
    case INPUT_MODE_TRANS:
      break;
    case INPUT_MODE_STUTTER:
      break;
    case INPUT_MODE_LFO:
      break;
    case INPUT_MODE_SEQ_SELECT:
      break;
    case INPUT_MODE_SEQ_NOTE:
      input_set_touch(0, TOUCH_TYPE_ROT_VALUE_RELATIVE, 0, -128, 127, 2);
      input_set_touch(1, TOUCH_TYPE_ROT_VALUE_RELATIVE, 0, -128, 127, 2);
      break;
    case INPUT_MODE_SEQ_OSC:
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      break;
    case INPUT_MODE_SEQ_FILTER:
      break;
    case INPUT_MODE_SEQ_AMPEG:
      break;
    case INPUT_MODE_SEQ_MODFX:
      break;
    case INPUT_MODE_SEQ_DELFX:
      break;
    case INPUT_MODE_SEQ_REVFX:
      break;
    case INPUT_MODE_SEQ_ARP:
      break;
    case INPUT_MODE_SEQ_SCALE:
      break;
    case INPUT_MODE_SEQ_TRANS:
      break;
    case INPUT_MODE_SEQ_STUTTER:
      break;
    case INPUT_MODE_SEQ_LFO:
      break;
    case INPUT_MODE_SIZE:
      break;
  }
}

static inline uint8_t input_button_is_seq_pressed() {
  return input_state.button_bits & (1<<BTN_SEQ_IDX);
}

static inline void input_edit_lr_button_handler(uint8_t is_right, uint8_t on) {
  // TODO: Touch Padを押しながらL/Rで変更する値の分解能を変更
  switch(input_state.mode) {
    case INPUT_MODE_OSC:
      if (osc_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.osc.index = (preset_state.osc.index + 1) % osc_defs_size;
          } else {
            preset_state.osc.index = (preset_state.osc.index + osc_defs_size - 1) % osc_defs_size;
          }
          nts1_param_change(k_param_id_osc_type, 0, preset_state.osc.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_CUSTOM:
      if (osc_defs[preset_state.osc.index].param_count > 2) {
        uint8_t last_page = (osc_defs[preset_state.osc.index].param_count-1) / 2;
        if (on) {
          if (is_right) {
            input_state.current_page = (input_state.current_page+1) % (last_page+1);
          } else {
            input_state.current_page = (input_state.current_page+last_page) % (last_page+1);
          }
          // TODO: temporary save
          preset_state.osc.custom_value_selected_page = input_state.current_page;
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_FILTER:
      if (filter_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.filter.index = (preset_state.filter.index + 1) % filter_defs_size;
          } else {
            preset_state.filter.index = (preset_state.filter.index + filter_defs_size - 1) % filter_defs_size;
          }
          nts1_param_change(k_param_id_filt_type, 0, preset_state.filter.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_AMPEG:
      if (ampeg_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.ampeg.index = (preset_state.ampeg.index + 1) % ampeg_defs_size;
          } else {
            preset_state.ampeg.index = (preset_state.ampeg.index + ampeg_defs_size - 1) % ampeg_defs_size;
          }
          nts1_param_change(k_param_id_ampeg_type, 0, preset_state.ampeg.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_MODFX:
      if (modfx_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.modfx.index = (preset_state.modfx.index + 1) % modfx_defs_size;
          } else {
            preset_state.modfx.index = (preset_state.modfx.index + modfx_defs_size - 1) % modfx_defs_size;
          }
          nts1_param_change(k_param_id_mod_type, 0, preset_state.modfx.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_DELFX:
      if (delfx_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.delfx.index = (preset_state.delfx.index + 1) % delfx_defs_size;
          } else {
            preset_state.delfx.index = (preset_state.delfx.index + delfx_defs_size - 1) % delfx_defs_size;
          }
          nts1_param_change(k_param_id_del_type, 0, preset_state.delfx.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_REVFX:
      if (revfx_defs_size > 1) {
        if (on) {
          if (is_right) {
            preset_state.revfx.index = (preset_state.revfx.index + 1) % revfx_defs_size;
          } else {
            preset_state.revfx.index = (preset_state.revfx.index + revfx_defs_size - 1) % revfx_defs_size;
          }
          nts1_param_change(k_param_id_rev_type, 0, preset_state.revfx.index);
          // TODO: temporary save
          input_refresh();
          input_touch_init();
        }
      }
      break;
    case INPUT_MODE_ARP:
      if (on) {
        uint8_t last_page = 2;
        if (is_right) {
          input_state.current_page = (input_state.current_page+1) % (last_page+1);
        } else {
          input_state.current_page = (input_state.current_page+last_page) % (last_page+1);
        }
        // TODO: temporary save
        input_refresh();
        input_touch_init();
      }
      break;
    case INPUT_MODE_SAVE:
      break;
    case INPUT_MODE_LOAD:
      break;
    case INPUT_MODE_CLEAR:
      break;
    case INPUT_MODE_GLOBAL:
      break;
    case INPUT_MODE_SCALE:
      break;
    case INPUT_MODE_TRANS:
      break;
    case INPUT_MODE_STUTTER:
      break;
    case INPUT_MODE_LFO:
      break;
    case INPUT_MODE_SEQ_SELECT:
      break;
    case INPUT_MODE_SEQ_NOTE:
      break;
    case INPUT_MODE_SEQ_OSC:
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      break;
    case INPUT_MODE_SEQ_FILTER:
      break;
    case INPUT_MODE_SEQ_AMPEG:
      break;
    case INPUT_MODE_SEQ_MODFX:
      break;
    case INPUT_MODE_SEQ_DELFX:
      break;
    case INPUT_MODE_SEQ_REVFX:
      break;
    case INPUT_MODE_SEQ_ARP:
      break;
    case INPUT_MODE_SEQ_SCALE:
      break;
    case INPUT_MODE_SEQ_TRANS:
      break;
    case INPUT_MODE_SEQ_STUTTER:
      break;
    case INPUT_MODE_SEQ_LFO:
      break;
    case INPUT_MODE_SIZE:
      break;
  }
}

FORCE_INLINE void input_back_to_edit_mode() {
  switch (input_state.mode) {
    case INPUT_MODE_SEQ_NOTE:
      input_state.mode = INPUT_MODE_OSC;
      break;
    case INPUT_MODE_SEQ_OSC:
      input_state.mode = INPUT_MODE_OSC;
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      input_state.mode = INPUT_MODE_CUSTOM;
      break;
    case INPUT_MODE_SEQ_FILTER:
      input_state.mode = INPUT_MODE_FILTER;
      break;
    case INPUT_MODE_SEQ_AMPEG:
      input_state.mode = INPUT_MODE_AMPEG;
      break;
    case INPUT_MODE_SEQ_MODFX:
      input_state.mode = INPUT_MODE_MODFX;
      break;
    case INPUT_MODE_SEQ_DELFX:
      input_state.mode = INPUT_MODE_DELFX;
      break;
    case INPUT_MODE_SEQ_REVFX:
      input_state.mode = INPUT_MODE_REVFX;
      break;
    case INPUT_MODE_SEQ_ARP:
      input_state.mode = INPUT_MODE_ARP;
      break;
    case INPUT_MODE_SEQ_SCALE:
      input_state.mode = INPUT_MODE_SCALE;
      break;
    case INPUT_MODE_SEQ_TRANS:
      input_state.mode = INPUT_MODE_TRANS;
      break;
    case INPUT_MODE_SEQ_STUTTER:
      input_state.mode = INPUT_MODE_STUTTER;
      break;
    case INPUT_MODE_SEQ_LFO:
      input_state.mode = INPUT_MODE_LFO;
      break;
    default:
      break;
  }
}

FORCE_INLINE void input_toggle_run_state() {
  if (seq.run_state) {
    seq.stop();
  } else {
    seq.start();
  }
}

FORCE_INLINE void input_button_seq_mode_handler(uint8_t button_idx, uint8_t on) {
  switch(button_idx) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      {
        uint16_t bit = (uint16_t)1<<button_idx;
        if (on) {
          if ((uint16_t)input_state.button_bits == bit) {
            input_state.seq_selected_steps = bit;
          } else {
            input_state.seq_selected_steps |= bit;
          }
        }
      }
      break;
    case BTN_SEQ_IDX:
      input_back_to_edit_mode();
      break;
    case BTN_RUN_IDX:
      input_toggle_run_state();
      break;
    case BTN_L_IDX:
      break;
    case BTN_R_IDX:
      break;
    default:
      break;
  }
}

FORCE_INLINE void input_button_edit_mode_handler(uint8_t button_idx, uint8_t on) {
  volatile static uint8_t _input_planned_seq_mode = 255;

  if (input_button_is_seq_pressed()) {
    switch(button_idx) {
      case 0:
        _input_planned_seq_mode = INPUT_MODE_SEQ_OSC;
        break;
      case 1:
        _input_planned_seq_mode = INPUT_MODE_SEQ_CUSTOM;
        break;
      case 2:
        _input_planned_seq_mode = INPUT_MODE_SEQ_FILTER;
        break;
      case 3:
        _input_planned_seq_mode = INPUT_MODE_SEQ_AMPEG;
        break;
      case 4:
        _input_planned_seq_mode = INPUT_MODE_SEQ_MODFX;
        break;
      case 5:
        _input_planned_seq_mode = INPUT_MODE_SEQ_DELFX;
        break;
      case 6:
        _input_planned_seq_mode = INPUT_MODE_SEQ_REVFX;
        break;
      case 7:
        _input_planned_seq_mode = INPUT_MODE_SEQ_ARP;
        break;
      case 8: // save
        break;
      case 9: // load
        break;
      case 10: // clear
        break;
      case 11: // global
        break;
      case 12:
        _input_planned_seq_mode = INPUT_MODE_SEQ_SCALE;
        break;
      case 13:
        _input_planned_seq_mode = INPUT_MODE_SEQ_TRANS;
        break;
      case 14:
        _input_planned_seq_mode = INPUT_MODE_SEQ_STUTTER;
        break;
      case 15:
        _input_planned_seq_mode = INPUT_MODE_SEQ_LFO;
        break;
      case BTN_SEQ_IDX:
        if (on) {
          _input_planned_seq_mode = INPUT_MODE_SEQ_NOTE;
          input_state.mode = INPUT_MODE_SEQ_SELECT;
        }
        break;
      case BTN_RUN_IDX:
        break;
      case BTN_L_IDX:
        break;
      case BTN_R_IDX:
        break;
      default:
        break;
    }
  } else {
    switch(button_idx) {
      case 0:
        if (on) {
          input_state.mode = INPUT_MODE_OSC;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 1:
        if (on) {
          input_state.mode = INPUT_MODE_CUSTOM;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 2:
        if (on) {
          input_state.mode = INPUT_MODE_FILTER;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 3:
        if (on) {
          input_state.mode = INPUT_MODE_AMPEG;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 4:
        if (on) {
          input_state.mode = INPUT_MODE_MODFX;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 5:
        if (on) {
          input_state.mode = INPUT_MODE_DELFX;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 6:
        if (on) {
          input_state.mode = INPUT_MODE_REVFX;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 7:
        if (on) {
          input_state.mode = INPUT_MODE_ARP;
          screen_set_mode(SCREEN_MODE_EDIT);
        }
        break;
      case 8:
        input_state.mode = INPUT_MODE_SAVE;
        break;
      case 9:
        input_state.mode = INPUT_MODE_LOAD;
        break;
      case 10:
        input_state.mode = INPUT_MODE_CLEAR;
        break;
      case 11:
        input_state.mode = INPUT_MODE_GLOBAL;
        break;
      case 12:
        input_state.mode = INPUT_MODE_SCALE;
        break;
      case 13:
        input_state.mode = INPUT_MODE_TRANS;
        break;
      case 14:
        input_state.mode = INPUT_MODE_STUTTER;
        break;
      case 15:
        input_state.mode = INPUT_MODE_LFO;
        break;
      case BTN_SEQ_IDX:
        if (!on) {
          if (INPUT_MODE_SEQ_NOTE <= _input_planned_seq_mode && _input_planned_seq_mode <= INPUT_MODE_SEQ_LFO) {
            input_state.mode = _input_planned_seq_mode;
            screen_set_mode(SCREEN_MODE_SEQ_NOTE);
          } else {
            input_state.mode = INPUT_MODE_SEQ_NOTE;
            screen_set_mode(SCREEN_MODE_SEQ_NOTE);
          }
        }
        break;
      case BTN_RUN_IDX:
        input_toggle_run_state();
        break;
      case BTN_L_IDX:
        input_edit_lr_button_handler(0, on);
        break;
      case BTN_R_IDX:
        input_edit_lr_button_handler(1, on);
        break;
      default:
        break;
    }
  }
}

void input_button_handler(uint8_t button_idx, uint8_t on) {
  uint8_t prev_mode = input_state.mode;
  input_state.button_bits = (input_state.button_bits & ~(1<<button_idx)) | (!!on<<button_idx);
  if (INPUT_MODE_SEQ_START <= input_state.mode && input_state.mode <= INPUT_MODE_SEQ_END) {
    input_button_seq_mode_handler(button_idx, on);
  } else {
    input_button_edit_mode_handler(button_idx, on);
  }
  if (prev_mode != input_state.mode) {
    if (input_state.mode == INPUT_MODE_CUSTOM) {
      input_state.current_page = preset_state.osc.custom_value_selected_page;
    } else {
      input_state.current_page = 0;
    }
    input_refresh();
    input_touch_init();
  }
}

void input_setup() {
  touch_event_listen(input_touch_handler);

  uint8_t matrix_idx = button_register_matrix(0, 4, 4);
  button_register_matrix_row_pin(matrix_idx, 0, PIN_B11);
  button_register_matrix_row_pin(matrix_idx, 1, PIN_B10);
  button_register_matrix_row_pin(matrix_idx, 2, PIN_C2);
  button_register_matrix_row_pin(matrix_idx, 3, PIN_C3);
  button_register_matrix_col_pin(matrix_idx, 0, PIN_A4);
  button_register_matrix_col_pin(matrix_idx, 1, PIN_C4);
  button_register_matrix_col_pin(matrix_idx, 2, PIN_C6);
  button_register_matrix_col_pin(matrix_idx, 3, PIN_C7);

  button_register_single(BTN_SEQ_IDX, BTN_SEQ_PIN);
  button_register_single(BTN_RUN_IDX, BTN_RUN_PIN);
  button_register_single(BTN_L_IDX, BTN_L_PIN);
  button_register_single(BTN_R_IDX, BTN_R_PIN);

  //button_event_listen(input_button_debug_handler);
  button_event_listen(input_button_handler);

  input_state.touch_bits = 0;
  for (uint8_t i=0; i<9; ++i) {
    input_state.touch_values[i] = 0;
  }

 touch_value_init(&(input_state.touch_states[0]));
 touch_value_init(&(input_state.touch_states[1]));
}

void input_refresh() {
  screen_edit_clear();
  if (input_state.mode < INPUT_MODE_SIZE) {
    screen_edit_set_title(input_mode_names[input_state.mode], 16);
  }
  switch(input_state.mode) {
    case INPUT_MODE_OSC:
      {
        //screen_edit_set_page(1, 1);
        screen_edit_set_type(osc_defs[preset_state.osc.index].name, PARAM_NAME_LEN);
        screen_edit_set_param_name(0, "ShiftSh", 7);
        screen_edit_set_param_name(1, "Shape", 5);
        screen_edit_set_param_value(0, preset_state.osc.shift_shape);
        screen_edit_set_param_value(1, preset_state.osc.shape);
      }
      break;
    case INPUT_MODE_CUSTOM:
      {
        //screen_edit_set_page(input_state.current_page+1, osc_defs[preset_state.osc.index].param_count / 2);
        if (osc_defs[preset_state.osc.index].param_count > 0) {
          char page_text[8] = {
            'P', 'a', 'g', 'e', ' ',
            input_state.current_page+1+48,
            '/',
            (((osc_defs[preset_state.osc.index].param_count+1) / 2) % 10)+48
          };
          screen_edit_set_type(page_text, 8);
          char* param_name = osc_defs[preset_state.osc.index].params[input_state.current_page*2].name;
          screen_edit_set_param_name(0, param_name, PARAM_NAME_LEN);
          screen_edit_set_param_value(0, preset_state.osc.custom_values[input_state.current_page*2]);

          uint8_t is_last_page = input_state.current_page == (osc_defs[preset_state.osc.index].param_count / 2);
          if (!is_last_page || (osc_defs[preset_state.osc.index].param_count % 2) == 0) {
            char* param_name2 = osc_defs[preset_state.osc.index].params[input_state.current_page*2+1].name;
            screen_edit_set_param_name(1, param_name2, PARAM_NAME_LEN);
            screen_edit_set_param_value(1, preset_state.osc.custom_values[input_state.current_page*2+1]);
          }
        } else {
          screen_edit_set_type("No Param", PARAM_NAME_LEN);
        }
      }
      break;
    case INPUT_MODE_FILTER:
      //screen_edit_set_page(1, 1);
      screen_edit_set_type(filter_defs[preset_state.filter.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_name(0, "Peak", 4);
      screen_edit_set_param_name(1, "Cutoff", 6);
      screen_edit_set_param_value(0, preset_state.filter.peak);
      screen_edit_set_param_value(1, preset_state.filter.cutoff);
      break;
    case INPUT_MODE_AMPEG:
      //screen_edit_set_page(1, 1);
      screen_edit_set_type(ampeg_defs[preset_state.ampeg.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_name(0, "Attack", 6);
      screen_edit_set_param_name(1, "Release", 7);
      screen_edit_set_param_value(0, preset_state.ampeg.attack);
      screen_edit_set_param_value(1, preset_state.ampeg.release);
      break;
    case INPUT_MODE_MODFX:
      //screen_edit_set_page(1, 1);
      screen_edit_set_type(modfx_defs[preset_state.modfx.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_name(0, "Time", 4);
      screen_edit_set_param_name(1, "Depth", 5);
      screen_edit_set_param_value(0, preset_state.modfx.time);
      screen_edit_set_param_value(1, preset_state.modfx.depth);
      break;
    case INPUT_MODE_DELFX:
      //screen_edit_set_page(1, 1);
      screen_edit_set_type(delfx_defs[preset_state.delfx.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_name(0, "Time", 4);
      screen_edit_set_param_name(1, "Depth", 5);
      screen_edit_set_param_value(0, preset_state.delfx.time);
      screen_edit_set_param_value(1, preset_state.delfx.depth);
      break;
    case INPUT_MODE_REVFX:
      //screen_edit_set_page(1, 1);
      screen_edit_set_type(revfx_defs[preset_state.revfx.index].name, PARAM_NAME_LEN);
      screen_edit_set_param_name(0, "Time", 4);
      screen_edit_set_param_name(1, "Depth", 5);
      screen_edit_set_param_value(0, preset_state.revfx.time);
      screen_edit_set_param_value(1, preset_state.revfx.depth);
      break;
    case INPUT_MODE_ARP:
      //screen_edit_set_page(1, 1);
      {
        char page_text[8] = {
          'P', 'a', 'g', 'e', ' ',
            input_state.current_page+1+48,
          '/', '3'
        };
        screen_edit_set_type(page_text, 8);
        if (input_state.current_page == 0) {
          screen_edit_set_param_name(0, "Type", 4);
          screen_edit_set_param_name(1, "Interval", 8);
          // TODO: defs からパラメータ名を拾ってくる
          screen_edit_set_param_value_text(0, arppat_defs[preset_state.arp.index].name, PARAM_NAME_LEN);
          screen_edit_set_param_value_text(1, arpint_defs[preset_state.arp.intervals].name, PARAM_NAME_LEN);
        } else if (input_state.current_page == 1) {
          screen_edit_set_param_name(0, "Length", 6);
          screen_edit_set_param_name(1, "State", 5);
          screen_edit_set_param_value(0, preset_state.arp.length);
          screen_edit_set_param_value(1, preset_state.arp.state);
        } else {
          screen_edit_set_param_name(0, "Tempo", 5);
          screen_edit_set_param_value(0, preset_state.arp.tempo);
        }
      }
      break;
    case INPUT_MODE_SAVE:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_LOAD:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_CLEAR:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_GLOBAL:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SCALE:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_TRANS:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_STUTTER:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_LFO:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_SELECT:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_NOTE:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_OSC:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_CUSTOM:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_FILTER:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_AMPEG:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_MODFX:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_DELFX:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_REVFX:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_ARP:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_SCALE:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_TRANS:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_STUTTER:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SEQ_LFO:
      //screen_edit_set_page(1, 1);
      break;
    case INPUT_MODE_SIZE:
      break;
  }
  screen_set_dirty();
}

void input_process() {
}
