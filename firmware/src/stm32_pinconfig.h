#ifndef __N1GP_STM32_PINCONFIG_H__
#define __N1GP_STM32_PINCONFIG_H__

#include "common.h"

#define PIN_A0 0x00
#define PIN_A1 0x01
#define PIN_A2 0x02
#define PIN_A3 0x03
#define PIN_A4 0x04
#define PIN_A5 0x05
#define PIN_A6 0x06
#define PIN_A7 0x07
#define PIN_A8 0x08
#define PIN_A9 0x09
#define PIN_A10 0x0A
#define PIN_A11 0x0B
#define PIN_A12 0x0C
#define PIN_A13 0x0D
#define PIN_A14 0x0E
#define PIN_A15 0x0F

#define PIN_B0 0x10
#define PIN_B1 0x11
#define PIN_B2 0x12
#define PIN_B3 0x13
#define PIN_B4 0x14
#define PIN_B5 0x15
#define PIN_B6 0x16
#define PIN_B7 0x17
#define PIN_B8 0x18
#define PIN_B9 0x19
#define PIN_B10 0x1A
#define PIN_B11 0x1B
#define PIN_B12 0x1C
#define PIN_B13 0x1D
#define PIN_B14 0x1E
#define PIN_B15 0x1F

#define PIN_C0 0x20
#define PIN_C1 0x21
#define PIN_C2 0x22
#define PIN_C3 0x23
#define PIN_C4 0x24
#define PIN_C5 0x25
#define PIN_C6 0x26
#define PIN_C7 0x27
#define PIN_C8 0x28
#define PIN_C9 0x29
#define PIN_C10 0x2A
#define PIN_C11 0x2B
#define PIN_C12 0x2C
#define PIN_C13 0x2D
#define PIN_C14 0x2E
#define PIN_C15 0x2F

#define PIN_D0 0x30
#define PIN_D1 0x31
#define PIN_D2 0x32
#define PIN_D3 0x33
#define PIN_D4 0x34
#define PIN_D5 0x35
#define PIN_D6 0x36
#define PIN_D7 0x37
#define PIN_D8 0x38
#define PIN_D9 0x39
#define PIN_D10 0x3A
#define PIN_D11 0x3B
#define PIN_D12 0x3C
#define PIN_D13 0x3D
#define PIN_D14 0x3E
#define PIN_D15 0x3F

#define PIN_E0 0x40
#define PIN_E1 0x41
#define PIN_E2 0x42
#define PIN_E3 0x43
#define PIN_E4 0x44
#define PIN_E5 0x45
#define PIN_E6 0x46
#define PIN_E7 0x47
#define PIN_E8 0x48
#define PIN_E9 0x49
#define PIN_E10 0x4A
#define PIN_E11 0x4B
#define PIN_E12 0x4C
#define PIN_E13 0x4D
#define PIN_E14 0x4E
#define PIN_E15 0x4F

#define PIN_F0 0x50
#define PIN_F1 0x51
#define PIN_F2 0x52
#define PIN_F3 0x53
#define PIN_F4 0x54
#define PIN_F5 0x55
#define PIN_F6 0x56
#define PIN_F7 0x57
#define PIN_F8 0x58
#define PIN_F9 0x59
#define PIN_F10 0x5A
#define PIN_F11 0x5B
#define PIN_F12 0x5C
#define PIN_F13 0x5D
#define PIN_F14 0x5E
#define PIN_F15 0x5F

FORCE_INLINE GPIO_TypeDef* get_gpio_typedef(uint8_t pin) {
  GPIO_TypeDef* gpio = 0;
  switch (pin>>4) {
    case 0:
      gpio = GPIOA;
      break;
    case 1:
      gpio = GPIOB;
      break;
    case 2:
      gpio = GPIOC;
      break;
    case 3:
      gpio = GPIOD;
      break;
    case 4:
      gpio = GPIOE;
      break;
    case 5:
      gpio = GPIOF;
      break;
  }
  return gpio;
}

FORCE_INLINE uint16_t get_gpio_pin_bits(uint8_t pin) {
  return (uint16_t)1 << (pin & 0x0F);
}

FORCE_INLINE uint8_t gpio_read(uint8_t pin) {
  GPIO_TypeDef* gpio = get_gpio_typedef(pin);
  return !!((gpio->IDR) & get_gpio_pin_bits(pin));
}

FORCE_INLINE void gpio_write(uint8_t pin, uint8_t flag) {
  GPIO_TypeDef* gpio = get_gpio_typedef(pin);
  uint16_t pin_bits = get_gpio_pin_bits(pin);
  if (flag) {
    gpio->BSRR = pin_bits;
  } else {
    gpio->BRR = pin_bits;
  }
}

#endif /* __N1GP_STM32_PINCONFIG_H__ */
