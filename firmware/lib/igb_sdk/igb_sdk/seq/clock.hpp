#ifndef IGB_SDK_SEQ_CLOCK_H
#define IGB_SDK_SEQ_CLOCK_H

#include <igb_sdk/base.hpp>
#include <array>
#include <functional>

namespace igb {
namespace sdk {

// 同期用のカウンター
//
// 同期のトリガーとなる信号は、Trigger In, MIDI Clock等、それぞれ異なる速さ(Step per Clock)を持っている。
// それらを統一して扱うために、同じタイムスケールを持つ様にこのカウンターで調節する。
//
// 例えば、Trigger Inが一回来る時は1ステップ進み、MIDI Clockが6回来たときに1ステップ進むとすれば、
// Trigger Inがくるたびに6カウント足し、MIDI Clockがくるたびに1カウント足せばタイムスケールが揃うことになる。
//
// ex:
//  auto trig_counter = SeqClockCounter(6, 256);
//  auto midi_counter = SeqClockCounter(1, 256);
struct ClockCounter {
  const uint16_t step = 1;
  const uint16_t max_count = 256;
  uint16_t count;

  uint16_t nextCount() const {
    return (count + step) % max_count;
  }

  uint16_t get() const {
    return count;
  }

  void set(uint16_t count_) {
    count = count_;
  }

  void reset() {
    set(0);
  }
};

// hardware timer由来のTriggerを扱う場合、reset時にhardware timerのカウンタもリセットしたい。
// その場合は、このカウンタでresetのコールバックにてhardware timerのカウンタをリセットする。
struct ClockCounterWithResetCallback {
  ClockCounter counter;
  std::function<void()> reset_callback;

  uint16_t nextCount() const {
    return counter.nextCount();
  }

  uint16_t get() const {
    return counter.get();
  }

  void set(uint16_t count_) {
    counter.set(count_);
  }

  void reset() {
    set(0);
    if (reset_callback) {
      reset_callback();
    }
  }
};

// シングルクロックカウンタ
template<typename COUNTER_TYPE>
struct SeqClock {
  COUNTER_TYPE counter;
  std::function<void(uint16_t)> on_change;
  
  void reset() {
    counter.reset();
  }

  uint16_t getClockCount() const {
    return counter.get();
  }

  void receive() {
    counter.set(counter.nextCount());
    if (on_change) {
      on_change(getClockCount());
    }
  }
};

// 各同期用のカウンタに primary と secondary を指定できる。
// primary が更新されたとき、secondary は primary のカウンタ値にセットされる。
// getCount では primary と secondary のカウンタのうち、大きな方が返る。
// ただし、secondary カウンタは primary.count + primary.step の値を超えることはできない。
//
// 例えば、primary に 外部トリガに対応するカウンタ、
// secondary に内部タイマに対応するカウンタを指定した場合、
// 外部トリガによるクロック更新の間にタイマによるカウント更新を行うことで、
// 外部トリガより細かいクロックでシーケンサーを動作することが可能になる。
template<typename PRIMARY_COUNTER_TYPE, typename SECONDARY_COUNTER_TYPE>
struct Seq2Clock {
  PRIMARY_COUNTER_TYPE primary_counter;
  SECONDARY_COUNTER_TYPE secondary_counter;
  std::function<void(uint16_t)> on_change;

  void reset() {
    primary_counter.reset();
    secondary_counter.reset();
  }

  void receivePrimary() {
    primary_counter.set(primary_counter.nextCount());
    secondary_counter.set(primary_counter.get());
    if (on_change) {
      on_change(getClockCount());
    }
  }

  void receiveSecondary() {
    if (secondary_counter.nextCount() < primary_counter.nextCount()) {
      secondary_counter.set(secondary_counter.nextCount());
      if (on_change) {
        on_change(getClockCount());
      }
    } else if (secondary_counter.nextCount() > primary_counter.nextCount()) {
      // max count オーバーによって primary がwrap
      secondary_counter.set(primary_counter.get());
    }
  }

  uint16_t getClockCount() const {
    uint16_t primary_count = primary_counter.get();
    uint16_t secondary_count = secondary_counter.get();
    return primary_count > secondary_count ? primary_count : secondary_count;
  }
};

}
}

#endif /* IGB_SDK_SEQ_CLOCK_H */
