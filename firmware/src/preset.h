#ifndef __N1GP_PRESET_H__
#define __N1GP_PRESET_H__

#include "state.h"

#ifdef __cplusplus
extern "C" {
#endif

// active states
extern volatile PresetState preset_state;
extern volatile SeqState seq_state;
extern volatile GlobalState global_state;

void preset_setup();

void preset_temporary_save();
void preset_save(uint8_t idx);
void preset_seq_save(uint8_t idx);
void preset_global_save();

void preset_load(uint8_t idx);
void preset_seq_load(uint8_t idx);
void preset_global_load();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_PRESET_H__ */
