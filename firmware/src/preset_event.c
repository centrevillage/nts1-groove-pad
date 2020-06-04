#include "preset_event.h"

#define PRESET_EVENT_BUF_SIZE 64

volatile PresetEvent preset_event_buffer[PRESET_EVENT_BUF_SIZE];
volatile uint16_t preset_event_buffer_end_idx = 0;
volatile uint16_t preset_event_buffer_read_idx = 0;

uint8_t preset_event_is_empty() {
  return preset_event_buffer_end_idx == preset_event_buffer_read_idx;
}

void preset_event_add(PresetEvent preset_event) {
  preset_event_buffer[preset_event_buffer_end_idx] = preset_event;
  preset_event_buffer_end_idx = (preset_event_buffer_end_idx + 1) % PRESET_EVENT_BUF_SIZE;
}

PresetEvent preset_event_get() {
  PresetEvent event = {0};
  if (preset_event_buffer_end_idx != preset_event_buffer_read_idx) {
    event = preset_event_buffer[preset_event_buffer_read_idx];
    preset_event_buffer_read_idx = (preset_event_buffer_read_idx + 1) % PRESET_EVENT_BUF_SIZE;
  }
  return event;
}

