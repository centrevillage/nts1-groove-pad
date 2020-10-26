#ifndef IGB_SDK_SEQ_SEQ_H
#define IGB_SDK_SEQ_SEQ_H

#include <igb_sdk/base.hpp>
#include <array>
#include <functional>
#include <bitset>

namespace igb {
namespace sdk {

// 空のトラック実装.
// 独自トラッククラスではここで定義されたメソッドを必ず実装する必要がある
struct NullTrack {
  void receiveClock(auto current_count) {
    // トラックがクロックを受けた時の処理
  }
  void start() {
    // トラックがスタートイベントを受けた時の処理
  }
  void stop() {
    // トラックがストップイベントを受けた時の処理
  }
  void jump(auto&& step) {
    // トラックがジャンプイベントを受けた時の処理
  }
  void reset() {
    // トラックがリセットイベントを受けた時の処理
  }
  void processEvent(auto&& eventId, auto&& value) {
    // トラックがアプリ定義のイベントを受けた時の処理
  }
  // serialize api
  uint32_t serializedBufferSize() {
    return 0;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
};

template<size_t STEP_SIZE = 16>
struct TriggerTrack {
  uint16_t current_step = 0;
  std::bitset<STEP_SIZE> active_bits;
  std::function<void(uint16_t, bool)> on_step_change;
  bool is_resetted = false;

  static const size_t STEP_BYTE_SIZE = (STEP_SIZE + 7) / 8;

  inline void setTrig(uint8_t step_idx, bool active) {
    if (active) {
      active_bits.set(step_idx);
    } else {
      active_bits.reset(step_idx);
    }
  };

  inline bool getTrig(uint8_t step_idx) {
    return active_bits.test(step_idx);
  }

  void toggle(uint8_t step_idx) {
    setTrig(step_idx, !getTrig(step_idx));
  }

  void receiveClock(auto current_count) {
    if (is_resetted) {
      current_step = 0;
      is_resetted = false;
    } else {
      current_step = (current_step + 1) % STEP_SIZE;
    }
    if (on_step_change) {
      on_step_change(current_step, active_bits.test(current_step));
    }
  }

  void reset() {
    is_resetted = true;
  }
  void start() {
    // トラックがスタートイベントを受けた時の処理
  }
  void stop() {
    // トラックがストップイベントを受けた時の処理
  }
  void jump(auto&& step) {
    // トラックがジャンプイベントを受けた時の処理
  }
  void processEvent(auto&& eventId, auto&& value) {
    // トラックがイベントを受けた時の処理
  }

  // serialize api
  uint32_t serializedBufferSize() {
    return STEP_BYTE_SIZE;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      for (int i = STEP_BYTE_SIZE-1; i >= 0; --i) {
        *out_buffer = (uint8_t)(((active_bits >> (i*8)) & std::bitset<STEP_SIZE>(0xFF)).to_ulong());
        ++out_buffer;
      }
    }
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
    if (size >= serializedBufferSize()) {
      for (int i = STEP_BYTE_SIZE-1; i >= 0; --i) {
        active_bits = ~(std::bitset<STEP_SIZE>(0xFF) << (i*8)) | (std::bitset<STEP_SIZE>(*in_buffer) << (i*8));
        ++in_buffer;
      }
    }
  }
};

template<typename VALUE_TYPE, size_t STEP_SIZE = 16>
struct ValueTrack {
  uint16_t current_step = 0;
  std::array<VALUE_TYPE, STEP_SIZE> values;
  std::function<void(uint16_t, VALUE_TYPE)> on_step_change;
  bool is_resetted = false;

  void receiveClock(auto current_count) {
    if (is_resetted) {
      current_step = 0;
      is_resetted = false;
    } else {
      current_step = (current_step + 1) % STEP_SIZE;
    }
    if (on_step_change) {
      on_step_change(current_step, values[current_step]);
    }
  }

  void reset() {
    is_resetted = true;
  }
  void start() {
    // トラックがスタートイベントを受けた時の処理
  }
  void stop() {
    // トラックがストップイベントを受けた時の処理
  }
  void jump(auto&& step) {
    // トラックがジャンプイベントを受けた時の処理
  }
  void processEvent(auto&& eventId, auto&& value) {
    // トラックがイベントを受けた時の処理
  }
  // serialize api
  uint32_t serializedBufferSize() {
    return 0;
  }
  void serialize(uint8_t* out_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
  void deserialize(uint8_t* in_buffer, size_t size /* must be equal to serializedBufferSize */ ) {
  }
};

//#include "seq/algorithm.hpp"
//
//// ユーザー定義のシーケンサーアルゴリズムを使うトラック
//struct AlgorithmTrack {
//  void receiveClock(auto current_count) {
//    // トラックがクロックを受けた時の処理
//  }
//  void start() {
//    // トラックがスタートイベントを受けた時の処理
//  }
//  void stop() {
//    // トラックがストップイベントを受けた時の処理
//  }
//  void jump(auto&& step) {
//    // トラックがジャンプイベントを受けた時の処理
//  }
//  void reset() {
//    // トラックがリセットイベントを受けた時の処理
//  }
//  void processEvent(auto&& eventId, auto&& value) {
//    // トラックがアプリ定義のイベントを受けた時の処理
//  }
//};

// シーケンサーの実装テンプレート。
// アプリ側では利用するもしないも自由。
// （ある程度複雑になってくると、おそらくアプリ独自で定義したほうが良い）
//
// ex:
//  Sequencer<TriggerTrack, 4, AppSeqClock> seq;
//  seq.clock.start();
template <typename TRACK_TYPE, size_t TRACK_SIZE, typename SEQ_CLOCK_TYPE>
struct SyncSequencer {
  std::array<TRACK_TYPE, TRACK_SIZE> tracks;
  SEQ_CLOCK_TYPE clock;

  SyncSequencer() {
    bindClock();
  }

  void bindClock() {
    clock.on_change = [this](auto count) {
      for (auto& track : tracks) {
        track.receiveClock(count);
      }
    };
  }
  void resetAllTracks() {
    for (auto& track : tracks) {
      track.reset();
    }
  }
  void startAllTracks() {
    for (auto& track : tracks) {
      track.start();
    }
  }
  void stopAllTracks() {
    for (auto& track : tracks) {
      track.stop();
    }
  }
  void jumpAllTracks(auto&& step) {
    for (auto& track : tracks) {
      track.jump(step);
    }
  }
  void processEventAllTracks(auto&& eventId, auto&& value) {
    for (auto& track : tracks) {
      track.processEvent(eventId, value);
    }
  }
};

}
}

#endif /* IGB_SDK_SEQ_SEQ_H */
