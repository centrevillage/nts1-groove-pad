#ifndef IGB_STM32_PERIPH_TSC_H
#define IGB_STM32_PERIPH_TSC_H

#include <functional>
#include <igb_stm32/base.hpp>
#include <igb_stm32/periph/gpio.hpp>
#include <igb_util/cast.hpp>
#include <igb_util/macro.hpp>
#include <igb_util/container.hpp>
#include <igb_util/bitmagic.hpp>

namespace igb {
namespace stm32 {

enum class TscAcquisitionMode : uint8_t {
  normal       = 0,
  synchronized = 1
};

enum class TscSyncPolarity : uint8_t {
  fallingEdgeOnly = 0,
  risingEdgeAndHighLevel = 1
};

enum class TscIoDefaultMode : uint8_t {
  pushpullLow = 0,
  inputFloating = 1
};

enum class TscMaxCount : uint8_t {
  _255 = 0,
  _511,
  _1023,
  _2047,
  _4095,
  _8191,
  _16383
};

enum class TscPulsePrescaler : uint8_t {
  div1 = 0,
  div2,
  div4,
  div8,
  div16,
  div32,
  div64,
  div128,
};

enum class TscSpreadSpectrumPrescaler : uint8_t {
  div1 = 0,
  div2,
};

enum class TscGroup : uint8_t {
  g1 = 0,
  g2,
  g3,
  g4,
  g5,
  g6,
  g7,
  g8,
};

enum class TscChannel : uint8_t {
  g1i1 = 0,
  g1i2,
  g1i3,
  g1i4,
  g2i1,
  g2i2,
  g2i3,
  g2i4,
  g3i1,
  g3i2,
  g3i3,
  g3i4,
  g4i1,
  g4i2,
  g4i3,
  g4i4,
  g5i1,
  g5i2,
  g5i3,
  g5i4,
  g6i1,
  g6i2,
  g6i3,
  g6i4,
  g7i1,
  g7i2,
  g7i3,
  g7i4,
  g8i1,
  g8i2,
  g8i3,
  g8i4,
};

using TscGroupBit = BitStruct<TscGroup, uint32_t>;
using TscChannelBit = BitStruct<TscChannel, uint32_t>;

struct TscCtrl {
  //constexpr static TSC_TypeDef* const p_tsc = STM32_PERIPH_INFO.tsc.p_tsc;

  static IGB_FAST_INLINE void enableBusClock() {
    STM32_PERIPH_INFO.tsc.bus.enableBusClock();
  }

  static IGB_FAST_INLINE void enable() {
    STM32_PERIPH_INFO.tsc.p_tsc->CR |= TSC_CR_TSCE;
  }

  static IGB_FAST_INLINE void disable() {
    STM32_PERIPH_INFO.tsc.p_tsc->CR &= ~TSC_CR_TSCE;
  }

  static IGB_FAST_INLINE void start() {
    STM32_PERIPH_INFO.tsc.p_tsc->ICR |= TSC_ICR_EOAIC | TSC_ICR_MCEIC; // request clearing MCEF and EOAF flags 
    STM32_PERIPH_INFO.tsc.p_tsc->CR |= TSC_CR_START;
  }

  static IGB_FAST_INLINE void setAcquisitionMode(TscAcquisitionMode mode) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_AM, mode);
  }

