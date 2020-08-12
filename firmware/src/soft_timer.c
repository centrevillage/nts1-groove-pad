#include "soft_timer.h"
#include "systick_timer.h"

volatile TimerInfo timer_infos[MAX_TIMER_SIZE];
static volatile uint32_t prev_msec;

void soft_timer_setup() {
  prev_msec = current_msec();
  for (uint8_t i = 0; i < MAX_TIMER_SIZE; ++i) {
    timer_infos[i].active = 0;
  }
}

void soft_timer_start(uint8_t timer_idx, uint32_t interval, TimerCallback callback) {
  timer_infos[timer_idx].callback = callback;
  timer_infos[timer_idx].interval = interval;
  timer_infos[timer_idx].msec = current_msec();
  timer_infos[timer_idx].interval_adjust_msec = 0;
  timer_infos[timer_idx].active = 1;
}

void soft_timer_stop(uint8_t timer_idx) {
  timer_infos[timer_idx].active = 0;
}

void soft_timer_process() {
  if (prev_msec == current_msec()) {
    return;
  }
  volatile uint32_t msec = current_msec();
  for (uint8_t i = 0; i < MAX_TIMER_SIZE; ++i) {
    if (timer_infos[i].active) {
      uint32_t diff = (uint32_t)(msec + timer_infos[i].interval_adjust_msec - timer_infos[i].msec);
      if (diff > timer_infos[i].interval) {
        timer_infos[i].msec = msec;
        timer_infos[i].interval_adjust_msec = diff - timer_infos[i].interval;
        timer_infos[i].callback();
      }
    }
  }
  prev_msec = msec;
}

