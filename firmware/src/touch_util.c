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
  value->state_bits_history = 0;
  value->max_value = 32;
  value->min_value = 0;
  value->steps = 2;
}

static inline uint8_t touch_util_is_center_pressed(TouchState* value) {
  return value->state_bits & 0b1000;
}

static inline uint8_t touch_util_switch_process(TouchState* value, uint8_t new_state_bits) {
  int8_t rot_value_current = touch_util_state_bits_to_idx[new_state_bits];
  int16_t prev_value = value->value;
  if (rot_value_current == TOUCH_NO_VALUE) {
    value->value = TOUCH_NO_VALUE;
  } else if (rot_value_current == TOUCH_HOLD_VALUE) {
  } else {
    value->value = rot_value_current / 2;
  }
  return prev_value != value->value;
}

static inline uint8_t touch_util_rot_switch_process(TouchState* value, uint8_t new_state_bits) {
  int8_t v = touch_util_state_bits_to_idx[new_state_bits];
  if (v != TOUCH_HOLD_VALUE) {
    value->value = touch_util_state_bits_to_idx[new_state_bits];
    return 1;
  }
  return 0;
}

static inline uint8_t touch_util_rot_value_process(TouchState* value, uint8_t new_state_bits) {
  //int8_t rot_value_prev = touch_util_state_bits_to_idx[value->state_bits];
  //int8_t rot_value_current = touch_util_state_bits_to_idx[new_state_bits];
  if (!(new_state_bits & 0b0111)) {
    // released
    return 0;
  }
  int16_t prev_value = value->value;
  int8_t rot_value_prev = touch_util_state_bits_to_idx[(value->state_bits_history >> (4*2)) & 0x0F];
  int8_t rot_value_current = touch_util_state_bits_to_idx[(value->state_bits_history >> (4*1)) & 0x0F];
  if (rot_value_prev != rot_value_current
      && rot_value_current >= 0 && rot_value_prev >= 0) {
    if (rot_value_current == (rot_value_prev + 1) % 6) {
      // move high position
      if (value->value < value->max_value) {
        volatile int16_t tmp = value->value;
        if (touch_util_is_center_pressed(value)) {
          tmp += 1;
        } else {
          tmp += value->steps;
        }
        value->value = (tmp < (value->max_value) ? tmp : (value->max_value));
      }
    } else if (rot_value_current == (rot_value_prev + 5) % 6) {
      // move low position
      if (value->value > value->min_value) {
        volatile int16_t tmp = value->value;
        if (touch_util_is_center_pressed(value)) {
          tmp -= 1;
        } else {
          tmp -= value->steps;
        }
        value->value = (tmp > (value->min_value) ? tmp : (value->min_value));
      }
    }
  } else if (rot_value_current == TOUCH_HOLD_VALUE) {
  } else if (rot_value_current == TOUCH_NO_VALUE) {
  }
  return prev_value != value->value;
}

static inline uint8_t touch_util_rot_value_relative_process(TouchState* value, uint8_t new_state_bits) {
  //int8_t rot_value_prev = touch_util_state_bits_to_idx[value->state_bits];
  //int8_t rot_value_current = touch_util_state_bits_to_idx[new_state_bits];
  if (!(new_state_bits & 0b0111)) {
    // released
    return 0;
  }
  uint8_t is_changed = 0;
  int8_t rot_value_prev = touch_util_state_bits_to_idx[(value->state_bits_history >> (4*2)) & 0x0F];
  int8_t rot_value_current = touch_util_state_bits_to_idx[(value->state_bits_history >> (4*1)) & 0x0F];
  if (rot_value_prev != rot_value_current
      && rot_value_current >= 0 && rot_value_prev >= 0) {
    if (rot_value_current == (rot_value_prev + 1) % 6) {
      // move high position
      volatile int16_t tmp = value->value;
      if (touch_util_is_center_pressed(value)) {
        value->value = 1;
      } else {
        value->value = value->steps;
      }
      is_changed = 1;
    } else if (rot_value_current == (rot_value_prev + 5) % 6) {
      // move low position
      volatile int16_t tmp = value->value;
      if (touch_util_is_center_pressed(value)) {
        value->value = -1;
      } else {
        value->value = -(value->steps);
      }
      is_changed = 1;
    }
  } else if (rot_value_current == TOUCH_HOLD_VALUE) {
  } else if (rot_value_current == TOUCH_NO_VALUE) {
  }
  return is_changed;
}


uint8_t touch_util_process(uint8_t state_bits, TouchState* value) {
  value->state_bits_history <<= 4;
  value->state_bits_history |= state_bits & 0x0F;
  uint8_t is_changed = 0;
  switch (value->touch_type) {
    case TOUCH_TYPE_SWITCH:
      is_changed = touch_util_switch_process(value, state_bits);
      break;
    case TOUCH_TYPE_ROT_SWITCH:
      is_changed = touch_util_rot_switch_process(value, state_bits);
      break;
    case TOUCH_TYPE_ROT_VALUE:
      is_changed = touch_util_rot_value_process(value, state_bits);
      break;
    case TOUCH_TYPE_ROT_VALUE_RELATIVE:
      is_changed = touch_util_rot_value_relative_process(value, state_bits);
      break;
  }
  value->state_bits = state_bits;
  return is_changed;
}
