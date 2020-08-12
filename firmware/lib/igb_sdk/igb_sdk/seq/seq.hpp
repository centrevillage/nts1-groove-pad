#ifndef IGB_SDK_SEQ_SEQ_H
#define IGB_SDK_SEQ_SEQ_H

#include <igb_sdk/base.hpp>
#include <array>
#include <functional>

namespace igb_sdk {

struct SimpleSteps {
  uint16_t active_bits = 0;

  void setTrig(uint8_t step_idx, bool active) {
    if (active) {
      active_bits |= (1<<step_idx);
    } else {
      active_bits &= ~(1<<step_idx);
    }
  }
};

template<typename STEPS_TYPE>
struct SimpleTrack {
  STEPS_TYPE steps;
  uint16_t current_step = 0;
  uint16_t step_length = 16;
  int16_t step_direction = 1;
  std::function<void(uint16_t)> on_step_change;

  void stepNext() {
    int16_t next_step = (int16_t)current_step + step_direction;
    if (next_step < 0) {
      next_step = (step_length - next_step);
      if (next_step < 0) {
        next_step = 0;
      }
    } else {
      next_step = next_step % step_length;
    }
    if (current_step != (uint16_t)next_step) {
      current_step = (uint16_t)next_step;
      if (on_step_change) {
        on_step_change(current_step);
      }
    }
  }
};

// ex:
//  Sequencer<SimpleTrack<SimpleSteps>, 4, AppSeqClock> seq;
//  seq.clock.start();
template <typename TRACK_TYPE, size_t TRACK_SIZE, typename SEQ_CLOCK_TYPE>
struct Sequencer {
  std::array<TRACK_TYPE, TRACK_SIZE> tracks;
  SEQ_CLOCK_TYPE clock;

  void init() {
    bindSimpleOnChange();
  }

  void bindSimpleOnChange() {
    clock.on_change = [this](auto count) {
      for (auto& track : tracks) {
        track.stepNext();
      }
    };
  }
};

}

#endif /* IGB_SDK_SEQ_SEQ_H */
