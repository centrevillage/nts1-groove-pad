struct PeriphBusInfo {
  const BusType   bus_type;
  const uint32_t  periph_bit;

  inline void enableBusClock() const {
    auto p_enr = STM32_BUS_TO_ENR_ADDRESS[ static_cast<uint32_t>(bus_type) ];
    (*p_enr) |= periph_bit;
    __IO auto tmp = (*p_enr); // delay until clock enabled
  }
};

struct GpioAfInfo {
  GPIO_TypeDef* const p_gpio;
  const uint16_t      pin_bit;
  const uint8_t       af_idx;
};

#ifdef STM32_PERIPHGRP_RCC_EXISTS
struct RccInfo {
  const PeriphType   periph_type;
  RCC_TypeDef* const p_rcc;
};
#endif

#ifdef STM32_PERIPHGRP_GPIO_EXISTS
struct GpioInfo {
  const PeriphType    periph_type;
  GPIO_TypeDef* const p_gpio;
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
  SPI_TypeDef* const p_spi;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_I2C_EXISTS
struct I2cInfo {
  const PeriphType   periph_type;
  I2C_TypeDef* const p_i2c;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_USART_EXISTS
struct UsartInfo {
  const PeriphType   periph_type;
  USART_TypeDef* const p_usart;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_DAC_EXISTS
struct DacInfo {
  const PeriphType   periph_type;
  DAC_TypeDef* const p_dac;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_ADC_EXISTS
struct AdcInfo {
  const PeriphType   periph_type;
  ADC_TypeDef* const p_adc;
  const PeriphBusInfo bus;
};
#endif

#ifdef STM32_PERIPHGRP_TSC_EXISTS
struct TscInfo {
  const PeriphType   periph_type;
  TSC_TypeDef* const p_tsc;
  const PeriphBusInfo bus;
};
#endif
