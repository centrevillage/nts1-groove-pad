#ifndef IGB_SDK_UTIL_SOFT_TIMER_H
#define IGB_SDK_UTIL_SOFT_TIMER_H

#include <igb_sdk/base.hpp>
#include <array>
#include <functional>

namespace igb {
namespace sdk {

template <size_t MAX_TIMER_SIZE>
struct SoftTimer {
  struct TimerState {
    uint32_t interval = 1000; // tick or msec
    std::function<void(void)> callback = nullptr;
    bool oneshot = false;
    bool active = false;
    uint32_t _offset = 0;
    uint32_t _start_msec = 0;
  };

  std::array<TimerState, MAX_TIMER_SIZE> states;

  void inactivate(size_t timer_idx) {
    if (timer_idx < MAX_TIMER_SIZE) {
      states[timer_idx].active = false;
    }
  }

  void activate(size_t timer_idx) {
    if (timer_idx < MAX_TIMER_SIZE) {
      states[timer_idx].active = true;
    }
  }

  void changeInterval(size_t timer_idx, uint32_t interval) {
    if (timer_idx < MAX_TIMER_SIZE) {
      states[timer_idx].interval = interval;
    }
  }

  size_t intervalCallback(uint32_t interval, uint32_t current_msec_, auto&& callback) {
    size_t timer_idx = getFreeState();
    auto& new_state = states[timer_idx];
    new_state.interval = interval;
    new_state.oneshot = false;
    new_state.active = true;
    new_state.callback = callback;
    new_state._start_msec = current_msec_;
    return timer_idx;
  }

  size_t oneshotCallback(uint32_t interval, uint32_t current_msec_, auto&& callback) {
    size_t timer_idx = getFreeState();
    auto& new_state = states[timer_idx];
    new_state.interval = interval;
    new_state.oneshot = true;
    new_state.active = true;
    new_state.callback = callback;
    new_state._start_msec = current_msec_;
    return timer_idx;
  }

  void process(uint32_t current_msec_) {
    for (auto& s : states) {
      if (s.active) {
        uint32_t current_interval = current_msec_ - s._start_msec;
        if (current_interval >= s.interval) {
          if (s.callback) {
            s.callback();
          }
          if (s.oneshot) {
            s.active = false;
          } else {
            s._start_msec += s.interval;
          }
        }
      }
    }
  }

  // 溢れた場合はどれか消す
  size_t getFreeState() {
    for (size_t i = 0; i < MAX_TIMER_SIZE; ++i) {
      auto& s = states[i];
      if (!s.active) {
        s.active = false;
        s.callback = nullptr;
        return i;
      }
    }
    // oneshot のものから優先的に消す
    for (size_t i = 0; i < MAX_TIMER_SIZE; ++i) {
      auto& s = states[i];
      if (s.oneshot) {
        s.active = false;
        s.callback = nullptr;
        return i;
      }
    }
    size_t timer_idx = MAX_TIMER_SIZE - 1; // どれにもマッチしない場合は最後のStateを返す
    auto& s = states[timer_idx];
    s.active = false;
    s.callback = nullptr;
    return timer_idx;
  }
};

}
}

#endif /* IGB_SDK_UTIL_SOFT_TIMER_H */
