#ifndef __N1GP_SPI_DEF_STM32F072_H__
#define __N1GP_SPI_DEF_STM32F072_H__

#define SPI_DEF_STM32F072_SIZE 2
static const SpiDef spi_defs[SPI_DEF_STM32F072_SIZE] = {
  {SPI1},
  {SPI2},
};

static inline uint32_t spi_reset(uint8_t idx) {
  switch (idx) {
    case 0:
      {
        RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST);
        RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST);
        __IO uint32_t tmpreg;
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        tmpreg = RCC->APB2ENR & RCC_APB2ENR_SPI1EN;
      }
      break;
    case 1:
      {
        RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST);
        RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST);
        __IO uint32_t tmpreg;
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
        tmpreg = RCC->APB1ENR & RCC_APB1ENR_SPI2EN;
      }
      break;
    default:
      break;
  }
}

static inline uint32_t spi_pin_alternate(uint8_t pin) {
  uint32_t alternate = 0;
  switch (pin) {
    case PIN_A4:
    case PIN_A5:
    case PIN_A6:
    case PIN_A7:
    case PIN_A15:
    case PIN_B3:
    case PIN_B4:
    case PIN_B5:
    case PIN_B12:
    case PIN_B13:
    case PIN_B14:
    case PIN_B15:
      alternate = LL_GPIO_AF_0;
      break;
    case PIN_B9:
    case PIN_B10:
      alternate = LL_GPIO_AF_5;
      break;
    default:
      break;
  }
  return alternate;
}

static inline void spi_clock_enable(uint8_t idx) {
  switch (idx) {
    case 0:
      LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SPI1);
      break;
    case 1:
      LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
      break;
    default:
      break;
  }
}

#endif /* __N1GP_SPI_DEF_STM32F072_H__ */
