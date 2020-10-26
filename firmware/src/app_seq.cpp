#include "app_seq.h"
#include "state.h"
#include "preset.h"
#include "nts1_iface.h"
#include "app_screen.hpp"

#include <igb_stm32/periph/tim.hpp>

using namespace igb::stm32;

AppSequencer seq;

static uint8_t prev_note = 0;

void AppSequencer::init() {
  auto& note_track = tracks[static_cast<uint8_t>(AppTrackType::note)];
  note_track.on_step_change = [this, note_track](uint16_t step_idx){
    if (note_track.values[step_idx].active) {
      uint8_t note_no = note_track.values[step_idx].r_value;
      uint8_t velocity = note_track.values[step_idx].l_value;
      nts1_note_off(prev_note);
      nts1_note_on(note_no, velocity);
      // TODO: タイマーでlength に依存した時間ののちnote off
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

