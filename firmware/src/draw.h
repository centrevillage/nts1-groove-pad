#ifndef __N1GP_DRAW_H__
#define __N1GP_DRAW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "screen_conf.h"

typedef enum {
  DRAW_PAD_L1 = 0,
  DRAW_PAD_L2,
  DRAW_PAD_L3,
  DRAW_PAD_R1,
  DRAW_PAD_R2,
  DRAW_PAD_R3,
  DRAW_PAD_C1,
  DRAW_PAD_C2
} DrawPadType;

void draw_touch_pad(uint8_t *buffer, DrawPadType type);
void draw_touch_pad_small(uint8_t *buffer, DrawPadType type);
void draw_text_medium(uint8_t *buffer, const char* text, uint8_t length, uint16_t page, uint16_t offset);
void draw_text_small(uint8_t *buffer, const char* text, uint8_t length, uint16_t page, uint16_t offset);
void draw_invert(uint8_t *buffer, uint8_t page_size, uint16_t length, uint16_t page, uint16_t offset);
void draw_fill_bg(uint8_t *buffer);
void draw_fill_fg(uint8_t *buffer);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_DRAW_H__ */
