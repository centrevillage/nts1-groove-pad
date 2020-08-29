struct PeriphBusInfo {
  const BusType   bus_type;
  const uint32_t  periph_bit;
};

#ifdef STM32_PERIPHGRP_RCC_EXISTS
struct RccInfo {
  const PeriphType   periph_type;
  const RCC_TypeDef* p_rcc;
};
#endif

#ifdef STM32_PERIPHGRP_GPIO_EXISTS
struct GpioInfo {
  const PeriphType    periph_type;
  const GPIO_TypeDef* p_gpio;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_TIM_EXISTS
enum class TimCategory {
  UNKNOWN = 0,
  ADVANCED,
  GENERAL,
  BASIC,
};
struct TimInfo {
  const PeriphType      periph_type;
  const TimCategory     category;
  const TIM_TypeDef*    p_tim;
  const IRQn_Type       irqn;
  const PeriphBusInfo   bus;
};
#endif

#ifdef STM32_PERIPHGRP_SPI_EXISTS
struct SpiInfo {
  const PeriphType   periph_type;
  const SPI_TypeDef* p_spi;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_I2C_EXISTS
struct I2cInfo {
  const PeriphType   periph_type;
  const I2C_TypeDef* p_i2c;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_USART_EXISTS
struct UsartInfo {
  const PeriphType   periph_type;
  const USART_TypeDef* p_usart;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_DAC_EXISTS
struct DacInfo {
  const PeriphType   periph_type;
  const DAC_TypeDef* p_dac;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_ADC_EXISTS
struct AdcInfo {
  const PeriphType   periph_type;
  const ADC_TypeDef* p_adc;
  const PeriphBusInfo bus;
};
#endif
