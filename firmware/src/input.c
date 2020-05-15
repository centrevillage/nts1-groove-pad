#include "input.h"
#include "touch.h"
#include "oled.h"
#include "button.h"
#include "led.h"

#define BTN_MODE_IDX 16
#define BTN_RUN_IDX  17
#define BTN_L_IDX    18
#define BTN_R_IDX    19

#define BTN_MODE_PIN PIN_A11
#define BTN_RUN_PIN  PIN_C1
#define BTN_L_PIN    PIN_A8
#define BTN_R_PIN    PIN_A15

__IO InputState input_state = {0};

void input_touch_handler(uint8_t touch_idx, uint8_t on, uint32_t value) {
  input_state.touch_bits = (input_state.touch_bits & ~(1<<touch_idx)) | ((on ? 1 : 0)<<touch_idx);
  input_state.touch_values[touch_idx] = value;
}

void input_button_handler(uint8_t button_idx, uint8_t on) {
  if (button_idx < 18) {
    led_set(button_idx, on);
  }
  static char buf[16] = "BTN:";
  if (on) {
    text_0x_from_uint8(&(buf[4]), button_idx);
    debug_text(buf, 6); 
  } else {
    debug_text("", 0); 
  }
}

void input_setup() {
  input_state.touch_bits = 0;
  for (uint8_t i=0; i<9; ++i) {
    input_state.touch_values[i] = 0;
  }
  touch_event_listen(input_touch_handler);

  uint8_t matrix_idx = button_register_matrix(0, 4, 4);
  button_register_matrix_row_pin(matrix_idx, 0, PIN_B11);
  button_register_matrix_row_pin(matrix_idx, 1, PIN_B10);
  button_register_matrix_row_pin(matrix_idx, 2, PIN_C2);
  button_register_matrix_row_pin(matrix_idx, 3, PIN_C3);
  button_register_matrix_col_pin(matrix_idx, 0, PIN_A4);
  button_register_matrix_col_pin(matrix_idx, 1, PIN_C4);
  button_register_matrix_col_pin(matrix_idx, 2, PIN_C6);
  button_register_matrix_col_pin(matrix_idx, 3, PIN_C7);

  button_register_single(BTN_MODE_IDX, BTN_MODE_PIN);
  button_register_single(BTN_RUN_IDX, BTN_RUN_PIN);
  button_register_single(BTN_L_IDX, BTN_L_PIN);
  button_register_single(BTN_R_IDX, BTN_R_PIN);

  button_event_listen(input_button_handler);
}