#include "event_buf.h"

void event_buf_add_u8(EventStateU8* state, uint8_t event) {
  state->buf[state->end_idx] = event;
  state->end_idx = (state->end_idx + 1) % 256;
}

EventDataU8 event_buf_get_u8(EventStateU8* state) {
  EventDataU8 result;
  result.valid = 0;
  if (state->read_idx != state->end_idx) {
    result.data = state->buf[state->read_idx];
    result.valid = 1;
    state->read_idx = (state->read_idx + 1) % 256;
  }
  return result;
}

uint8_t event_buf_is_empty_u8(EventStateU8* state) {
  return state->read_idx == state->end_idx;
}

