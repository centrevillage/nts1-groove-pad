#ifndef __N1GP_INPUT_H__
#define __N1GP_INPUT_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t touch_bits;
  uint32_t touch_values[9];
} InputState;

extern __IO InputState input_state;

void input_setup();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_INPUT_H__ */