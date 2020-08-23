// Generated by svd_parser.rb. Dont't edit please.
#ifndef IGB_STM32_DEVICE_SVD_STM32F072X_H
#define IGB_STM32_DEVICE_SVD_STM32F072X_H

#include <igb_stm32/base.hpp>
#include <array>

#define STM32_PERIPHGRP_CRC_EXISTS 1
#define STM32_PERIPH_CRC_EXISTS 1
#define STM32_PERIPHGRP_GPIO_EXISTS 1
#define STM32_PERIPH_GPIOF_EXISTS 1
#define STM32_PERIPH_GPIOD_EXISTS 1
#define STM32_PERIPH_GPIOC_EXISTS 1
#define STM32_PERIPH_GPIOB_EXISTS 1
#define STM32_PERIPH_GPIOE_EXISTS 1
#define STM32_PERIPH_GPIOA_EXISTS 1
#define STM32_PERIPHGRP_SPI_EXISTS 1
#define STM32_PERIPH_SPI1_EXISTS 1
#define STM32_PERIPH_SPI2_EXISTS 1
#define STM32_PERIPHGRP_DAC_EXISTS 1
#define STM32_PERIPH_DAC_EXISTS 1
#define STM32_PERIPHGRP_PWR_EXISTS 1
#define STM32_PERIPH_PWR_EXISTS 1
#define STM32_PERIPHGRP_I2C_EXISTS 1
#define STM32_PERIPH_I2C1_EXISTS 1
#define STM32_PERIPH_I2C2_EXISTS 1
#define STM32_PERIPHGRP_IWDG_EXISTS 1
#define STM32_PERIPH_IWDG_EXISTS 1
#define STM32_PERIPHGRP_WWDG_EXISTS 1
#define STM32_PERIPH_WWDG_EXISTS 1
#define STM32_PERIPHGRP_TIM_EXISTS 1
#define STM32_PERIPH_TIM1_EXISTS 1
#define STM32_PERIPH_TIM2_EXISTS 1
#define STM32_PERIPH_TIM3_EXISTS 1
#define STM32_PERIPH_TIM14_EXISTS 1
#define STM32_PERIPH_TIM6_EXISTS 1
#define STM32_PERIPH_TIM7_EXISTS 1
#define STM32_PERIPH_TIM15_EXISTS 1
#define STM32_PERIPH_TIM16_EXISTS 1
#define STM32_PERIPH_TIM17_EXISTS 1
#define STM32_PERIPHGRP_EXTI_EXISTS 1
#define STM32_PERIPH_EXTI_EXISTS 1
#define STM32_PERIPHGRP_NVIC_EXISTS 1
#define STM32_PERIPH_NVIC_EXISTS 1
#define STM32_PERIPHGRP_DMA_EXISTS 1
#define STM32_PERIPH_DMA_EXISTS 1
#define STM32_PERIPHGRP_RCC_EXISTS 1
#define STM32_PERIPH_RCC_EXISTS 1
#define STM32_PERIPHGRP_SYSCFG_EXISTS 1
#define STM32_PERIPH_SYSCFG_EXISTS 1
#define STM32_PERIPHGRP_ADC_EXISTS 1
#define STM32_PERIPH_ADC1_EXISTS 1
#define STM32_PERIPHGRP_USART_EXISTS 1
#define STM32_PERIPH_USART1_EXISTS 1
#define STM32_PERIPH_USART2_EXISTS 1
#define STM32_PERIPH_USART3_EXISTS 1
#define STM32_PERIPH_USART4_EXISTS 1
#define STM32_PERIPHGRP_COMP_EXISTS 1
#define STM32_PERIPH_COMP_EXISTS 1
#define STM32_PERIPHGRP_RTC_EXISTS 1
#define STM32_PERIPH_RTC_EXISTS 1
#define STM32_PERIPHGRP_TSC_EXISTS 1
#define STM32_PERIPH_TSC_EXISTS 1
#define STM32_PERIPHGRP_CEC_EXISTS 1
#define STM32_PERIPH_CEC_EXISTS 1
#define STM32_PERIPHGRP_FLASH_EXISTS 1
#define STM32_PERIPH_FLASH_EXISTS 1
#define STM32_PERIPHGRP_DBGMCU_EXISTS 1
#define STM32_PERIPH_DBGMCU_EXISTS 1
#define STM32_PERIPHGRP_USB_EXISTS 1
#define STM32_PERIPH_USB_EXISTS 1
#define STM32_PERIPHGRP_CRS_EXISTS 1
#define STM32_PERIPH_CRS_EXISTS 1
#define STM32_PERIPHGRP_CAN_EXISTS 1
#define STM32_PERIPH_CAN_EXISTS 1

