#include "preset.h"

volatile SeqState seq_state;
volatile PresetState preset_state;
volatile GlobalState global_state;

void preset_setup() {
  state_reset_preset(&preset_state);
  state_reset_global(&global_state);
  state_reset_seq(&seq_state);
}

void preset_temporary_save() {
}

void preset_save(uint8_t idx) {
}

void preset_seq_save(uint8_t idx) {
}

void preset_global_save() {
}


void preset_load(uint8_t idx) {
}

void preset_seq_load(uint8_t idx) {
}

void preset_global_load() {
}

