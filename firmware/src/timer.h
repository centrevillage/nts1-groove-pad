#ifndef __STM_TIMER_H__
#define __STM_TIMER_H__

#include "main.h"
#include "common.h"

#include "timer_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// functions
void timer_simple_setup(uint8_t timer_idx, uint16_t prescale, uint32_t period, uint16_t priority);
void timer_start(uint8_t timer_idx);
void timer_stop(uint8_t timer_idx);

#define TIMER_EVENT_HANDLER(timer_idx) _TIMER_EVENT_HANDLER(timer_idx)
#define _TIMER_EVENT_HANDLER(timer_idx) void timer_##timer_idx##_event_handler()

#ifdef __cplusplus
}
#endif

#endif /* __STM_TIMER_H__ */
