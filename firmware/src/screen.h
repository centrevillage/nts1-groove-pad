#ifndef __N1GP_SCREEN_H__
#define __N1GP_SCREEN_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SCREEN_MODE_OSC = 0,
  SCREEN_MODE_FILTER,
  SCREEN_MODE_EG,
  SCREEN_MODE_MOD,
  SCREEN_MODE_DELAY,
  SCREEN_MODE_REVERB,
  SCREEN_MODE_LFO,
  SCREEN_MODE_SEQ,
  SCREEN_MODE_SAVE,
  SCREEN_MODE_LOAD,
  SCREEN_MODE_CLEAR,
  SCREEN_MODE_SCALE,
  SCREEN_MODE_TRANS,
  SCREEN_MODE_STUTTER,
  SCREEN_MODE_SLIDE,
  SCREEN_MODE_RAND,

  SCREEN_MODE_INPUT_DEBUG,

  SCREEN_MODE_SIZE
} ScreenMode;

void screen_setup();
void screen_set_mode(ScreenMode screen_mode);
void screen_set_default(ScreenMode screen_mode);
void screen_back_to_default();
void screen_draw(uint8_t* buffer);
void screen_set_dirty();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_SCREEN_H__ */

