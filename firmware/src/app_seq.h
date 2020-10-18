#ifndef APP_SEQ_H
#define APP_SEQ_H

#include <igb_sdk/seq/seq.hpp>
#include "app_seq_clock.h"
#include "state.h"
#include "main.h"

using namespace igb::sdk;

struct AppSequencer;
extern AppSequencer seq;

enum class AppTrackType : uint8_t {
  note = 0,
  osc,
  custom,
  filter,
  ampeg,
  modfx,
  delfx,
  revfx,
  arp,
  scale,
  trans,
  stutter,
  lfo
};
constexpr uint8_t APP_TRACK_SIZE = 13;

struct AppSteps : SimpleSteps {
  struct Value {
    int16_t l_value = 0;
    int16_t r_value = 0;
    uint8_t page = 0;
  };

  std::array<Value, 16> values;
};

// アプリケーション依存のシーケンサー
// アプリケーション固有の挙動を実現する

// カスタムパラメータなど複数のパラメータを持つ場合は、
// ページ番号と二つのパラメータをトラック値として保持する。
// (1ステップに設定できる値はそこで設定しばページ番号のパラメータ二つのみ）
struct AppSequencer {
  Sequencer<SimpleTrack<AppSteps>, APP_TRACK_SIZE, AppSeqClock> base_seq;
  bool run_state = 0;
  AppTrackType current_track_type = AppTrackType::note;
  uint16_t selected_steps = 0;

  void init();

  void receiveClock();
  void start();
  void stop();

  void setState(const SeqState& state);
  void getState(SeqState& state);

  inline void changeTrack(AppTrackType track_type) {
    current_track_type = track_type;
    selected_steps = 0;
  }

  inline uint16_t getCurrentStep(AppTrackType track_type) {
    return base_seq.tracks[static_cast<uint8_t>(track_type)].current_step;
  }

  inline uint16_t getStepLength(AppTrackType track_type) {
    return base_seq.tracks[static_cast<uint8_t>(track_type)].step_length;
  }

  inline int16_t getStepDirection(AppTrackType track_type) {
    return base_seq.tracks[static_cast<uint8_t>(track_type)].step_direction;
  }

  inline bool getStepTrig(AppTrackType track_type, uint8_t step_idx) {
    return base_seq.tracks[static_cast<uint8_t>(track_type)].steps.getTrig(step_idx);
  }

  inline void setStepTrig(AppTrackType track_type, uint8_t step_idx, bool active) {
    base_seq.tracks[static_cast<uint8_t>(track_type)].steps.setTrig(step_idx, active);
  }
  inline void toggleStepTrig(AppTrackType track_type, uint8_t step_idx) {
    base_seq.tracks[static_cast<uint8_t>(track_type)].steps.toggle(step_idx);
  }
};


#endif /* APP_SEQ_H */
