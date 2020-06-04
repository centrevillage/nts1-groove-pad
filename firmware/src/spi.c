#include "spi.h"

#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_spi.h"
#include "stm32f0xx_ll_bus.h"

#include "spi_def.h"

// TODO: consider APB1, APB2 clock rate
inline uint32_t _spi_baudrate_div(uint32_t baudrate) {
  uint32_t div = SystemCoreClock / baudrate;
  if (div < 4) {
    return LL_SPI_BAUDRATEPRESCALER_DIV2;
  }
  if (div < 8) {
    return LL_SPI_BAUDRATEPRESCALER_DIV4;
  }
  if (div < 16) {
    return LL_SPI_BAUDRATEPRESCALER_DIV8;
  }
  if (div < 32) {
    return LL_SPI_BAUDRATEPRESCALER_DIV16;
  }
  if (div < 64) {
    return LL_SPI_BAUDRATEPRESCALER_DIV32;
  }
  if (div < 128) {
    return LL_SPI_BAUDRATEPRESCALER_DIV64;
  }
  if (div < 256) {
    return LL_SPI_BAUDRATEPRESCALER_DIV128;
  }
  return LL_SPI_BAUDRATEPRESCALER_DIV256;
}

void spi_simple_setup(uint8_t spi_idx, uint8_t mosi_pin, uint8_t miso_pin, uint8_t sck_pin, uint32_t baudrate) {
  SpiDef spi_def = spi_def_get(spi_idx);

  spi_clock_enable(spi_idx);

  LL_GPIO_InitTypeDef gpio = {0};
  gpio.Mode = LL_GPIO_MODE_ALTERNATE;
  gpio.Pull = LL_GPIO_PULL_NO;
  gpio.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  gpio.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

  gpio.Alternate = spi_pin_alternate(mosi_pin);
  gpio.Pin = get_gpio_pin_bits(mosi_pin);
  LL_GPIO_Init(get_gpio_typedef(mosi_pin), &gpio);

  gpio.Alternate = spi_pin_alternate(miso_pin);
  gpio.Pin = get_gpio_pin_bits(miso_pin);
  LL_GPIO_Init(get_gpio_typedef(miso_pin), &gpio);

  gpio.Alternate = spi_pin_alternate(sck_pin);
  gpio.Pin = get_gpio_pin_bits(sck_pin);
  LL_GPIO_Init(get_gpio_typedef(sck_pin), &gpio);

  spi_reset(spi_idx);

  LL_SPI_InitTypeDef spi = {0};

  spi.TransferDirection = LL_SPI_FULL_DUPLEX;
  spi.Mode = LL_SPI_MODE_MASTER;
  spi.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  spi.ClockPolarity = LL_SPI_POLARITY_LOW;
  spi.ClockPhase = LL_SPI_PHASE_1EDGE;
  spi.NSS = LL_SPI_NSS_SOFT;
  spi.BaudRate = _spi_baudrate_div(baudrate);
  spi.BitOrder = LL_SPI_MSB_FIRST;
  spi.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  spi.CRCPoly = 7;

  LL_SPI_Init(spi_def.p_spi, &spi);
  LL_SPI_SetStandard(spi_def.p_spi, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_SetRxFIFOThreshold(spi_def.p_spi, LL_SPI_RX_FIFO_TH_QUARTER);
  LL_SPI_Enable(spi_def.p_spi);
  LL_SPI_EnableNSSPulseMgt(spi_def.p_spi);
}

uint8_t spi_transmit(uint8_t spi_idx, uint8_t data) {
  SPI_TypeDef* p_spi = spi_def_get(spi_idx).p_spi;
  while (LL_SPI_IsActiveFlag_BSY(p_spi));
  if (!LL_SPI_IsEnabled(p_spi)) LL_SPI_Enable(p_spi);
  while (!LL_SPI_IsActiveFlag_TXE(p_spi));
  LL_SPI_TransmitData8(p_spi, data);
  while (!LL_SPI_IsActiveFlag_RXNE(p_spi));
  return LL_SPI_ReceiveData8(p_spi);
}

uint8_t spi_is_busy(uint8_t spi_idx) {
  return LL_SPI_IsActiveFlag_BSY(spi_def_get(spi_idx).p_spi);
}

