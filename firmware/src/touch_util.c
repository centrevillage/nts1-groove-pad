#include "touch_util.h"

const int8_t touch_util_state_bits_to_idx[16] = {
  // 0b0000
  TOUCH_NO_VALUE,
  // 0b0001
  0,
  // 0b0010
  2,
  // 0b0011
  1,
  // 0b0100
  4,
  // 0b0101
  5,
  // 0b0110
  3,
  // 0b0111
  TOUCH_HOLD_VALUE,
  // 0b1000
  TOUCH_NO_VALUE,
  // 0b1001
  0,
  // 0b1010
  2,
  // 0b1011
  1,
  // 0b1100
  4,
  // 0b1101
  5,
  // 0b1110
  3,
  // 0b1111
  TOUCH_HOLD_VALUE,
};

void touch_value_init(TouchState* value) {
  value->touch_type = TOUCH_TYPE_SWITCH;
  value->value = TOUCH_NO_VALUE;
  value->state_bits = 0;
  value->max_value = 32;
  value->min_value = 0;
  value->steps = 2;
}

static inline uint8_t touch_util_is_center_pressed(TouchState* value) {
  return value->state_bits & 0b1000;
}

static inline void touch_util_switch_process(uint8_t key_idx, uint8_t press_state, TouchState* value, uint8_t new_state_bits) {
  int8_t rot_value_current = touch_util_state_bits_to_idx[new_state_bits];
  if (rot_value_current == TOUCH_NO_VALUE) {
    value->value = TOUCH_NO_VALUE;
  } else if (rot_value_current == TOUCH_HOLD_VALUE) {
  } else {
    value->value = rot_value_current / 2;
  }
}

static inline void touch_util_rot_switch_process(uint8_t key_idx, uint8_t press_state, TouchState* value, uint8_t new_state_bits) {
  int8_t v = touch_util_state_bits_to_idx[new_state_bits];
  if (v != TOUCH_HOLD_VALUE) {
    value->value = touch_util_state_bits_to_idx[new_state_bits];
  }
}

// TODO: 指を離したときに値がずれるのを抑止
static inline void touch_util_rot_value_process(uint8_t key_idx, uint8_t press_state, TouchState* value, uint8_t new_state_bits) {
  int8_t rot_value_prev = touch_util_state_bits_to_idx[value->state_bits];
  int8_t rot_value_current = touch_util_state_bits_to_idx[new_state_bits];
  if (rot_value_prev != rot_value_current
      && rot_value_current >= 0 && rot_value_prev >= 0) {
    if (rot_value_current == (rot_value_prev + 1) % 6) {
      // move high position
      if (value->value < value->max_value) {
        int16_t tmp = value->value;
        if (touch_util_is_center_pressed(value)) {
          tmp += 1;
        } else {
          tmp += value->steps;
        }
        value->value = tmp < value->max_value ? tmp : value->max_value;
      }
    } else if (rot_value_current == (rot_value_prev + 5) % 6) {
      // move low position
      if (value->value > value->min_value) {
        int16_t tmp = value->value;
        if (touch_util_is_center_pressed(value)) {
          tmp -= 1;
        } else {
          tmp -= value->steps;
        }
        value->value = tmp > value->min_value ? tmp : value->min_value;
      }
    }
  } else if (rot_value_current == TOUCH_HOLD_VALUE) {
  } else if (rot_value_current == TOUCH_NO_VALUE) {
  }
}


int16_t touch_util_process(uint8_t key_idx, uint8_t press_state, TouchState* value) {
  uint8_t state_bits = ((value->state_bits) & ~(1<<key_idx)) | (press_state << key_idx);
  switch (value->touch_type) {
    case TOUCH_TYPE_SWITCH:
      touch_util_switch_process(key_idx, press_state, value, state_bits);
      break;
    case TOUCH_TYPE_ROT_SWITCH:
      touch_util_rot_switch_process(key_idx, press_state, value, state_bits);
      break;
    case TOUCH_TYPE_ROT_VALUE:
      touch_util_rot_value_process(key_idx, press_state, value, state_bits);
      break;
  }
  value->state_bits = state_bits;
  return value->value;
}
