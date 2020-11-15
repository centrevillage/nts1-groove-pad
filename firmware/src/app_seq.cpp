#include "app_seq.h"
#include "state.h"
#include "preset.h"
#include "nts1_iface.h"
#include "app_screen.hpp"
#include "app_soft_timer.hpp"

#include <igb_stm32/periph/tim.hpp>
#include <igb_stm32/periph/systick.hpp>

using namespace igb::stm32;

AppSequencer seq;

static uint8_t prev_note = 0;

void AppSequencer::init() {
  clock.on_change = [this](uint16_t count){
    led_set_run(0);
    app_soft_timer.oneshotCallback(50, current_msec(), []{ led_set_run(1); });
    for (auto& track : tracks) { track.receiveClock(count); }
  };

  auto& note_track = tracks[static_cast<uint8_t>(AppTrackType::note)];
  note_track.on_step_change = [this, &note_track](uint16_t step_idx){
    if (note_track.values[step_idx].active) {
      uint8_t note_no = note_track.values[step_idx].r_value;
      uint8_t velocity = note_track.values[step_idx].l_value;
      uint8_t gate_len = note_track.values[step_idx].page;

      nts1_note_off(prev_note);
      nts1_note_on(note_no, velocity);
      if (gate_len != 11) {
        // TODO: gate_len
        app_soft_timer.oneshotCallback(20UL * gate_len, current_msec(), [note_no] {
          nts1_note_off(note_no);
        });
      }
      prev_note = note_no;
    }
  };

  // TODO: load from saved preset
  for (uint8_t i = 0; i < 16; ++i) {
    auto& value = note_track.values[i];
    value.active = true;
    value.page = 7; // default gate length(max 15)
    value.l_value = 100; // default velocity
    value.r_value = 64; // default note no
  }
}

void AppSequencer::receiveClock() {
  clock.receive();
}

void AppSequencer::start() {
  clock.reset();
  auto tim = Tim { TIM_SEQ };
  tim.enable();
  run_state = true;
}

void AppSequencer::stop() {
  nts1_note_off(prev_note);
  auto tim = Tim { TIM_SEQ };
  tim.disable();
  run_state = false;
}

