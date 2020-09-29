#ifndef IGB_SDK_UI_TOUCH_H
#define IGB_SDK_UI_TOUCH_H

#include <igb_sdk/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_util/macro.hpp>
#include <array>
#include <optional>
#include <algorithm>

namespace igb {
namespace sdk {

const int8_t TOUCH_NO_VALUE = -128;
const int8_t TOUCH_HOLD_VALUE = -127;

template<
  typename TOUCH_CH_TYPE
>
struct TouchSingleSwitch {
  TOUCH_CH_TYPE channel;

  void IGB_FAST_INLINE process() const noexcept {
  }

  bool IGB_FAST_INLINE isOn()  const noexcept {
    return channel.read();
  }
};

const int8_t TOUCH_STATE_BITS_TO_IDX[16] = {
  // 0b0000
  TOUCH_NO_VALUE,
  // 0b0001
  0,
  // 0b0010
  2,
  // 0b0011
  1,
  // 0b0100
  4,
  // 0b0101
  5,
  // 0b0110
  3,
  // 0b0111
  TOUCH_HOLD_VALUE,
  // 0b1000
  TOUCH_NO_VALUE,
  // 0b1001
  0,
  // 0b1010
  2,
  // 0b1011
  1,
  // 0b1100
  4,
  // 0b1101
  5,
  // 0b1110
  3,
  // 0b1111
  TOUCH_HOLD_VALUE,
};

template<
  typename TOUCH_CH_TYPE
>
struct TouchRot3Switch {
  std::array<TOUCH_CH_TYPE, 3> channels;

  IGB_FAST_INLINE void process() const noexcept {
  }

  IGB_FAST_INLINE std::optional<uint8_t> value() const noexcept {
    uint8_t bits = (channels[0].read() ? 1 : 0) | ((channels[1].read() ? 1 : 0) << 1) | ((channels[2].read() ? 1 : 0) << 2);
    uint8_t v = TOUCH_STATE_BITS_TO_IDX[bits];
    return (v != TOUCH_NO_VALUE && v != TOUCH_HOLD_VALUE) ? std::make_optional(v) : std::nullopt;
  }
};

template<
  typename TOUCH_CH_TYPE,
  typename VALUE_TYPE = int16_t
>
struct TouchRot3Dial {
  std::array<TOUCH_CH_TYPE, 3> channels;
  VALUE_TYPE steps = 1;
  std::optional<VALUE_TYPE> _value;
  uint8_t _current_touch_bits = 0;
  uint8_t _prev_touch_bits = 0;

  IGB_FAST_INLINE void process() const noexcept {
    _prev_touch_bits = _current_touch_bits;
    _current_touch_bits = (channels[0].read() ? 1 : 0) | ((channels[1].read() ? 1 : 0) << 1) | ((channels[2].read() ? 1 : 0) << 2);
    if (!(_current_touch_bits & 0b0111)) {
      // released
      _value = std::nullopt;
      return;
    }
    int8_t rot_value_prev = TOUCH_STATE_BITS_TO_IDX[_prev_touch_bits & 0x0F];
    int8_t rot_value_current = TOUCH_STATE_BITS_TO_IDX[_current_touch_bits & 0x0F];
    if (rot_value_prev != rot_value_current && rot_value_current >= 0 && rot_value_prev >= 0) {
      if (rot_value_current == (rot_value_prev + 1) % 6) {
        // move high position
        _value = steps;
        return;
      } else if (rot_value_current == (rot_value_prev + 5) % 6) {
        // move low position
        _value = -steps;
        return;
      }
    }
    _value = std::nullopt;
  }

  IGB_FAST_INLINE std::optional<VALUE_TYPE> value() const noexcept {
    return _value;
  }
};

template<
  typename TOUCH_CH_TYPE,
  typename VALUE_TYPE = int16_t
>
struct TouchRot3DialWithCenter {
  std::array<TOUCH_CH_TYPE, 3> channels;
  TOUCH_CH_TYPE center_channel;
  VALUE_TYPE steps = 4;
  VALUE_TYPE steps_on_center = 1;
  std::optional<VALUE_TYPE> _value;
  uint8_t _current_touch_bits = 0;
  uint8_t _prev_touch_bits = 0;

  IGB_FAST_INLINE void process() noexcept {
    _prev_touch_bits = _current_touch_bits;
    _current_touch_bits = !!(channels[0].read()) | (!!(channels[1].read()) << 1) | (!!(channels[2].read()) << 2) | (!!(center_channel.read()) << 3);
    if (!(_current_touch_bits & 0b0111)) {
      // released
      _value = std::nullopt;
      return;
    }
    VALUE_TYPE rot_value_prev = TOUCH_STATE_BITS_TO_IDX[_prev_touch_bits & 0x0F];
    VALUE_TYPE rot_value_current = TOUCH_STATE_BITS_TO_IDX[_current_touch_bits & 0x0F];
    if (rot_value_prev != rot_value_current && rot_value_current >= 0 && rot_value_prev >= 0) {
      if (rot_value_current == (rot_value_prev + 1) % 6) {
        // move high position
        if (_current_touch_bits & 0b1000) {
          _value = steps_on_center;
        } else {
          _value = steps;
        }
        return;
      } else if (rot_value_current == (rot_value_prev + 5) % 6) {
        // move low position
        if (_current_touch_bits & 0b1000) {
          _value = -steps_on_center;
        } else {
          _value = -steps;
        }
        return;
      }
    }
    _value = std::nullopt;
  }

  IGB_FAST_INLINE std::optional<VALUE_TYPE> value() const noexcept {
    return _value;
  }
};

template<
  template <typename, typename> typename BASE_TYPE,
  typename TOUCH_CH_TYPE,
  typename VALUE_TYPE = int16_t
>
struct TouchClippedValue {
  VALUE_TYPE min;
  VALUE_TYPE max;
  VALUE_TYPE _value = min;

  BASE_TYPE<TOUCH_CH_TYPE, VALUE_TYPE> base;

  IGB_FAST_INLINE void process() const noexcept {
    base.process();
    auto relative_value = base.value();
    if (relative_value.has_value()) {
      _value = std::clamp(_value + relative_value.value(), min, max);
    }
  }

  IGB_FAST_INLINE VALUE_TYPE value() const noexcept {
    return _value;
  }
};

template<typename TOUCH_CH_TYPE, typename VALUE_TYPE = int16_t>
using TouchRot3DialAbs = TouchClippedValue<TouchRot3Dial, TOUCH_CH_TYPE, VALUE_TYPE>;

template<typename TOUCH_CH_TYPE, typename VALUE_TYPE = int16_t>
using TouchRot3DialWithCenterAbs = TouchClippedValue<TouchRot3DialWithCenter, TOUCH_CH_TYPE, VALUE_TYPE>;

}
}

#endif /* IGB_SDK_UI_TOUCH_H */
