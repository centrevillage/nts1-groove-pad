#ifndef __N1GP_PRESET_EVENT_H__
#define __N1GP_PRESET_EVENT_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  PST_EVT_NONE = 0,
  PST_EVT_PRESET_SAVE,
  PST_EVT_PRESET_LOAD,

  PST_EVT_PRESET_TMP_SAVE,
  PST_EVT_PRESET_TMP_LOAD,

  PST_EVT_OSC_SHAPE_TMP_SAVE,
};

typedef struct {
  uint8_t command_id;
  uint8_t target_id;
  int16_t value;
} PresetEvent;

void preset_event_add(PresetEvent preset_event);
PresetEvent preset_event_get();
uint8_t preset_event_is_empty();

static inline void preset_event_create(uint8_t command_id, uint8_t target_id, int16_t value) {
  PresetEvent event = {command_id, target_id, value}; 
  preset_event_add(event);
}

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_PRESET_EVENT_H__ */
