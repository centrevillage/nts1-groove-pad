#ifndef N1GP_APP_INPUT_CUSTOM_H
#define N1GP_APP_INPUT_CUSTOM_H

#include <app_input/base.hpp>

struct AppInputCustom {
  uint8_t current_page = 0;
  uint8_t last_page = 0;

  inline void init() {
    app_screen.changeMode(AppScreenEdit {});
    current_page = 0;
    last_page = (osc_defs[preset_state.osc.index].param_count-1) / 2;
  }
  inline void touch(uint8_t touch_idx, bool on) {
  }

  inline void _incValue(uint8_t param_idx, int16_t inc_value) {
    volatile const OscDef& osc_def = osc_defs[preset_state.osc.index & 0x0F];
    volatile const ParamDef& param_def = osc_def.params[std::clamp<uint8_t>(param_idx, (uint8_t)0, (uint8_t)osc_def.param_count)];
    int16_t value = std::clamp<int16_t>(preset_state.osc.custom_values[param_idx] + inc_value, param_def.min, param_def.max);
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
    if (!app_screen.isMode<AppScreenEdit>()) { return; }
    auto& screen_mode = app_screen.getMode<AppScreenEdit>();
    screen_mode.setTitle("Custom", 16);
    if (osc_defs[preset_state.osc.index].param_count > 0) {
      char page_text[8] = {
        'P', 'a', 'g', 'e', ' ',
        current_page+1+48,
        '/',
        (((osc_defs[preset_state.osc.index].param_count+1) / 2) % 10)+48
      };
      screen_mode.setType(page_text, 8);
      char* param_name = osc_defs[preset_state.osc.index].params[current_page*2].name;
      screen_mode.setParamName(0, param_name, PARAM_NAME_LEN);
      screen_mode.setParamValue(0, preset_state.osc.custom_values[current_page*2]);

      uint8_t is_last_page = current_page == (osc_defs[preset_state.osc.index].param_count / 2);
      if (!is_last_page || (osc_defs[preset_state.osc.index].param_count % 2) == 0) {
        char* param_name2 = osc_defs[preset_state.osc.index].params[current_page*2+1].name;
        screen_mode.setParamName(1, param_name2, PARAM_NAME_LEN);
        screen_mode.setParamValue(1, preset_state.osc.custom_values[current_page*2+1]);
      }
    } else {
      screen_mode.setType("No Param", PARAM_NAME_LEN);
    }
  }
};


#endif /* N1GP_APP_INPUT_CUSTOM_H */