  static IGB_FAST_INLINE void setSyncPolarity(TscSyncPolarity polarity) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_SYNCPOL, polarity);
  }

  static IGB_FAST_INLINE void setIoDefaultMode(TscIoDefaultMode mode) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_IODEF, mode);
  }

  static IGB_FAST_INLINE void setMaxCount(TscMaxCount count) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_MCV, count);
  }

  static IGB_FAST_INLINE void setPulsePrescaler(TscPulsePrescaler prescaler) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_PGPSC, prescaler);
  }

  static IGB_FAST_INLINE void setSpreadSpectrumPrescaler(TscSpreadSpectrumPrescaler prescaler) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_SSPSC, prescaler);
  }

  static IGB_FAST_INLINE void enableSpreadSpectrum() {
    STM32_PERIPH_INFO.tsc.p_tsc->CR |= TSC_CR_SSE;
  }

  static IGB_FAST_INLINE void disableSpreadSpectrum() {
    STM32_PERIPH_INFO.tsc.p_tsc->CR &= ~TSC_CR_SSE;
  }

  static IGB_FAST_INLINE void setSpreadSpectrumDeviation(uint8_t deviation) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_SSD, deviation & 0x7F);
  }

  static IGB_FAST_INLINE void setChargePulseLow(uint8_t pulse_duration) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_CTPL, pulse_duration & 0x0F);
  }

  static IGB_FAST_INLINE void setChargePulseHigh(uint8_t pulse_duration) {
    MODIFY_REG_SIMPLE(STM32_PERIPH_INFO.tsc.p_tsc->CR, TSC_CR_CTPH, pulse_duration & 0x0F);
  }

  static IGB_FAST_INLINE void setSamplingCap(TscChannel io) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOSCR |= 1UL << static_cast<uint32_t>(io);
  }

  static IGB_FAST_INLINE void setSamplingCap(TscChannelBit bit) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOSCR = bit.get();
  }

  static IGB_FAST_INLINE void clearSamplingCap() {
    STM32_PERIPH_INFO.tsc.p_tsc->IOSCR = 0;
  }

  static IGB_FAST_INLINE void enableHysteresisCtrl(TscChannel io) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOHCR |= 1UL << static_cast<uint32_t>(io);
  }

  static IGB_FAST_INLINE void clearHisteresisCtrl() {
    STM32_PERIPH_INFO.tsc.p_tsc->IOHCR = 0;
  }

  static IGB_FAST_INLINE void setHysteresisCtrlBit(TscChannelBit bit) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOHCR = bit.get();
  }

  static IGB_FAST_INLINE void enableGroup(TscGroup group) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOGCSR |= 1UL << static_cast<uint32_t>(group);
  }

  static IGB_FAST_INLINE void disableGroup(TscGroup group) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOGCSR &= ~(1UL << static_cast<uint32_t>(group));
  }

  static IGB_FAST_INLINE void setGroupCtrl(TscGroupBit bit) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOGCSR = bit.get();
  }

  static IGB_FAST_INLINE void enableChannel(TscChannel ch) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOCCR |= 1UL << static_cast<uint32_t>(ch);
  }

  static IGB_FAST_INLINE void setChannelCtrl(TscChannelBit bit) {
    STM32_PERIPH_INFO.tsc.p_tsc->IOCCR = bit.get();
  }

  static IGB_FAST_INLINE uint16_t value(TscGroup group) {
    return STM32_PERIPH_INFO.tsc.p_tsc->IOGXCR[static_cast<uint8_t>(group)];
  }

  static bool IGB_FAST_INLINE isEoc() {
    return (STM32_PERIPH_INFO.tsc.p_tsc->ISR & 0x01);
  }

  static bool IGB_FAST_INLINE isError() {
    return (STM32_PERIPH_INFO.tsc.p_tsc->ISR & 0x02);
  }
};


constexpr TscGroup tsc_pin_to_group(TscChannel ch) {
  switch (ch) {
    case TscChannel::g1i1:
    case TscChannel::g1i2:
    case TscChannel::g1i3:
    case TscChannel::g1i4:
      return TscGroup::g1;
      [[fallthrough]];
    case TscChannel::g2i1:
    case TscChannel::g2i2:
    case TscChannel::g2i3:
    case TscChannel::g2i4:
      return TscGroup::g2;
      [[fallthrough]];
    case TscChannel::g3i1:
    case TscChannel::g3i2:
    case TscChannel::g3i3:
    case TscChannel::g3i4:
      return TscGroup::g3;
      [[fallthrough]];
    case TscChannel::g4i1:
    case TscChannel::g4i2:
    case TscChannel::g4i3:
    case TscChannel::g4i4:
      return TscGroup::g4;
      [[fallthrough]];
    case TscChannel::g5i1:
    case TscChannel::g5i2:
    case TscChannel::g5i3:
    case TscChannel::g5i4:
      return TscGroup::g5;
      [[fallthrough]];
    case TscChannel::g6i1:
    case TscChannel::g6i2:
    case TscChannel::g6i3:
    case TscChannel::g6i4:
      return TscGroup::g6;
      [[fallthrough]];
    case TscChannel::g7i1:
    case TscChannel::g7i2:
    case TscChannel::g7i3:
    case TscChannel::g7i4:
      return TscGroup::g7;
      [[fallthrough]];
    case TscChannel::g8i1:
    case TscChannel::g8i2:
    case TscChannel::g8i3:
    case TscChannel::g8i4:
      return TscGroup::g8;
      [[fallthrough]];
    default:
      break;
  }
  return TscGroup::g1;
}

enum class TscIoType {
  none = 0,
  input,
  samplingCap
};

