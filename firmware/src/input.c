#include "input.h"
#include "touch.h"
#include "oled.h"

__IO InputState input_state = {0};

void input_touch_handler(uint8_t touch_idx, uint8_t on) {
  input_state.touch_bits = (input_state.touch_bits & ~(1<<touch_idx)) | ((on ? 1 : 0)<<touch_idx);
}

void input_setup() {
  touch_event_listen(input_touch_handler);
}
