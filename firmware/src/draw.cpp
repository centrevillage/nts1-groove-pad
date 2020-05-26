#include "draw.h"
#include "font.h"
#include "screen_conf.h"

void draw_text_medium(uint8_t *buffer, const char* text, uint8_t length, uint16_t page, uint16_t offset) {
  uint8_t pos = 0;
  for (uint8_t i=0; i<length; ++i) {
    char c = text[i];
    if (c == '\n') {
      page += 2;
      pos = 0;
      continue;
    }
    if (c < 32 || c > 126) {
      return; // null or meta char
    }
    const uint16_t* image = font_medium_image[c-32];
    for (uint8_t x=0; x<8; ++x) {
      uint16_t bits = image[x];
      buffer[((page)*SCREEN_WIDTH)+(pos*8)+offset+x] = (uint8_t)bits;
      buffer[((page+1)*SCREEN_WIDTH)+(pos*8)+offset+x] = (uint8_t)(bits>>8);
    }
    ++pos;
  }
}

void draw_text_small(uint8_t *buffer, const char* text, uint8_t length, uint16_t page, uint16_t offset) {
  uint8_t pos = 0;
  for (uint8_t i=0; i<length; ++i) {
    char c = text[i];
    if (c == '\n') {
      page += 1;
      pos = 0;
      continue;
    }
    if (c < 32 || c > 126) {
      return; // null or meta char
    }
    const uint8_t* image = font_small_image[c-32];
    for (uint8_t x=0; x<8; ++x) {
      uint8_t bits = image[x];
      buffer[((page)*SCREEN_WIDTH)+(pos*5)+offset+x] = bits;
    }
    ++pos;
  }
}

inline void draw_touch_pad_l(uint8_t *buffer, const uint32_t* image, uint16_t page) {
  for (uint8_t i=0; i<32; ++i) {
    uint32_t bits = image[i];
    for (uint8_t j=0; j<4; ++j) {
      buffer[((page+3-j)*SCREEN_WIDTH)+i] |= (uint8_t)(bits >> (8*(3-j)));
    }
  }
}

inline void draw_touch_pad_r(uint8_t *buffer, const uint32_t* image, uint16_t page) {
  const uint16_t offset = SCREEN_WIDTH - 32;
  for (uint16_t i=0; i<32; ++i) {
    uint32_t bits = image[i];
    for (uint16_t j=0; j<4; ++j) {
      buffer[((page+3-j)*SCREEN_WIDTH)+offset+i] |= (uint8_t)(bits >> (8*(3-j)));
    }
  }
}

void draw_touch_pad(uint8_t *buffer, DrawPadType type) {
  uint16_t page = ((SCREEN_HEIGHT/2)-16) / 8;
  switch(type) {
    case DRAW_PAD_L1:
      draw_touch_pad_l(buffer, touch_pad_image[0], page);
      break;
    case DRAW_PAD_L2:
      draw_touch_pad_l(buffer, touch_pad_image[1], page);
      break;
    case DRAW_PAD_L3:
      draw_touch_pad_l(buffer, touch_pad_image[2], page);
      break;
    case DRAW_PAD_R1:
      draw_touch_pad_r(buffer, touch_pad_image[4], page);
      break;
    case DRAW_PAD_R2:
      draw_touch_pad_r(buffer, touch_pad_image[5], page);
      break;
    case DRAW_PAD_R3:
      draw_touch_pad_r(buffer, touch_pad_image[6], page);
      break;
    case DRAW_PAD_C1:
      draw_touch_pad_l(buffer, touch_pad_image[3], page);
      break;
    case DRAW_PAD_C2:
      draw_touch_pad_r(buffer, touch_pad_image[3], page);
      break;
    default:
      break;
  }
}

void draw_fill_bg(uint8_t *buffer) {
  uint16_t size = SCREEN_WIDTH * SCREEN_HEIGHT / 8;
  for (size_t i = 0; i < size; ++i) {
    buffer[i] = 0;
  }
}

void draw_fill_fg(uint8_t *buffer) {
  uint16_t size = SCREEN_WIDTH * SCREEN_HEIGHT / 8;
  for (size_t i = 0; i < size; ++i) {
    buffer[i] = 0xFF;
  }
}
