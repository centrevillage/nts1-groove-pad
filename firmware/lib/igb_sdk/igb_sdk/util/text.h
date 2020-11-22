#ifndef IGB_SDK_UTIL_TEXT_H
#define IGB_SDK_UTIL_TEXT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t text_0x_from_uint8(char* result_text, uint8_t value);
uint8_t text_0x_from_uint16(char* result_text, uint16_t value);
uint8_t text_0x_from_uint32(char* result_text, uint32_t value);
uint8_t text_from_uint8(char* result_text, uint8_t value);
uint8_t text_from_uint16(char* result_text, uint16_t value);
uint8_t text_from_uint32(char* result_text, uint32_t value);
uint8_t text_12dec_from_note(char* result_text, uint8_t note);

#ifdef __cplusplus
}
#endif

#endif /* IGB_SDK_UTIL_TEXT_H */
