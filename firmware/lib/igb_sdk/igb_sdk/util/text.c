#include <igb_sdk/util/text.h>

static const char oct_chars[16] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static const char dec_chars[10] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

static const char twlv_chars[12] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B'
};

uint8_t text_0x_from_uint8(char* result_text, uint8_t value) {
  result_text[0] = oct_chars[value >> 4];
  result_text[1] = oct_chars[value & 0x0F];
  result_text[2] = 0; // null terminate
  return 2;
}

uint8_t text_0x_from_uint16(char* result_text, uint16_t value) {
  result_text[0] = oct_chars[(value >> 12) & 0x0F];
  result_text[1] = oct_chars[(value >> 8) & 0x0F];
  result_text[2] = oct_chars[(value >> 4) & 0x0F];
  result_text[3] = oct_chars[value & 0x0F];
  result_text[4] = 0; // null terminate
  return 4;
}

uint8_t text_0x_from_uint32(char* result_text, uint32_t value) {
  result_text[0] = oct_chars[(value >> 28) & 0x0F];
  result_text[1] = oct_chars[(value >> 24) & 0x0F];
  result_text[2] = oct_chars[(value >> 20) & 0x0F];
  result_text[3] = oct_chars[(value >> 16) & 0x0F];
  result_text[4] = oct_chars[(value >> 12) & 0x0F];
  result_text[5] = oct_chars[(value >> 8) & 0x0F];
  result_text[6] = oct_chars[(value >> 4) & 0x0F];
  result_text[7] = oct_chars[value & 0x0F];
  result_text[8] = 0; // null terminate
  return 8;
}

uint8_t text_from_uint8(char* result_text, uint8_t value) {
  result_text[0] = oct_chars[value / 100];
  result_text[1] = oct_chars[(value / 10) % 10];
  result_text[2] = oct_chars[value % 10];
  result_text[3] = 0; // null terminate
  return 3;
}

uint8_t text_from_uint16(char* result_text, uint16_t value) {
  result_text[0] = oct_chars[value / 10000];
  result_text[1] = oct_chars[(value / 1000) % 10];
  result_text[2] = oct_chars[(value / 100) % 10];
  result_text[3] = oct_chars[(value / 10) % 10];
  result_text[4] = oct_chars[value % 10];
  result_text[5] = 0; // null terminate
  return 5;
}

uint8_t text_from_uint32(char* result_text, uint32_t value) {
  result_text[0] = oct_chars[value  / 1000000000];
  result_text[1] = oct_chars[(value / 100000000) % 10];
  result_text[2] = oct_chars[(value / 10000000) % 10];
  result_text[3] = oct_chars[(value / 1000000) % 10];
  result_text[4] = oct_chars[(value / 100000) % 10];
  result_text[5] = oct_chars[(value / 10000) % 10];
  result_text[6] = oct_chars[(value / 1000) % 10];
  result_text[7] = oct_chars[(value / 100) % 10];
  result_text[8] = oct_chars[(value / 10) % 10];
  result_text[9] = oct_chars[value % 10];
  result_text[10] = 0; // null terminate
  return 10;
}

uint8_t text_12dec_from_note(char* result_text, uint8_t note) {
  result_text[0] = twlv_chars[(note / 12) % 12];
  result_text[1] = twlv_chars[note % 12];
  result_text[2] = 0; // null terminate
  return 2;
}
