#ifndef IGB_SDK_UTIL_TIMER_H
#define IGB_SDK_UTIL_TIMER_H

#include <array>
#include <functional>

namespace igb {
namespace sdk {

struct HardwareTimerSrc {
};

struct SoftwareTimerSrc {
};

enum class TimeUnit : uint8_t {
  msec = 0,
  usec,
  tick,
};

template <typename TIMER_SRC_TYPE, size_t MAX_TIMER_SIZE>
struct TimerUtil {
  TIMER_SRC_TYPE timer_src;

  struct TimerState {
    uint32_t interval; // tick or msec
    TimeUnit unit;
    bool oneshot = false;
    bool active = false;
    uint32_t _offset = 0;
  };

  std::array<TimerState, MAX_TIMER_SIZE> states;

  void intervalCallback(uint32_t interval, TimerUnit unit, auto&& callback) {
    auto& new_state = getFreeState();
    new_state.inverval = interval;
    new_state.unit = unit;
    new_state.oneshot = false;
    new_state.active = true;
  }

  void oneshotCallback(uint32_t interval, TimerUnit unit, auto&& callback) {
    auto& new_state = getFreeState();
    new_state.inverval = interval;
    new_state.unit = unit;
    new_state.oneshot = true;
    new_state.active = true;
  }

  // 溢れた場合はどれか消す
  auto& getFreeState() {
    for (auto& s : states) {
      if (!s.active) {
        s.active = false;
        s.callback = nullptr;
        return s;
      }
    }
    // oneshot のものから優先的に消す
    for (auto& s : states) {
      if (s.oneshot) {
        s.active = false;
        s.callback = nullptr;
        return s;
      }
    }
    // 最後のstateを消す
    auto& s = states[MAX_TIMER_SIZE - 1];
    s.active = false;
    s.callback = nullptr;
    return s;
  }
};

}
}

#endif /* IGB_SDK_UTIL_TIMER_H */
