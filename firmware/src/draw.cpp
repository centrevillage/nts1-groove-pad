#include "draw.h"
#include "font.h"
#include "screen_conf.h"
#include <igb_sdk/font/bitmap/cvfont_5x8.h>
#include <igb_sdk/font/bitmap/cvfont_8x16.h>

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
    const uint16_t* image = cvfont_8_16[c-32];
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
    const uint8_t* image = cvfont_5_8[c-32];
    for (uint8_t x=0; x<5; ++x) {
      uint8_t bits = image[x];
      buffer[((page)*SCREEN_WIDTH)+(pos*5)+offset+x] = bits;
    }
    ++pos;
  }
}

void draw_invert(uint8_t *buffer, uint8_t page_size, uint16_t length, uint16_t page, uint16_t offset) {
  for (uint16_t i=0; i<length; ++i) {
    for (uint16_t page_i=0; page_i<page_size; ++page_i) {
      buffer[((page+page_i)*SCREEN_WIDTH) + offset + i] ^= 0xFF; 
    }
  }
}

void draw_touch_pad_small_l(uint8_t *buffer, const uint8_t* image, uint16_t page) {
  for (uint8_t i=0; i<8; ++i) {
    uint8_t bits = image[i];
    buffer[((page)*SCREEN_WIDTH)+i] |= bits;
  }
}

void draw_touch_pad_small_r(uint8_t *buffer, const uint8_t* image, uint16_t page) {
  const uint16_t offset = SCREEN_WIDTH - 8;
  for (uint8_t i=0; i<8; ++i) {
    uint8_t bits = image[i];
    buffer[((page)*SCREEN_WIDTH)+offset+i] |= bits;
  }
}


void draw_touch_pad_small(uint8_t *buffer, DrawPadType type) {
  switch(type) {
    case DRAW_PAD_L1:
      draw_touch_pad_small_l(buffer, touch_pad_image_small[0], 0);
      break;
    case DRAW_PAD_L2:
      draw_touch_pad_small_l(buffer, touch_pad_image_small[1], 0);
      break;
    case DRAW_PAD_L3:
      draw_touch_pad_small_l(buffer, touch_pad_image_small[2], 0);
      break;
    case DRAW_PAD_R1:
      draw_touch_pad_small_r(buffer, touch_pad_image_small[4], 0);
      break;
    case DRAW_PAD_R2:
      draw_touch_pad_small_r(buffer, touch_pad_image_small[5], 0);
      break;
    case DRAW_PAD_R3:
      draw_touch_pad_small_r(buffer, touch_pad_image_small[6], 0);
      break;
    case DRAW_PAD_C1:
      draw_touch_pad_small_l(buffer, touch_pad_image_small[3], 0);
      break;
    case DRAW_PAD_C2:
      draw_touch_pad_small_r(buffer, touch_pad_image_small[3], 0);
      break;
    default:
      break;
  }
}

void draw_touch_pad_l(uint8_t *buffer, const uint32_t* image, uint16_t page) {
  for (uint8_t i=0; i<32; ++i) {
    uint32_t bits = image[i];
    for (uint8_t j=0; j<4; ++j) {
      buffer[((page+3-j)*SCREEN_WIDTH)+i] |= (uint8_t)(bits >> (8*(3-j)));
    }
  }
}

void draw_touch_pad_r(uint8_t *buffer, const uint32_t* image, uint16_t page) {
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
