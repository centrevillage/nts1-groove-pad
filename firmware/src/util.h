#ifndef __STM_UTIL_H
#define __STM_UTIL_H

#include "main.h"

FORCE_INLINE float clipping_f(float v, float min_value, float max_value) {
  if (v < min_value) {
    return min_value;
  }
  if (v > max_value) {
    return max_value;
  }
  return v;
}

FORCE_INLINE int16_t clipping_int16(int16_t v, int16_t min_value, int16_t max_value) {
  if (v < min_value) {
    return min_value;
  }
  if (v > max_value) {
    return max_value;
  }
  return v;
}

FORCE_INLINE uint8_t bit_count_in_8bit(uint8_t bits) {
  bits = bits - ((bits >> 1) & 0b01010101);
  bits = (bits & 0b00110011) + ((bits >> 2) & 0b00110011);
  bits = (bits & 0b00001111) + (bits >> 4);
  return bits;
}

FORCE_INLINE uint16_t bit_count_in_16bit(uint16_t bits) {
  bits = bits - ((bits >> 1) & 0b0101010101010101);
  bits = (bits & 0b0011001100110011) + ((bits >> 2) & 0b0011001100110011);
  bits = (bits + (bits >> 4)) & 0b0000111100001111;
  bits = bits + (bits >> 8);
  return bits & 0x1F;
}

FORCE_INLINE uint32_t bit_count_in_32bit(uint32_t bits) {
  bits = bits - ((bits >> 1) & 0x55555555);
  bits = (bits & 0x33333333) + ((bits >> 2) & 0x33333333);
  bits = (bits + (bits >> 4)) & 0x0F0F0F0F;
  bits = bits + (bits >> 8);
  bits = bits + (bits >> 16);
  return bits & 0x3F;
}

//#define extract_most_right1(bits) ((bits) & -(bits))
//#define reset_most_right1(bits) ((bits) & ((bits)-1))
//#define bit_is_set(n,bit) (n & (1<<(bit)))

#endif /* __STM_UTIL_H */