namespace igb_stm32 {

enum class PeriphGroupType : uint16_t {
  gpio = 0,
  spi,
  dac,
  i2c,
  tim,
  rcc,
  adc,
  usart,
};

enum class PeriphType : uint16_t {
  gpioa = 0,
  gpiob,
  gpioc,
  gpiod,
  gpioe,
  gpiof,
  spi1,
  spi2,
  dac,
  i2c1,
  i2c2,
  tim1,
  tim2,
  tim3,
  tim6,
  tim7,
  tim14,
  tim15,
  tim16,
  tim17,
  rcc,
  adc1,
  usart1,
  usart2,
  usart3,
  usart4,
};

enum class GpioType : uint8_t {
  gpioa = 0,
  gpiob,
  gpioc,
  gpiod,
  gpioe,
  gpiof,
};
enum class SpiType : uint8_t {
  spi1 = 0,
  spi2,
};
enum class DacType : uint8_t {
  dac = 0,
};
enum class I2cType : uint8_t {
  i2c1 = 0,
  i2c2,
};
enum class TimType : uint8_t {
  tim1 = 0,
  tim2,
  tim3,
  tim6,
  tim7,
  tim14,
  tim15,
  tim16,
  tim17,
};
enum class AdcType : uint8_t {
  adc1 = 0,
};
enum class UsartType : uint8_t {
  usart1 = 0,
  usart2,
  usart3,
  usart4,
};

enum class BusType : uint8_t {
  ahb = 0,
  apb1,
  apb2,
};

const std::array<__IO uint32_t*, 3> STM32_BUS_TO_ENR_ADDRESS = {
  &(RCC->AHBENR),
  &(RCC->APB1ENR),
  &(RCC->APB2ENR),
};

const std::array<__IO uint32_t*, 3> STM32_BUS_TO_RSTR_ADDRESS = {
  &(RCC->AHBRSTR),
  &(RCC->APB1RSTR),
  &(RCC->APB2RSTR),
};

#include <igb_stm32/base/_info.hpp>

const struct PeriphInfo {
  const std::array<GPIOInfo, 6> gpio {
    GPIOInfo {
      .periph_type = PeriphType::gpioa,
      .p_gpio = GPIOA,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 17},
    },
    GPIOInfo {
      .periph_type = PeriphType::gpiob,
      .p_gpio = GPIOB,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 18},
    },
    GPIOInfo {
      .periph_type = PeriphType::gpioc,
      .p_gpio = GPIOC,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 19},
    },
    GPIOInfo {
      .periph_type = PeriphType::gpiod,
      .p_gpio = GPIOD,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 20},
    },
    GPIOInfo {
      .periph_type = PeriphType::gpioe,
      .p_gpio = GPIOE,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 21},
    },
    GPIOInfo {
      .periph_type = PeriphType::gpiof,
      .p_gpio = GPIOF,
      .bus = PeriphBusInfo { BusType::ahb, (uint32_t)1 << 22},
    },
  };
  const std::array<SPIInfo, 2> spi {
    SPIInfo {
      .periph_type = PeriphType::spi1,
      .p_spi = SPI1,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 12},
    },
    SPIInfo {
      .periph_type = PeriphType::spi2,
      .p_spi = SPI2,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 14},
    },
  };
  const std::array<DACInfo, 1> dac {
    DACInfo {
      .periph_type = PeriphType::dac,
      .p_dac = DAC,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 29},
    },
  };
  const std::array<I2CInfo, 2> i2c {
    I2CInfo {
      .periph_type = PeriphType::i2c1,
      .p_i2c = I2C1,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 21},
    },
    I2CInfo {
      .periph_type = PeriphType::i2c2,
      .p_i2c = I2C2,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 22},
    },
  };
  const std::array<TIMInfo, 9> tim {
    TIMInfo {
      .periph_type = PeriphType::tim1,
      .type = TIMType::ADVANCED,
      .p_tim = TIM1,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 11},
    },
    TIMInfo {
      .periph_type = PeriphType::tim2,
      .type = TIMType::GENERAL,
      .p_tim = TIM2,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 0},
    },
    TIMInfo {
      .periph_type = PeriphType::tim3,
      .type = TIMType::GENERAL,
      .p_tim = TIM3,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 1},
    },
    TIMInfo {
      .periph_type = PeriphType::tim6,
      .type = TIMType::BASIC,
      .p_tim = TIM6,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 4},
    },
    TIMInfo {
      .periph_type = PeriphType::tim7,
      .type = TIMType::BASIC,
      .p_tim = TIM7,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 5},
    },
    TIMInfo {
      .periph_type = PeriphType::tim14,
      .type = TIMType::GENERAL,
      .p_tim = TIM14,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 8},
    },
    TIMInfo {
      .periph_type = PeriphType::tim15,
      .type = TIMType::GENERAL,
      .p_tim = TIM15,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 16},
    },
    TIMInfo {
      .periph_type = PeriphType::tim16,
      .type = TIMType::GENERAL,
      .p_tim = TIM16,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 17},
    },
    TIMInfo {
      .periph_type = PeriphType::tim17,
      .type = TIMType::GENERAL,
      .p_tim = TIM17,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 18},
    },
  };
  const RCCInfo rcc {
    .periph_type = PeriphType::rcc,
    .p_rcc = RCC,
  };
  const std::array<ADCInfo, 1> adc {
    ADCInfo {
      .periph_type = PeriphType::adc1,
      .p_adc = ADC1,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 9},
    },
  };
  const std::array<USARTInfo, 4> usart {
    USARTInfo {
      .periph_type = PeriphType::usart1,
      .p_usart = USART1,
      .bus = PeriphBusInfo { BusType::apb2, (uint32_t)1 << 14},
    },
    USARTInfo {
      .periph_type = PeriphType::usart2,
      .p_usart = USART2,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 17},
    },
    USARTInfo {
      .periph_type = PeriphType::usart3,
      .p_usart = USART3,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 18},
    },
    USARTInfo {
      .periph_type = PeriphType::usart4,
      .p_usart = USART4,
      .bus = PeriphBusInfo { BusType::apb1, (uint32_t)1 << 19},
    },
  };
} STM32_PERIPH_INFO;

}

#endif /* IGB_STM32_DEVICE_SVD_STM32F072X_H */
