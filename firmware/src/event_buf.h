#ifndef __N1GP_EVENT_BUF_H__
#define __N1GP_EVENT_BUF_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t valid;
  uint8_t data;
} EventDataU8;

typedef struct {
  uint8_t buf[256];
  uint8_t read_idx;
  uint8_t end_idx;
} EventStateU8;

void event_buf_add_u8(EventStateU8* state, uint8_t event);
EventDataU8 event_buf_get_u8(EventStateU8* state);
uint8_t event_buf_is_empty_u8(EventStateU8* state);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_EVENT_BUF_H__ */
