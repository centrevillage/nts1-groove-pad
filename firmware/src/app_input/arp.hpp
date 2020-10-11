#ifndef N1GP_APP_INPUT_ARP_H
#define N1GP_APP_INPUT_ARP_H

#include <app_input/base.hpp>

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
    screen_edit_set_title("ARP", 16);
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


#endif /* N1GP_APP_INPUT_ARP_H */
