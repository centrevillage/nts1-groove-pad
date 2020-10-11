#ifndef N1GP_APP_INPUT_CUSTOM_H
#define N1GP_APP_INPUT_CUSTOM_H

#include <app_input/base.hpp>

struct AppInputCustom {
  uint8_t current_page = 0;
  uint8_t last_page = 0;

  inline void init() {
    current_page = 0;
    last_page = (osc_defs[preset_state.osc.index].param_count-1) / 2;
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
          if (on) {
            current_page = (current_page+last_page) % (last_page+1);
            preset_state.osc.custom_value_selected_page = current_page;
          }
        }
        return true;
      case AppBtnID::R:
        if (on) {
          current_page = (current_page+1) % (last_page+1);
          preset_state.osc.custom_value_selected_page = current_page;
        }
        return true;
      default:
        break;
    }
    return false;
  }
  inline void refresh() {
    screen_edit_set_title("Custom", 16);
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


#endif /* N1GP_APP_INPUT_CUSTOM_H */
