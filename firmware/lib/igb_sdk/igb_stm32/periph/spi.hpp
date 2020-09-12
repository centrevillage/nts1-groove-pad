#ifndef IGB_STM32_PERIPH_SPI_H
#define IGB_STM32_PERIPH_SPI_H

#include <igb_stm32/base.hpp>
#include <igb_util/cast.hpp>
#include <igb_stm32/periph/gpio.hpp>
#include <igb_stm32/periph/rcc.hpp>

using igb_util::as;

namespace igb_stm32 {

enum class SpiMode : uint32_t {
  SLAVE  = 0,
  MASTER = (SPI_CR1_MSTR | SPI_CR1_SSI),
};

enum class SpiStandard : uint32_t {
  MOTOROLA = 0,
  TI = SPI_CR2_FRF,
};

enum class SpiClockPhase : uint32_t {
  ONE_EDGE = 0,
  TWO_EDGE = SPI_CR1_CPHA,
};

enum class SpiClockPolarity : uint32_t {
  LOW = 0,
  HIGH = SPI_CR1_CPOL
};

enum class SpiBaudratePrescaler : uint32_t {
  DIV2 = 0,
  DIV4 = SPI_CR1_BR_0,
  DIV8 = SPI_CR1_BR_1,
  DIV16 = SPI_CR1_BR_1 | SPI_CR1_BR_0,
  DIV32 = SPI_CR1_BR_2,
  DIV64 = SPI_CR1_BR_2 | SPI_CR1_BR_0,
  DIV128 = SPI_CR1_BR_2 | SPI_CR1_BR_1,
  DIV256 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
};

enum class SpiBitOrder : uint32_t {
  MSB_FIRST = 0,
  LSB_FIRST = SPI_CR1_LSBFIRST,
};

enum class SpiTransDir : uint32_t {
  FULL_DUPLEX = 0,
  SIMPLEX_RX  = SPI_CR1_RXONLY,
  HALF_DUPLEX_RX = SPI_CR1_BIDIMODE,
  HALF_DUPLEX_TX = SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE,
};

enum class SpiDataWidth : uint32_t {
  _4BIT = SPI_CR2_DS_0 | SPI_CR2_DS_1,
  _5BIT = SPI_CR2_DS_2,
  _6BIT = SPI_CR2_DS_2 | SPI_CR2_DS_0,
  _7BIT = SPI_CR2_DS_2 | SPI_CR2_DS_1,
  _8BIT = SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
  _9BIT = SPI_CR2_DS_3,
  _10BIT = SPI_CR2_DS_3 | SPI_CR2_DS_0,
  _11BIT = SPI_CR2_DS_3 | SPI_CR2_DS_1,
  _12BIT = SPI_CR2_DS_3 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
  _13BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2,
  _14BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_0,
  _15BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1,
  _16BIT = SPI_CR2_DS_3 | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0,
};

enum class SpiFifoThreshold : uint32_t {
  HALF = 0,
  QUARTER = SPI_CR2_FRXTH,
};

enum class SpiCrcWidth : uint32_t {
  _8BIT = 0,
  _16BIT = SPI_CR1_CRCL,
};

enum class SpiNssMode : uint32_t {
  HARD_INPUT  = 0,
  HARD_OUTPUT = SPI_CR1_SSM,
  SOFT        = SPI_CR1_SSM,
};

enum class SpiState : uint32_t {
  RX_BUF_NOT_EMPTY   = SPI_SR_RXNE,
  TX_BUF_EMPTY       = SPI_SR_TXE,
  BUSY               = SPI_SR_BSY,
  CRC_ERROR          = SPI_SR_CRCERR,
  MODE_FAULT         = SPI_SR_MODF,
  OVERRUN            = SPI_SR_OVR,
  FRAME_FORMAT_ERROR = SPI_SR_FRE,
};

enum class SpiInterruptType : uint32_t {
  RX_BUF_NOT_EMPTY = SPI_CR2_RXNEIE,
  TX_BUF_EMPTY     = SPI_CR2_TXEIE,
  ERROR            = SPI_CR2_ERRIE,
};

enum class SpiDmaReqTarget : uint32_t {
  RX = SPI_CR2_RXDMAEN,
  TX = SPI_CR2_TXDMAEN,
};

enum class SpiDmaParityTarget : uint32_t {
  RX = SPI_CR2_RXDMAEN,
  TX = SPI_CR2_TXDMAEN,
};

enum class SpiDmaParityType : uint32_t {
  EVEN = 0,
  ODD  = 1,
};

struct Spi {
  SPI_TypeDef* p_spi;

