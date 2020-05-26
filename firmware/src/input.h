#ifndef __N1GP_INPUT_H__
#define __N1GP_INPUT_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  INPUT_MODE_OSC = 0,
  INPUT_MODE_CUSTOM,
  INPUT_MODE_FILTER,
  INPUT_MODE_AMPEG,
  INPUT_MODE_MODFX,
  INPUT_MODE_DELFX,
  INPUT_MODE_REVFX,
  INPUT_MODE_ARP,
  INPUT_MODE_SAVE,
  INPUT_MODE_LOAD,
  INPUT_MODE_CLEAR,
  INPUT_MODE_GLOBAL,
  INPUT_MODE_SCALE,
  INPUT_MODE_TRANS,
  INPUT_MODE_STUTTER,
  INPUT_MODE_LFO,

  INPUT_MODE_SEQ_SELECT,
  INPUT_MODE_SEQ_NOTE,
  INPUT_MODE_SEQ_OSC,
  INPUT_MODE_SEQ_CUSTOM,
  INPUT_MODE_SEQ_FILTER,
  INPUT_MODE_SEQ_AMPEG,
  INPUT_MODE_SEQ_MODFX,
  INPUT_MODE_SEQ_DELFX,
  INPUT_MODE_SEQ_REVFX,
  INPUT_MODE_SEQ_ARP,
  INPUT_MODE_SEQ_SCALE,
  INPUT_MODE_SEQ_TRANS,
  INPUT_MODE_SEQ_STUTTER,
  INPUT_MODE_SEQ_LFO,

  INPUT_MODE_SIZE,
} InputMode;

static const char* input_mode_names[INPUT_MODE_SIZE] = {
  "OSC",
  "Custom",
  "Filter",
  "AmpEG",
  "ModFX",
  "DelFX",
  "RevFX",
  "ARP",
  "Save",
  "Load",
  "Clear",
  "Global",
  "Scale",
  "Transpose",
  "Stutter",
  "LFO",

  "SEQ:Select",
  "SEQ:Note",
  "SEQ:OSC",
  "SEQ:Custom",
  "SEQ:Filter",
  "SEQ:AmpEG",
  "SEQ:ModFX",
  "SEQ:DelFX",
  "SEQ:RevFX",
  "SEQ:ARP",
  "SEQ:Scale",
  "SEQ:Transpose",
  "SEQ:Stutter",
  "SEQ:LFO",
};

typedef struct {
  uint8_t touch_bits;
  uint32_t touch_values[9];
  uint32_t button_bits;
  InputMode mode;
  uint8_t current_page;
} InputState;

extern volatile InputState input_state;

void input_setup();
void input_refresh();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_INPUT_H__ */
