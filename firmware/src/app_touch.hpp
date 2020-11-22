#ifndef N1GP_APP_TOUCH_H
#define N1GP_APP_TOUCH_H

#include "debug.h"
#include <igb_sdk/util/text.h>
#include <igb_stm32/periph/tsc.hpp>
#include <igb_sdk/ui/touch.hpp>
#include <igb_util/cast.hpp>

using namespace igb;
using namespace igb::stm32;
using namespace igb::sdk;

enum class AppTouchPadID : uint8_t {
  L = 0,
  R,
};

struct AppTouch {
  Tsc tsc;
  std::function<void(AppTouchPadID, int16_t)> on_change;
  std::function<void(uint8_t)> on_acquisition_end;

  TouchRot3DialWithCenter<Tsc::Channel> l_pad {
    .channels = {tsc.newChannel(TscChannel::g5i4), tsc.newChannel(TscChannel::g5i3), tsc.newChannel(TscChannel::g5i2)},
    .center_channel = tsc.newChannel(TscChannel::g3i2),
    .steps = 16,
    .steps_on_center = 1
  };

  TouchRot3DialWithCenter<Tsc::Channel> r_pad {
    .channels = {tsc.newChannel(TscChannel::g1i4), tsc.newChannel(TscChannel::g1i3), tsc.newChannel(TscChannel::g1i2)},
    .center_channel = tsc.newChannel(TscChannel::g3i3),
    .steps = 16,
    .steps_on_center = 1
  };

  inline void resetDefaultSteps() {
    l_pad.steps = 16;
    r_pad.steps = 16;
    l_pad.steps_on_center = 1;
    r_pad.steps_on_center = 1;
  }

  inline void setSteps(int16_t l_steps, int16_t r_steps, int16_t l_steps_on_center=1, int16_t r_steps_on_center=1) {
    l_pad.steps = l_steps;
    r_pad.steps = r_steps;
    l_pad.steps_on_center = l_steps_on_center;
    r_pad.steps_on_center = r_steps_on_center;
  }

  inline uint8_t touch_bits_from(uint32_t bits) {
    return (!!(bits & (1UL << as<uint8_t>(TscChannel::g5i2))) << 2) | 
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g5i3))) << 1) |
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g5i4))) << 0) |
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g1i2))) << 5) | 
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g1i3))) << 4) |
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g1i4))) << 3) |
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g3i2))) << 6) |
      (!!(bits & (1UL << as<uint8_t>(TscChannel::g3i3))) << 7);
  }

  inline static bool is_left_bit(uint8_t bits) {
    return bits & (0b01000111);
  }

  inline static bool is_right_bit(uint8_t bits) {
    return bits & (0b10111000);
  }

  void init() {
    tsc.initDefault(
      // R Pad
      TscPinConf { TscChannel::g1i1, GpioPinType::pa0, TscIoType::samplingCap },
      TscPinConf { TscChannel::g1i2, GpioPinType::pa1, TscIoType::input },
      TscPinConf { TscChannel::g1i3, GpioPinType::pa2, TscIoType::input },
      TscPinConf { TscChannel::g1i4, GpioPinType::pa3, TscIoType::input },
      // L Pad
      TscPinConf { TscChannel::g5i1, GpioPinType::pb3, TscIoType::samplingCap },
      TscPinConf { TscChannel::g5i2, GpioPinType::pb4, TscIoType::input },
      TscPinConf { TscChannel::g5i3, GpioPinType::pb6, TscIoType::input },
      TscPinConf { TscChannel::g5i4, GpioPinType::pb7, TscIoType::input },
      // center pad
      TscPinConf { TscChannel::g3i1, GpioPinType::pc5, TscIoType::samplingCap },
      TscPinConf { TscChannel::g3i2, GpioPinType::pb0, TscIoType::input },
      TscPinConf { TscChannel::g3i3, GpioPinType::pb1, TscIoType::input }
    );
    tsc.setThreshold(TscChannel::g1i2, 1000);
    tsc.setThreshold(TscChannel::g1i3, 1000);
    tsc.setThreshold(TscChannel::g1i4, 1000);
    tsc.setThreshold(TscChannel::g5i2, 1000);
    tsc.setThreshold(TscChannel::g5i3, 1000);
    tsc.setThreshold(TscChannel::g5i4, 1000);
    tsc.setThreshold(TscChannel::g3i2, 1000);
    tsc.setThreshold(TscChannel::g3i3, 1000);

    tsc.on_acquisition_end = [this](uint32_t bits) {
      l_pad.process();
      r_pad.process();
      auto l_val = l_pad.value();
      if (l_val.has_value()) {
        on_change(AppTouchPadID::L, l_val.value());
      }
      auto r_val = r_pad.value();
      if (r_val.has_value()) {
        on_change(AppTouchPadID::R, r_val.value());
      }
      if (on_acquisition_end) {
        on_acquisition_end(touch_bits_from(bits));
      }
    };
  }

  void process() {
    tsc.process();
  }
};

extern AppTouch app_touch;

#endif /* N1GP_APP_TOUCH_H */
