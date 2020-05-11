#ifndef __N1GP_DEBUG_H__
#define __N1GP_DEBUG_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void debug_text(const char* text, uint16_t length);
const char* debug_text_get();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_DEBUG_H__ */