struct TscPinConf {
  TscChannel channel;
  GpioPinType pin_type;
  TscIoType io_type;
};

enum class TscProcessState : uint8_t {
  ready = 0,
  start
};

enum class TscTouchState : uint8_t {
  inactive = 0,
  released,
  pressed
};

struct TscChannelState {
  uint16_t threshold = 500;
  uint16_t value = 2000;
  TscTouchState state;
};

struct Tsc {
  struct Channel {
    const TscChannelState& channel;

    IGB_FAST_INLINE bool read() const noexcept {
      return channel.state == TscTouchState::pressed;
    }

    IGB_FAST_INLINE uint16_t getValue() const noexcept {
      return channel.value;
    }

    IGB_FAST_INLINE uint16_t getThreshold() const noexcept {
      return channel.threshold;
    }
  };

  static const uint16_t MAX_COUNT = 16383;
  static const uint8_t CHANNEL_MAX = 32;
  static const uint8_t CHANNEL_SIZE_OF_GROUP = 4;
  static const uint8_t GROUP_MAX = 8;
  constexpr static const uint32_t CH_OF_GRP_MASK[8] = {
    (0b0001UL << 0) | (0b0001UL << 4) | (0b0001UL << 8) | (0b0001UL << 12) | (0b0001UL << 16) | (0b0001UL << 20) | (0b0001UL << 24) | (0b0001UL << 28),
    (0b0010UL << 0) | (0b0010UL << 4) | (0b0010UL << 8) | (0b0010UL << 12) | (0b0010UL << 16) | (0b0010UL << 20) | (0b0010UL << 24) | (0b0010UL << 28),
    (0b0100UL << 0) | (0b0100UL << 4) | (0b0100UL << 8) | (0b0100UL << 12) | (0b0100UL << 16) | (0b0100UL << 20) | (0b0100UL << 24) | (0b0100UL << 28),
    (0b1000UL << 0) | (0b1000UL << 4) | (0b1000UL << 8) | (0b1000UL << 12) | (0b1000UL << 16) | (0b1000UL << 20) | (0b1000UL << 24) | (0b1000UL << 28),
  };

  TscGroupBit group_bit;
  TscChannelBit channel_bit;
  TscChannelBit sampling_cap_bit;
  TscChannelBit input_ch_bit;
  TscChannelState channels[CHANNEL_MAX];
  uint32_t touch_bit;
  std::function<void(uint32_t)> on_acquisition_end;

  TscProcessState _state = TscProcessState::ready;
  uint8_t _process_ch_of_grp_idx = 0;
  uint32_t _touch_bits = 0;

  // auto = TscPinConf
  static IGB_FAST_INLINE void prepareGpio(GpioPinType pin_type, TscIoType io_type) {
    auto result = get_af_idx(PeriphType::tsc, pin_type);
    if (!(result.has_value())) { return; }
    if (io_type == TscIoType::none) { return; }

    GpioPin pin = GpioPin::newPin(pin_type);
    pin.setMode(GpioMode::ALTERNATE);
    pin.setPullMode(GpioPullMode::NO);
    pin.setSpeedMode(GpioSpeedMode::MEDIUM);
    if (io_type == TscIoType::input) {
      pin.setOutputMode(GpioOutputMode::PUSHPULL);
    } else { // sampling cap
      pin.setOutputMode(GpioOutputMode::OPENDRAIN);
    }
    pin.setAlternateFunc(result.value());
  }

  static IGB_FAST_INLINE void prepareGpios(auto&& first, auto&&... rest) {
    prepareGpio(first.pin_type, first.io_type);
    prepareGpios(rest...);
  }
  static IGB_FAST_INLINE void prepareGpios() { }

  static IGB_FAST_INLINE TscGroupBit constructGroupBit(auto&& first, auto&&... rest) {
    return TscGroupBit(tsc_pin_to_group(first.channel)) | constructGroupBit(rest...);
  }
  static IGB_FAST_INLINE TscGroupBit constructGroupBit() { return TscGroupBit {}; }

  static IGB_FAST_INLINE TscChannelBit constructChannelBit(auto&& first, auto&&... rest) {
    return TscChannelBit(first.channel) | constructChannelBit(rest...);
  }
  static IGB_FAST_INLINE TscChannelBit constructChannelBit() { return TscChannelBit {}; }

