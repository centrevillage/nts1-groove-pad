#ifndef __N1GP_TOUCH_H__
#define __N1GP_TOUCH_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TouchEventCallback)(uint8_t touch_idx, uint8_t on);

void touch_setup();
void touch_process();
void touch_event_listen(TouchEventCallback cb);

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_TOUCH_H__ */
