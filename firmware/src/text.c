#include "text.h"

static const char oct_chars[16] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void text_0x_from_uint8(char* result_text, uint8_t value) {
  result_text[0] = oct_chars[value >> 4];
  result_text[1] = oct_chars[value & 0x0F];
  result_text[2] = 0; // null terminate
}

// 呼び出すとフリーズすることがある？
void text_0x_from_uint16(char* result_text, uint16_t value) {
  result_text[0] = oct_chars[(value >> 12) & 0x0F];
  result_text[1] = oct_chars[(value >> 8) & 0x0F];
  result_text[2] = oct_chars[(value >> 4) & 0x0F];
  result_text[3] = oct_chars[value & 0x0F];
  result_text[4] = 0; // null terminate
}

void text_0x_from_uint32(char* result_text, uint32_t value) {
  result_text[0] = oct_chars[(value >> 28) & 0x0F];
  result_text[1] = oct_chars[(value >> 24) & 0x0F];
  result_text[2] = oct_chars[(value >> 20) & 0x0F];
  result_text[3] = oct_chars[(value >> 16) & 0x0F];
  result_text[4] = oct_chars[(value >> 12) & 0x0F];
  result_text[5] = oct_chars[(value >> 8) & 0x0F];
  result_text[6] = oct_chars[(value >> 4) & 0x0F];
  result_text[7] = oct_chars[value & 0x0F];
  result_text[8] = 0; // null terminate
}
