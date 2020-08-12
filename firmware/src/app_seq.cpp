#include "app_seq.h"
#include "timer.h"
#include "state.h"
#include "preset.h"
#include "nts1_iface.h"

AppSequencer seq;

static uint8_t prev_note = 0;

void AppSequencer::init() {
  base_seq.init();
  base_seq.tracks[0].on_step_change = [this](uint16_t step_idx){
    if (seq_state.active_steps & ((uint16_t)1<<step_idx)) {
      const auto& step = seq_state.steps[step_idx];
      nts1_note_off(prev_note);
      nts1_note_on(step.note, step.velocity);
      // TODO: タイマーでlength に依存した時間ののちnote off
      prev_note = step.note;
    }
  };
}

void AppSequencer::receiveClock() {
  base_seq.clock.receive();
}

void AppSequencer::start() {
  base_seq.clock.reset();
  timer_start(TIM_SEQ_ID);
  run_state = true;
}

void AppSequencer::stop() {
  nts1_note_off(prev_note);
  timer_stop(TIM_SEQ_ID);
  run_state = false;
}

void AppSequencer::setState(const SeqState& state) {
  for (auto& track : base_seq.tracks) {
    track.step_length = state.length;
    // TODO: state.direction の意味をちゃんと考えてないので・・・
    //track.step_direction = state.direction;
  }
}

void AppSequencer::getState(SeqState& state) {
  const auto track = base_seq.tracks[0];
  state.length = track.step_length;
}

