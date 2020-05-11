#include "input.h"
#include "touch.h"
#include "oled.h"

__IO InputState input_state = {0};

void input_touch_handler(uint8_t touch_idx, uint8_t on, uint32_t value) {
  input_state.touch_bits = (input_state.touch_bits & ~(1<<touch_idx)) | ((on ? 1 : 0)<<touch_idx);
  input_state.touch_values[touch_idx] = value;
}

void input_setup() {
  input_state.touch_bits = 0;
  for (uint8_t i=0; i<9; ++i) {
    input_state.touch_values[i] = 0;
  }
  touch_event_listen(input_touch_handler);
}
