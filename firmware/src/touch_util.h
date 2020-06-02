#ifndef __N1GP_TOUCH_UTIL_H__
#define __N1GP_TOUCH_UTIL_H__

#include "main.h"

#define TOUCH_NO_VALUE -128
#define TOUCH_HOLD_VALUE -127

typedef enum {
  TOUCH_TYPE_SWITCH = 0,
  TOUCH_TYPE_ROT_SWITCH,
  TOUCH_TYPE_ROT_VALUE,
} TouchType;

typedef struct {
  uint8_t touch_type; 
  int16_t value;
  int16_t max_value;
  int16_t min_value;
  uint8_t state_bits;
  uint32_t state_bits_history;
  uint8_t steps;
} TouchState;

void touch_value_init(TouchState* value);
int16_t touch_util_process(uint8_t state_bits, TouchState* value);

#endif /* __N1GP_TOUCH_UTIL_H__ */
