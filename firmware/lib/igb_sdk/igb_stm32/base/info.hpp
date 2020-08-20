#ifndef IGB_STM32_BASE_DEVICE_INFO_H
#define IGB_STM32_BASE_DEVICE_INFO_H

#include <igb_stm32/base.hpp>

namespace igb_stm32 {
//  namespace device {
//    namespace info {
//      struct PeripheralBus {
//        volatile uint32_t* clock_bus_reg;
//        const uint32_t id_bit;

//        void enable() {
//          SET_BIT(*clock_bus_reg, id_bit);
//          volatile uint32_t tmp = READ_BIT(*clock_bus_reg, id_bit);
//        };

//        void disable() {
//          CLEAR_BIT(*clock_bus_reg, bus.id_bit);
//        }
//      };

//      struct Timer {
//        PeripheralBus bus;
//      };

//      struct GPIOPort {
//        PeripheralBus bus;
//        const GPIO_TypeDef* p_gpio;
//      };
//    }
//  }

#ifdef STM32_PERIPHGRP_GPIO_EXISTS
struct GPIOInfo {
  const GPIO_TypeDef* p_gpio;
};
#endif

#ifdef STM32_PERIPHGRP_TIM_EXISTS
enum class TIMType {
  UNKNOWN = 0,
  ADVANCED,
  GENERAL,
  BASIC,
};
struct TIMInfo {
  const   TIMType      type;
  const   TIM_TypeDef* p_tim;
};
#endif

#ifdef STM32_PERIPHGRP_RCC_EXISTS
struct RCCInfo {
  const RCC_TypeDef* p_rcc;
};
#endif

#ifdef STM32_PERIPHGRP_SPI_EXISTS
struct SPIInfo {
  const SPI_TypeDef* p_spi;
};
#endif

#ifdef STM32_PERIPHGRP_I2C_EXISTS
struct I2CInfo {
  const I2C_TypeDef* p_i2c;
};
#endif

#ifdef STM32_PERIPHGRP_USART_EXISTS
struct USARTInfo {
  const USART_TypeDef* p_usart;
};
#endif

#ifdef STM32_PERIPHGRP_DAC_EXISTS
struct DACInfo {
  const DAC_TypeDef* p_dac;
};
#endif

#ifdef STM32_PERIPHGRP_ADC_EXISTS
struct ADCInfo {
  const ADC_TypeDef* p_adc;
  const ADC_Common_TypeDef* p_adc_common;
};
#endif

}

#endif /* IGB_STM32_BASE_DEVICE_INFO_H */
