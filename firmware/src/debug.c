#include "debug.h"
#include <igb_sdk/util/text.h>

__IO char debug_text_buffer[256];

void debug_text(const char* text, uint16_t length) {
  uint16_t i=0;
  for (; i<length && i<255; ++i) {
    if (text[i] == 0) {
      break;
    }
    debug_text_buffer[i] = text[i];
  }
  debug_text_buffer[i] = 0;
}

const char* debug_text_get() {
  return (const char*)debug_text_buffer;
}
