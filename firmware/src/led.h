#ifndef __N1GP_LED_H__
#define __N1GP_LED_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void led_setup();
void led_process();
void led_set(uint8_t index, uint8_t on);
void led_set_run(uint8_t on);
void led_set_mode(uint8_t on);
void led_clear();

#ifdef __cplusplus
}
#endif

#endif /* __N1GP_LED_H__ */
