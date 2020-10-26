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

struct AppTrackValue {
  bool active = true;
  int16_t l_value = 0;
  int16_t r_value = 0;
  uint8_t page = 0;

  // serialize api
  static const uint32_t serializedBufferSize() {
    return 48;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      *(out_buffer++) = active ? 1 : 0;
      *(out_buffer++) = (uint8_t)(l_value >> 8);
      *(out_buffer++) = (uint8_t)l_value;
      *(out_buffer++) = (uint8_t)(r_value >> 8);
      *(out_buffer++) = (uint8_t)r_value;
      *(out_buffer++) = page;
    }
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      active = *(in_buffer++);
      uint16_t tmp = (*(in_buffer++)) << 8;
      tmp |= (*(in_buffer++));
      l_value = tmp;
      tmp = (*(in_buffer++)) << 8;
      tmp |= (*(in_buffer++));
      r_value = tmp;
      page = *in_buffer++;
    }
  }
};

template<size_t STEP_SIZE>
struct AppTrack {
  uint16_t current_step = 0;
  uint16_t _next_step = 0;
  bool _is_set_next_step = false;
  std::array<AppTrackValue, STEP_SIZE> values;
  std::function<void(uint16_t)> on_step_change;

  uint16_t _step_length = STEP_SIZE;
  void setStepLength(uint16_t length) {
    if (0 <= length && length < STEP_SIZE) {
      _step_length = length;
    }
  }
  uint16_t getStepLength() { return _step_length; }

  void toggleActive(uint8_t step_idx) {
    if (step_idx < STEP_SIZE) {
      values[step_idx].active = !values[step_idx].active;
    }
  }

  void receiveClock(auto current_count) {
    if (_is_set_next_step) {
      current_step = _next_step;
      _is_set_next_step = false;
    } else {
      current_step = (current_step + 1) % _step_length;
    }
    if (on_step_change) {
      on_step_change(current_step);
    }
  }

  void start() {
    // トラックがスタートイベントを受けた時の処理
  }
  void stop() {
    // トラックがストップイベントを受けた時の処理
  }
  void jump(auto&& step) {
    if (step < _step_length) {
      _next_step = step;
      _is_set_next_step = true;
    }
    // トラックがジャンプイベントを受けた時の処理
  }
  void reset() {
    // トラックがリセットイベントを受けた時の処理
    _next_step = 0;
    _is_set_next_step = true;
  }
  void processEvent(auto&& eventId, auto&& value) {
    // トラックがアプリ定義のイベントを受けた時の処理
  }
  // serialize api
  static const uint32_t serializedBufferSize() {
    return AppTrackValue::serializedBufferSize() * STEP_SIZE;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      for (uint8_t i = 0; i < STEP_SIZE; ++i) {
        values[i].serialize(out_buffer + (i*AppTrackValue::serializedBufferSize()), AppTrackValue::serializedBufferSize());
      }
    }
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      for (uint8_t i = 0; i < STEP_SIZE; ++i) {
        values[i].deserialize(in_buffer + (i*AppTrackValue::serializedBufferSize()), AppTrackValue::serializedBufferSize());
      }
    }
  }
};

// アプリケーション依存のシーケンサー
// アプリケーション固有の挙動を実現する

// カスタムパラメータなど複数のパラメータを持つ場合は、
// ページ番号と二つのパラメータをトラック値として保持する。
// (1ステップに設定できる値はそこで設定しばページ番号のパラメータ二つのみ）
struct AppSequencer : SyncSequencer<AppTrack<16>, APP_TRACK_SIZE, AppSeqClock> {
  bool run_state = 0;
  AppTrackType current_track_type = AppTrackType::note;
  uint16_t selected_steps = 0;

  void init();

  void receiveClock();
  void start();
  void stop();

  auto& getTrack(AppTrackType track_type) {
    return tracks[static_cast<size_t>(track_type)];
  }

  auto& currentTrack() {
    return tracks[static_cast<size_t>(current_track_type)];
  }

  inline void changeTrack(AppTrackType track_type) {
    current_track_type = track_type;
    selected_steps = 0;
  }
};


#endif /* APP_SEQ_H */
