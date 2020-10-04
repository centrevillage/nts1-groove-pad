#ifndef IGB_STM32_PERIPH_GPIO_H
#define IGB_STM32_PERIPH_GPIO_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_util/macro.hpp>

namespace igb {
namespace stm32 {

// TODO: MCU によって定義される値が違うかも？
enum class GpioMode : uint32_t {
  INPUT = 0,
  OUTPUT = GPIO_MODER_MODER0_0,
  ALTERNATE = GPIO_MODER_MODER0_1,
  ANALOG = GPIO_MODER_MODER0
};

enum class GpioSpeedMode : uint32_t {
  LOW = 0,
  MEDIUM = GPIO_OSPEEDR_OSPEEDR0_0,
  HIGH = GPIO_OSPEEDR_OSPEEDR0
};

enum class GpioPullMode : uint32_t {
  NO = 0,
  UP = GPIO_PUPDR_PUPDR0_0,
  DOWN = GPIO_PUPDR_PUPDR0_1,
};

enum class GpioOutputMode : uint32_t {
  PUSHPULL = 0,
  OPENDRAIN = GPIO_OTYPER_OT_0
};

struct GpioPort {
  const GpioType type;
  GPIO_TypeDef* const p_gpio = STM32_PERIPH_INFO.gpio[as<uint8_t>(type)].p_gpio;

  IGB_FAST_INLINE void setMode(uint32_t pin_bit, GpioMode mode) {
    MODIFY_REG(p_gpio->MODER, ((pin_bit * pin_bit) * GPIO_MODER_MODER0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  IGB_FAST_INLINE void setOutputMode(uint32_t pin_bit, GpioOutputMode mode) {
    MODIFY_REG(p_gpio->OTYPER, pin_bit, (pin_bit * static_cast<uint32_t>(mode)));
  }

  IGB_FAST_INLINE void setPullMode(uint32_t pin_bit, GpioPullMode mode) {
    MODIFY_REG(p_gpio->PUPDR, ((pin_bit * pin_bit) * GPIO_PUPDR_PUPDR0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  IGB_FAST_INLINE void setSpeedMode(uint32_t pin_bit, GpioSpeedMode mode) {
    MODIFY_REG(p_gpio->OSPEEDR, ((pin_bit * pin_bit) * GPIO_OSPEEDR_OSPEEDR0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  IGB_FAST_INLINE void setAlternateFunc(uint32_t pin_bit, GpioAf af) {
    uint32_t lsb = pin_bit & 0x00FF;
    uint32_t msb = (pin_bit >> 8) & 0x00FF;
    if (lsb) {
      MODIFY_REG(p_gpio->AFR[0], ((((lsb * lsb) * lsb) * lsb) * GPIO_AFRL_AFSEL0), ((((lsb * lsb) * lsb) * lsb) * as<uint32_t>(af)));
    }
    if (msb) {
      MODIFY_REG(p_gpio->AFR[1], ((((msb * msb) * msb) * msb) * GPIO_AFRH_AFSEL8), ((((msb * msb) * msb) * msb) * as<uint32_t>(af)));
    }
  }

  IGB_FAST_INLINE void lock(uint32_t pin_bit) {
    WRITE_REG(p_gpio->LCKR, GPIO_LCKR_LCKK | pin_bit);
    WRITE_REG(p_gpio->LCKR, pin_bit);
    WRITE_REG(p_gpio->LCKR, GPIO_LCKR_LCKK | pin_bit);
    __IO uint32_t temp = READ_REG(p_gpio->LCKR);
  }

  IGB_FAST_INLINE void on(uint32_t bits) {
    p_gpio->BSRR = bits;
  }

  IGB_FAST_INLINE void high(uint32_t bits) {
    on(bits);
  }

  IGB_FAST_INLINE void off(uint32_t bits) {
    p_gpio->BRR = bits;
  }

  IGB_FAST_INLINE void low(uint32_t bits) {
    off(bits);
  }

  IGB_FAST_INLINE uint32_t read() {
    return p_gpio->IDR;
  }

  IGB_FAST_INLINE uint32_t readOutput() {
    return p_gpio->ODR;
  }

  IGB_FAST_INLINE void enable() {
    STM32_PERIPH_INFO.gpio[as<uint8_t>(type)].bus.enableBusClock();
  }

  IGB_FAST_INLINE void disable() {
    // TODO: clock の無効化
  }

};

struct GpioPin {
  GpioPort port;
  const uint32_t pin_bit = 0;

  IGB_FAST_INLINE void setMode(GpioMode mode) {
    port.setMode(pin_bit, mode);
  }

  IGB_FAST_INLINE void setOutputMode(GpioOutputMode mode) {
    port.setOutputMode(pin_bit, mode);
  }

  IGB_FAST_INLINE void setPullMode(GpioPullMode mode) {
    port.setPullMode(pin_bit, mode);
  }

  IGB_FAST_INLINE void setSpeedMode(GpioSpeedMode mode) {
    port.setSpeedMode(pin_bit, mode);
  }

  IGB_FAST_INLINE void setAlternateFunc(GpioAf af) {
    port.setAlternateFunc(pin_bit, af);
  }

  IGB_FAST_INLINE void lock() {
    port.lock(pin_bit);
  }

  IGB_FAST_INLINE void on() {
    port.on(pin_bit);
  }

  IGB_FAST_INLINE void high() {
    on();
  }

  IGB_FAST_INLINE void off() {
    port.off(pin_bit);
  }

  IGB_FAST_INLINE void low() {
    off();
  }

  IGB_FAST_INLINE void write(bool flag) {
    if (flag) {
      on();
    } else {
      off();
    }
  }

  IGB_FAST_INLINE bool read() {
    return port.read() & pin_bit;
  }

  IGB_FAST_INLINE bool readOutput() {
    return port.readOutput() & (pin_bit);
  }

  IGB_FAST_INLINE void enable() {
    port.enable();
  }

  IGB_FAST_INLINE void disable() {
    // TODO: clock の無効化
  }

  IGB_FAST_INLINE void initInput(GpioPullMode pull, GpioSpeedMode speed) {
    setMode(GpioMode::INPUT);
    setPullMode(pull);
    setSpeedMode(speed);
  }

  IGB_FAST_INLINE void initOutput(GpioOutputMode output_mode, GpioSpeedMode speed) {
    setMode(GpioMode::OUTPUT);
    setOutputMode(output_mode);
    setPullMode(GpioPullMode::NO);
    setSpeedMode(speed);
  }

  static IGB_FAST_INLINE GpioPin newPin(const GpioPinType pin_type) {
    GpioType gpio_type = extract_gpio_type(pin_type);
    uint8_t pin_idx = extract_pin_idx(pin_type);
    return GpioPin {
      .port = { gpio_type },
      .pin_bit = 1UL << pin_idx
    };
  }
};

} // namespace stm32
} // namespace igb

#endif /* IGB_STM32_PERIPH_GPIO_H */
