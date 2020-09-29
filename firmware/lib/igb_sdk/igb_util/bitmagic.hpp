#ifndef IGB_UTIL_BITMAGIC_H
#define IGB_UTIL_BITMAGIC_H

#include <igb_util/macro.hpp>

namespace igb {

static IGB_FAST_INLINE uint8_t bit_count_u8(uint8_t bits) {
  bits = bits - ((bits >> 1) & 0b01010101);
  bits = (bits & 0b00110011) + ((bits >> 2) & 0b00110011);
  bits = (bits & 0b00001111) + (bits >> 4);
  return bits;
}

static IGB_FAST_INLINE uint16_t bit_count_u16(uint16_t bits) {
  bits = bits - ((bits >> 1) & 0b0101010101010101);
  bits = (bits & 0b0011001100110011) + ((bits >> 2) & 0b0011001100110011);
  bits = (bits + (bits >> 4)) & 0b0000111100001111;
  bits = bits + (bits >> 8);
  return bits & 0x1F;
}

static IGB_FAST_INLINE uint32_t bit_count_u32(uint32_t bits) {
  bits = bits - ((bits >> 1) & 0x55555555);
  bits = (bits & 0x33333333) + ((bits >> 2) & 0x33333333);
  bits = (bits + (bits >> 4)) & 0x0F0F0F0F;
  bits = bits + (bits >> 8);
  bits = bits + (bits >> 16);
  return bits & 0x3F;
}

inline uint8_t bit_index_u8(uint8_t bits) {
  return bit_count_u8((bits & (-bits)) - 1);
}

inline uint16_t bit_index_u16(uint16_t bits) {
  return bit_count_u16((bits & (-bits)) - 1);
}

inline uint16_t bit_left_rotate_u16(uint16_t bits, uint8_t rotate /* 0 to 15 */) {
  return (bits << rotate) | (bits >> (16 - rotate));
}

inline uint16_t bit_left_rotate_with_length_u16(uint16_t bits, uint8_t rotate /* 0 to length */, uint8_t length /* 1.. 16 */) {
  if (length == 16) {
    return bit_left_rotate_u16(bits, rotate);
  }
  return ((bits << rotate) | (bits >> (length - rotate))) & ((1<<(length)) - 1);
}

inline uint16_t bit_right_rotate_u16(uint16_t bits, uint8_t rotate /* 0 to 15 */) {
  return (bits >> rotate) | (bits << (16 - rotate));
}

static IGB_FAST_INLINE auto extract_most_right1(auto bits) -> decltype(bits) {
  return bits & -bits;
}

static IGB_FAST_INLINE auto reset_most_right1(auto bits) -> decltype(bits) {
  return bits & (bits - 1);
}

}

#endif /* IGB_UTIL_BITMAGIC_H */
