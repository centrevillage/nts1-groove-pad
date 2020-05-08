#ifndef __N1GP_INPUT_H__
#define __N1GP_INPUT_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t touch_bits;
} InputState;

extern __IO InputState input_state;

void input_touch_key_press(uint8_t type_idx, uint8_t key_idx);
void input_touch_key_leave(uint8_t type_idx, uint8_t key_idx);
void input_setup();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_INPUT_H__ */