  inline void enable() {
    p_spi->CR1 |= SPI_CR1_SPE;
  }

  inline void disable() {
    p_spi->CR1 &= ~SPI_CR1_SPE;
  }

  inline void setMode(SpiMode mode) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, as<uint32_t>(mode));
  }

  inline void setStandard(SpiStandard standard) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_FRF, as<uint32_t>(standard));
  }

  inline void setClockPhase(SpiClockPhase phase) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CPHA, as<uint32_t>(phase));
  }

  inline void setClockPolarity(SpiClockPolarity polarity) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CPOL, as<uint32_t>(polarity));
  }

  inline void setBaudratePrescaler(SpiBaudratePrescaler prescaler) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_BR, as<uint32_t>(prescaler));
  }

  inline void setTransBitOrder(SpiBitOrder order) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_LSBFIRST, as<uint32_t>(order));
  }

  inline void setTransDir(SpiTransDir dir) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE, as<uint32_t>(dir));
  }

  inline void setDataWidth(SpiDataWidth data_width) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_DS, as<uint32_t>(data_width));
  }

  inline void setRxFifoThreshold(SpiFifoThreshold threshold) {
    MODIFY_REG(p_spi->CR2, SPI_CR2_FRXTH, as<uint32_t>(threshold));
  }

  inline void setCrc(bool enable) {
    if (enable) {
      p_spi->CR1 |= SPI_CR1_CRCEN;
    } else {
      p_spi->CR1 &= ~SPI_CR1_CRCEN;
    }
  }

  inline void setCrcWidth(SpiCrcWidth width) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_CRCL, as<uint32_t>(width));
  }

  inline void setCrcNext() {
    p_spi->CR1 |= SPI_CR1_CRCNEXT;
  }

  inline void setCrcPolynomial(uint32_t poly) {
    p_spi->CRCPR = (uint16_t)poly;
  }

  inline uint32_t getRxCrc() {
    return (uint32_t)(p_spi->RXCRCR);
  }

  inline uint32_t getTxCrc() {
    return (uint32_t)(p_spi->TXCRCR);
  }

  inline void setNssMode(SpiNssMode mode) {
    MODIFY_REG(p_spi->CR1, SPI_CR1_SSM,  as<uint32_t>(mode));
    MODIFY_REG(p_spi->CR2, SPI_CR2_SSOE, ((uint32_t)(as<uint32_t>(mode) >> 16U)));
  }

  inline void setNssPulseMng(bool enable) {
    if (enable) {
      p_spi->CR2 |= SPI_CR2_NSSP;
    } else {
      p_spi->CR2 &= ~SPI_CR2_NSSP;
    }
  }

  inline bool isState(SpiState state) {
    return !!(p_spi->SR & as<uint32_t>(state));
  }
  
  inline void clearState(SpiState state) {
    CLEAR_BIT(p_spi->SR, as<uint32_t>(state));
  }

  inline void enableInterrupt(SpiInterruptType type) {
    p_spi->CR2 |= as<uint32_t>(type);
  }

  inline void disableInterrupt(SpiInterruptType type) {
    p_spi->CR2 &= ~(as<uint32_t>(type));
  }

  inline void enableDmaReq(SpiDmaReqTarget type) {
    p_spi->CR2 |= as<uint32_t>(type);
  }

  inline void disableDmaReq(SpiDmaReqTarget type) {
    p_spi->CR2 &= ~(as<uint32_t>(type));
  }

  inline void setDmaParity(SpiDmaParityTarget target, SpiDmaParityType type) {
    switch (target) {
      case SpiDmaParityTarget::TX:
        MODIFY_REG(p_spi->CR2, SPI_CR2_LDMATX, (as<uint32_t>(type) << SPI_CR2_LDMATX_Pos));
        break;
      case SpiDmaParityTarget::RX:
        MODIFY_REG(p_spi->CR2, SPI_CR2_LDMARX, (as<uint32_t>(type) << SPI_CR2_LDMARX_Pos));
        break;
    }
  }

  inline uint32_t getRegAddr() {
    return (uint32_t) &(p_spi->DR);
  }

  inline uint8_t receiveU8() {
    return (uint8_t)(p_spi->DR);
  }

  inline uint16_t receiveU16() {
    return (uint16_t)(p_spi->DR);
  }

  inline void sendU8(uint8_t data) {
#if defined (__GNUC__)
    __IO uint8_t *spidr = ((__IO uint8_t *)&p_spi->DR);
    *spidr = data;
#else
    *((__IO uint8_t *)&p_spi->DR) = data;
#endif /* __GNUC__ */
  }

  inline void sendU16(uint16_t data) {
#if defined (__GNUC__)
  __IO uint16_t *spidr = ((__IO uint16_t *)&p_spi->DR);
  *spidr = data;
#else
  p_spi->DR = data;
#endif /* __GNUC__ */
  }

  inline uint8_t transferU8sync(uint8_t data) {
    while (isState(SpiState::BUSY));
    while (!isState(SpiState::TX_BUF_EMPTY));
    sendU8(data);
    while (!isState(SpiState::RX_BUF_NOT_EMPTY));
    return receiveU8();
  }

  static inline void prepareGpio(SpiType spi_type, GpioPinType pin_type) {
    auto periph_type = as_periph_type(spi_type);
    if (!periph_type) { return; }

    auto result = get_af_idx(periph_type.value(), pin_type);
    if (!result) { return; }

    GpioType gpio_type = extract_gpio_type(pin_type);
    GpioPin pin {
      .port = {
        .p_gpio = STM32_PERIPH_INFO.gpio[as<uint8_t>(gpio_type)].p_gpio
      },
      .pin_bit = 1UL << extract_pin_idx(pin_type)
    };
    pin.setMode(GpioMode::ALTERNATE);
    pin.setPullMode(GpioPullMode::NO);
    pin.setSpeedMode(GpioSpeedMode::HIGH);
    pin.setOutputMode(GpioOutputMode::PUSHPULL);
    pin.setAlternateFunc(result.value());
  }

  static inline void prepareSpiMaster(SpiType spi_type, GpioPinType mosi_pin, GpioPinType miso_pin, GpioPinType sck_pin, SpiBaudratePrescaler prescaler) {
    const auto& spi_info = STM32_PERIPH_INFO.spi[as<uint8_t>(spi_type)];
    RccCtrl::enablePeriphBus(spi_info.bus);
    prepareGpio(spi_type, mosi_pin);
    prepareGpio(spi_type, miso_pin);
    prepareGpio(spi_type, sck_pin);

    Spi spi { .p_spi = spi_info.p_spi };
    spi.setTransDir(SpiTransDir::FULL_DUPLEX);
    spi.setMode(SpiMode::MASTER);
    spi.setDataWidth(SpiDataWidth::_8BIT);
    spi.setClockPolarity(SpiClockPolarity::LOW);
    spi.setClockPhase(SpiClockPhase::ONE_EDGE);
    spi.setNssMode(SpiNssMode::SOFT);
    spi.setBaudratePrescaler(prescaler);
    spi.setTransBitOrder(SpiBitOrder::MSB_FIRST);
    spi.setCrc(false);
    spi.setCrcPolynomial(7);
    spi.setStandard(SpiStandard::MOTOROLA);
    spi.setRxFifoThreshold(SpiFifoThreshold::QUARTER);
    spi.setNssPulseMng(true);
    spi.enable();
  }
};

}

#endif /* IGB_STM32_PERIPH_SPI_H */
