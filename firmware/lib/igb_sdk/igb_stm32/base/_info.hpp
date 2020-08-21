struct PeriphBusInfo {
  const BusType   bus_type;
  const uint32_t  periph_bit;
};

#ifdef STM32_PERIPHGRP_RCC_EXISTS
struct RCCInfo {
  const PeriphType   periph_type;
  const RCC_TypeDef* p_rcc;
};
#endif

#ifdef STM32_PERIPHGRP_GPIO_EXISTS
struct GPIOInfo {
  const PeriphType    periph_type;
  const GPIO_TypeDef* p_gpio;
  const PeriphBusInfo bus;
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
  const PeriphType      periph_type;
  const TIMType         type;
  const TIM_TypeDef*    p_tim;
  const PeriphBusInfo   bus;
};
#endif

#ifdef STM32_PERIPHGRP_SPI_EXISTS
struct SPIInfo {
  const PeriphType   periph_type;
  const SPI_TypeDef* p_spi;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_I2C_EXISTS
struct I2CInfo {
  const PeriphType   periph_type;
  const I2C_TypeDef* p_i2c;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_USART_EXISTS
struct USARTInfo {
  const PeriphType   periph_type;
  const USART_TypeDef* p_usart;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_DAC_EXISTS
struct DACInfo {
  const PeriphType   periph_type;
  const DAC_TypeDef* p_dac;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_ADC_EXISTS
struct ADCInfo {
  const PeriphType   periph_type;
  const ADC_TypeDef* p_adc;
  const PeriphBusInfo bus;
};
#endif