  static IGB_FAST_INLINE TscChannelBit constructSamplingCapBit(auto&& first, auto&&... rest) {
    return (first.io_type == TscIoType::samplingCap ? TscChannelBit(first.channel) : (TscChannelBit {})) | constructSamplingCapBit(rest...);
  }
  static IGB_FAST_INLINE TscChannelBit constructSamplingCapBit() { return TscChannelBit {}; }

  static IGB_FAST_INLINE TscChannelBit constructInputChBit(auto&& first, auto&&... rest) {
    return (first.io_type == TscIoType::samplingCap ? (TscChannelBit {}) : TscChannelBit(first.channel)) | constructInputChBit(rest...);
  }
  static IGB_FAST_INLINE TscChannelBit constructInputChBit() { return TscChannelBit {}; }

  IGB_FAST_INLINE void setThreshold(TscChannel channel, uint16_t threshold) {
    channels[static_cast<uint8_t>(channel)].threshold = threshold;
  }

  IGB_FAST_INLINE void initConfigDefault() {
    TscCtrl::enableBusClock();
    TscCtrl::setMaxCount(TscMaxCount::_16383);
    TscCtrl::setPulsePrescaler(TscPulsePrescaler::div4);
    TscCtrl::setChargePulseLow(1);
    TscCtrl::setChargePulseHigh(1);
    TscCtrl::enable();
    TscCtrl::setSamplingCap(sampling_cap_bit);
    TscCtrl::clearHisteresisCtrl();
    TscCtrl::setGroupCtrl(group_bit);
    
    for (uint8_t i = 0; i < CHANNEL_MAX; ++i) {
      if (input_ch_bit & (1UL << i)) {
        channels[i].state = TscTouchState::released;
      } else {
        channels[i].state = TscTouchState::inactive;
      }
    }
  }

  IGB_FAST_INLINE void initDefault(auto&&... confs) {
    prepareGpios(confs...);
    group_bit = constructGroupBit(confs...);
    channel_bit = constructChannelBit(confs...);
    sampling_cap_bit = constructSamplingCapBit(confs...);
    input_ch_bit = constructInputChBit(confs...);
    initConfigDefault();
    _state = TscProcessState::ready;
    _process_ch_of_grp_idx = 0;
    _touch_bits = 0;
  }

  IGB_FAST_INLINE void startAcquisition() {
    TscCtrl::setChannelCtrl(input_ch_bit & CH_OF_GRP_MASK[_process_ch_of_grp_idx]);
    TscCtrl::start();
  }

  IGB_FAST_INLINE void execAcquisition() {
    for (uint8_t i = _process_ch_of_grp_idx; i < CHANNEL_MAX; i += CHANNEL_SIZE_OF_GROUP) {
      TscChannelState& ch = channels[i];
      if (ch.state != TscTouchState::inactive) {
        uint16_t v = TscCtrl::value(static_cast<TscGroup>(i / CHANNEL_SIZE_OF_GROUP));
        if (v == MAX_COUNT) {
          continue;
        }
        ch.value = v;
        if (ch.value < ch.threshold) {
          if (ch.state == TscTouchState::released) {
            ch.state = TscTouchState::pressed;
            _touch_bits |= (1UL << i);
          }
        } else {
          if (ch.state == TscTouchState::pressed) {
            ch.state = TscTouchState::released;
            _touch_bits &= ~(1UL << i);
          }
        }
      }
    }
  }

  void process() {
    if (!input_ch_bit) { return; }
    if (_state == TscProcessState::ready) {
      startAcquisition();
      _state = TscProcessState::start;
    } else {
      if (TscCtrl::isEoc()) {
        execAcquisition();
        uint8_t next_idx = _process_ch_of_grp_idx + 1;
        while (!(input_ch_bit & CH_OF_GRP_MASK[next_idx]) && next_idx < CHANNEL_SIZE_OF_GROUP) { ++next_idx; }
        if (next_idx < CHANNEL_SIZE_OF_GROUP) {
        } else {
          if (on_acquisition_end) {
            on_acquisition_end(_touch_bits);
          }
          //_touch_bits = 0;
          next_idx = 0;
          while (!(input_ch_bit & CH_OF_GRP_MASK[next_idx]) && next_idx < CHANNEL_SIZE_OF_GROUP) { ++next_idx; }
        }
        _process_ch_of_grp_idx = next_idx;
        _state = TscProcessState::ready;
      }
    }
  }

  IGB_FAST_INLINE Channel newChannel(TscChannel ch) {
    return Channel {
      .channel = channels[static_cast<uint8_t>(ch)]
    };
  }
};

}
}

#endif /* IGB_STM32_PERIPH_TSC_H */
