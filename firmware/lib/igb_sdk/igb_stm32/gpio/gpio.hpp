#ifndef IGB_STM32_GPIO_GPIO_H
#define IGB_STM32_GPIO_GPIO_H

#include <igb_stm32/base.hpp>

namespace igb_stm32 {

// TODO: MCU によって定義される値が違うかも？
enum class GPIOMode : uint32_t {
  INPUT = 0,
  OUTPUT = GPIO_MODER_MODER0_0,
  ALTERNATE = GPIO_MODER_MODER0_1,
  ANALOG = GPIO_MODER_MODER0
};

enum class GPIOSpeedMode : uint32_t {
  LOW = 0,
  MEDIUM = GPIO_OSPEEDR_OSPEEDR0_0,
  HIGH = GPIO_OSPEEDR_OSPEEDR0
};

enum class GPIOPullMode: uint32_t {
  NO = 0,
  UP = GPIO_PUPDR_PUPDR0_0,
  DOWN = GPIO_PUPDR_PUPDR0_1,
};

enum class GPIOOutputMode : uint32_t {
  PUSHPULL = 0,
  OPENDRAIN = GPIO_OTYPER_OT_0
};

struct GPIOPort {
  GPIO_TypeDef* p_gpio;

  void setMode(uint32_t pin_bit, GPIOMode mode) {
    MODIFY_REG(p_gpio->MODER, ((pin_bit * pin_bit) * GPIO_MODER_MODER0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  void setOutputMode(uint32_t pin_bit, GPIOOutputMode mode) {
    MODIFY_REG(p_gpio->OTYPER, pin_bit, (pin_bit * static_cast<uint32_t>(mode)));
  }

  void setPullMode(uint32_t pin_bit, GPIOPullMode mode) {
    MODIFY_REG(p_gpio->PUPDR, ((pin_bit * pin_bit) * GPIO_PUPDR_PUPDR0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  void setSpeedMode(uint32_t pin_bit, GPIOSpeedMode mode) {
    MODIFY_REG(p_gpio->OSPEEDR, ((pin_bit * pin_bit) * GPIO_OSPEEDR_OSPEEDR0), ((pin_bit * pin_bit) * static_cast<uint32_t>(mode)));
  }

  void on(uint32_t bits) {
    p_gpio->BSRR = bits;
  }

  void off(uint32_t bits) {
    p_gpio->BRR = bits;
  }

  uint32_t read() {
    return p_gpio->IDR;
  }

  uint32_t readOutput() {
    return p_gpio->ODR;
  }

  void enable() {
    // TODO: enable gpio clock
    // クロックがAHB,APB1,APB2 のどれに属するかはハードウェア依存なので、外部定義
  }

  void disable() {
    // TODO: disable gpio clock
  }

};

struct GPIOPin {
  GPIOPort port;
  const uint32_t pin_bit = 0;

  void setMode(GPIOMode mode) {
    port.setMode(pin_bit, mode);
  }

  void setOutputMode(GPIOOutputMode mode) {
    port.setOutputMode(pin_bit, mode);
  }

  void setPullMode(GPIOPullMode mode) {
    port.setPullMode(pin_bit, mode);
  }

  void setSpeedMode(GPIOSpeedMode mode) {
    port.setSpeedMode(pin_bit, mode);
  }

  void on() {
    port.on(pin_bit);
  }

  void off() {
    port.off(pin_bit);
  }

  void write(bool flag) {
    if (flag) {
      on();
    } else {
      off();
    }
  }

  bool read() {
    return port.read() & pin_bit;
  }

  bool readOutput() {
    return port.readOutput() & (pin_bit);
  }

  void initInput(GPIOPullMode pull, GPIOSpeedMode speed) {
    setMode(GPIOMode::INPUT);
    setPullMode(pull);
    setSpeedMode(speed);
  }

  void initOutput(GPIOOutputMode output_mode, GPIOSpeedMode speed) {
    setMode(GPIOMode::OUTPUT);
    setOutputMode(output_mode);
    setPullMode(GPIOPullMode::NO);
    setSpeedMode(speed);
  }

  // TODO: pin_idx と pin_bit は扱いが混乱しそうな気もする。
  //       一方で、それぞれに専用型を割り当てると利用が面倒になりそうな懸念もある。
  static GPIOPin newPin(const GPIOPort port_, uint8_t pin_idx) {
    return {
      .port = port_,
      .pin_bit = ((uint32_t)1 << pin_idx)
    };
  }
};

} // namespace igb_stm32

#endif /* IGB_STM32_GPIO_GPIO_H */